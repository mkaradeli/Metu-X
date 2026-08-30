"""
Viewer for live_atis.csv (or any log already exported to csv), based on the
same layout/style as logViewer_pressure_test.py but reading the csv directly
(no log_processor/.bin needed) and with automatic cleanup for two problems
found in live_atis.csv:

1. A handful of rows are corrupted into physically-impossible garbage values
   on essentially random channels -- sometimes astronomic (~1e30), sometimes
   "only" a few thousand. A single such sample makes matplotlib autoscale the
   whole y-axis to that value, squashing all the real data to a flat line at
   the bottom -> looks like the axis "shifted". Fixed with a Hampel
   (rolling local-median/MAD) filter per column, which flags any sample that
   is far from its own immediate neighbors regardless of its magnitude.

2. Reference/demand channels (pressure_demand_*, thrust_demand_*, pos_ref_*)
   sit at a constant 0 for a long stretch before the real commanding starts,
   well after the feedback channels are already logging real data. Before
   that point they're not exactly 0 either -- they carry tiny denormalized
   float noise (~1e-44 .. 1e-30) from bit-level corruption, which a naive
   "first nonzero sample" check would mistake for the channel coming alive.
   Each demand channel's real, sustained start time is detected (a change
   that persists for many consecutive samples, not a single noisy blip) and
   everything before it is blanked (NaN) instead of drawn as a fake 0 demand.

3. Exactly one row in live_atis.csv has its timestamp corrupted into
   something wildly inconsistent (209.27s -> -414.02s -> 210.20s: only the
   middle sample is bad, the very next row picks back up right where it
   should). This is a single-sample glitch, not two recordings appended back
   to back -- it's repaired by interpolation. (Treating it as a session
   restart and re-basing everything after it, which an earlier version of
   this script did, silently opened a fake ~620s gap in the middle of the
   plot and pushed the real end of the shot off almost to the right edge --
   exactly what made the shot's actual ending hard to see.)

4. force_demand never actually returns to 0 in this log -- it keeps
   commanding a small idle-level value all the way to the last recorded
   sample (the recording just gets cut off mid-command). So "when the shot
   ends" isn't visible in the demand channels at all; it's only visible in
   the feedback (nozzle_pressure) as one clearly-shaped, large excursion
   above the idle/low-command baseline. The plot is cropped tightly (+/-1s)
   around that excursion, which also happens to hide a couple of remaining
   single-sample corrupted spikes later in the file (e.g. two samples ~5.5s
   apart sharing the exact same nonsense value, 348.218... -- a repeating
   bit-corruption pattern, not a real repeated reading) that sit far outside
   the shot and would otherwise still clutter the plot.

5. lidar_height/lidar_strength get the same Hampel cleaning as everything
   else and are plotted in a second window/tab. They get their *own* crop
   window rather than reusing the main figure's -- the vehicle's physical
   response (climb, bounce, settle) to the shot plays out over tens of
   seconds, well past the few-second nozzle-pressure burst that bounds the
   main figure, so cropping the lidar view to that same narrow window cuts
   the interesting part of the motion off early.
"""
import pathlib
import sys

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

DEFAULT_FILE = "live_atis.csv"
N_MOTORS = 4
HAMPEL_WINDOW = 11      # samples on each side considered "local neighborhood"
HAMPEL_K = 50           # reject if |x - local median| > k * local MAD


def fix_timestamp(t, resume_tol=2.0):
	"""Repair backward jumps in the time column.

	Most backward jumps in these logs are a single sample whose timestamp got
	corrupted -- the row right after it resumes exactly on schedule (e.g.
	209.27s -> -414.02s -> 210.20s: only the middle value is garbage). Those
	are fixed by interpolating just the bad sample.

	Only if the samples *after* the jump keep counting up from the new
	(lower) value -- i.e. it doesn't resume near the pre-jump schedule within
	`resume_tol` seconds -- do we treat it as a genuine session restart and
	re-base everything from there on, so time keeps increasing monotonically
	instead of folding back on itself on the plot."""
	t = np.asarray(t, dtype=float).copy()
	dt = np.diff(t)
	positive = dt[(dt > 0) & (dt < 1.0)]
	fallback_dt = np.median(positive) if len(positive) else 0.0
	for i in np.where(dt < 0)[0]:
		if i + 2 < len(t) and abs(t[i + 2] - (t[i] + 2 * fallback_dt)) < resume_tol:
			bad = t[i + 1]
			t[i + 1] = t[i] + fallback_dt
			print(f"[fix_timestamp] repaired isolated corrupted timestamp at row {i+1}: "
				  f"{bad:.3f}s -> {t[i+1]:.3f}s (neighbors resume on schedule)")
			continue
		offset = t[i] - t[i + 1] + fallback_dt
		print(f"[fix_timestamp] backward jump at row {i}: {t[i]:.3f}s -> {t[i+1]:.3f}s looks like "
			  f"a real session restart, re-based by {offset:.3f}s")
		t[i + 1:] += offset
	return t


def reject_outliers(series, window=HAMPEL_WINDOW, k=HAMPEL_K):
	"""Replace corrupted samples with NaN using a Hampel (local-median) filter.

	A handful of rows in this log get corrupted (bit errors -> a float
	reinterpreted as garbage). The corruption isn't a single fixed magnitude:
	sometimes it's astronomic (~1e30), sometimes it's "only" a few thousand
	(e.g. a valve angle reading of 5000 degrees, or a bit pattern that happens
	to decode to a suspiciously round 2**23) -- always physically impossible
	for the channel, but not always separable from real data with one global
	threshold.

	What every corrupted sample does share: it's an isolated single-sample
	spike that departs sharply from its immediate neighbors and is gone again
	on the very next sample, whereas the real signal (pressure, angle, force)
	only changes gradually from one 2ms sample to the next even during fast
	transients. So instead of comparing each sample to the column's global
	statistics, we compare it to a rolling local median; anything more than
	k local-MADs away from its own neighborhood is flagged, regardless of
	its absolute magnitude."""
	x = series.to_numpy(dtype=float)
	s = pd.Series(x)
	local_med = s.rolling(window, center=True, min_periods=1).median()
	resid = (s - local_med).abs()
	local_mad = resid.rolling(window, center=True, min_periods=1).median() * 1.4826
	thresh = np.maximum(k * local_mad.to_numpy(), 1e-9)
	bad = resid.to_numpy() > thresh
	n_bad = int(np.nansum(bad))
	if n_bad:
		print(f"[reject_outliers] {series.name}: dropped {n_bad} corrupted sample(s)")
	x[bad] = np.nan
	return pd.Series(x, index=series.index, name=series.name)


def find_logging_start(series, window=25, tol=1e-9):
	"""Index at which a channel stops being a flat constant (its lead-in
	value, usually 0) and starts producing real data. Requires the change to
	persist for `window` consecutive samples so a single noise blip doesn't
	count. Returns 0 if the channel is live for the whole log."""
	x = series.to_numpy(dtype=float)
	changed = np.abs(x - x[0]) > tol
	if not changed.any():
		return 0
	roll = pd.Series(changed).rolling(window).sum().to_numpy()
	persistent = np.where(roll >= window)[0]
	return int(persistent[0] - window + 1) if len(persistent) else int(np.argmax(changed))


def robust_noise_tol(x, n=500, k=10):
	"""Estimate a "this is just sensor noise" tolerance from the spread of
	the first `n` samples (a MAD-based robust noise floor, scaled up by k for
	margin), instead of a fixed hardcoded tolerance -- so it adapts to
	whatever the channel's own resting noise level actually is."""
	sample = x[: min(n, len(x))]
	sample = sample[~np.isnan(sample)]
	if len(sample) < 2:
		return 1e-9
	med = np.median(sample)
	mad = np.median(np.abs(sample - med)) * 1.4826
	return max(k * mad, 1e-9)


def find_settle_window(series, window=50):
	"""Span of a series from where it first, persistently, departs from its
	own starting (resting) value to where it last, persistently, departs
	from its own ending (resting) value -- i.e. the whole "something is
	happening" span, regardless of how long that takes or whether it settles
	back to the same resting value it started at.

	Unlike find_shot_window (a brief excursion against an otherwise-constant
	background, via a global magnitude threshold), this works for slow,
	long-duration motion that can occupy most of the recording, where a
	global "typical magnitude" reference would itself be skewed by the
	activity."""
	x = series.to_numpy(dtype=float)
	start = find_logging_start(pd.Series(x), window=window, tol=robust_noise_tol(x))
	rev = x[::-1]
	rev_end = find_logging_start(pd.Series(rev), window=window, tol=robust_noise_tol(rev))
	end = len(x) - 1 - rev_end
	if end <= start:
		return None
	return start, end


def mask_before(series, start_idx):
	x = series.to_numpy(dtype=float).copy()
	x[:start_idx] = np.nan
	return pd.Series(x, index=series.index, name=series.name)


def find_shot_window(t, magnitude, rel_level=15.0, bridge_gap_s=0.5):
	"""Locate the shot: the single dominant, sustained excursion of `magnitude`
	well above its own "quiet" level (idle noise and/or the low idle-command
	plateau).

	The threshold is derived from the data itself (rel_level x the median of
	all non-near-zero samples) rather than a fixed number, so it adapts to
	whatever units/scale the log actually has. Candidate active samples are
	grouped into clusters (allowing gaps up to `bridge_gap_s` seconds so brief
	dropped-sample holes inside the real shot don't split it), and the widest
	cluster -- i.e. the one with the most samples, which a multi-second real
	transient will always dominate over an isolated 1-2 sample corrupted
	spike -- is taken as the shot. Returns (start_idx, end_idx) or None if
	nothing stands out above the noise floor."""
	mag = np.nan_to_num(magnitude, nan=0.0)
	nonzero = mag[mag > 1e-9]
	if len(nonzero) == 0:
		return None
	ref = np.median(nonzero)
	threshold = rel_level * max(ref, 1e-9)
	active_idx = np.where(mag > threshold)[0]
	if len(active_idx) == 0:
		return None

	median_dt = np.median(np.diff(t))
	gap_samples = max(int(bridge_gap_s / median_dt), 1) if median_dt > 0 else 1

	clusters = []
	cur = [active_idx[0]]
	for idx in active_idx[1:]:
		if idx - cur[-1] <= gap_samples:
			cur.append(idx)
		else:
			clusters.append(cur)
			cur = [idx]
	clusters.append(cur)

	best = max(clusters, key=len)
	return best[0], best[-1]


def main():
	filename = sys.argv[1] if len(sys.argv) > 1 else DEFAULT_FILE
	print(f"loading {filename}")
	df = pd.read_csv(filename)

	t = fix_timestamp(df["timestamp"])

	feedback_cols = (
		[f"nozzle_pressure_{i}" for i in range(N_MOTORS)]
		+ [f"thrust_estimated_{i}" for i in range(N_MOTORS)]
		+ [f"valveAngle_{i}" for i in range(N_MOTORS)]
		+ ["thrust_measured"]
	)
	demand_cols = (
		[f"pressure_demand_{i}" for i in range(N_MOTORS)]
		+ [f"thrust_demand_{i}" for i in range(N_MOTORS)]
		+ [f"pos_ref_{i}" for i in range(N_MOTORS)]
	)
	lidar_cols = ["lidar_height", "lidar_strength", "manifold_pressure"]

	for col in feedback_cols + demand_cols + lidar_cols:
		df[col] = reject_outliers(df[col])

	demand_starts = {col: find_logging_start(df[col]) for col in demand_cols}
	for col, start in demand_starts.items():
		if start > 0:
			print(f"[find_logging_start] {col}: real data starts at t={t[start]:.3f}s (row {start})")
			df[col] = mask_before(df[col], start)

	# Write the fixed timestamp back into the dataframe so it's included
	# (correctly) in the cleaned export below.
	df["timestamp"] = t

	# The lidar figure gets its own crop further down: the vehicle's physical
	# motion (climb, bounce, settle) plays out over tens of seconds, much
	# longer than the nozzle-pressure burst that defines "the shot" below,
	# so keep the full-length, cleaned data around for it.
	t_full, df_full = t, df

	pressure_mag = np.zeros(len(df))
	for i in range(N_MOTORS):
		pressure_mag = np.fmax(pressure_mag, np.abs(np.nan_to_num(df[f"nozzle_pressure_{i}"].to_numpy(dtype=float), nan=0.0)))

	window = find_shot_window(t, pressure_mag)
	if window is not None:
		start_idx, end_idx = window
		margin = 1.0
		t0, t1 = t[start_idx] - margin, t[end_idx] + margin
		print(f"[find_shot_window] shot spans t={t[start_idx]:.3f}s..{t[end_idx]:.3f}s "
			  f"-> cropping plot to t={t0:.3f}s..{t1:.3f}s")
		keep = (t >= t0) & (t <= t1)
		t = t[keep]
		df = df.loc[keep].reset_index(drop=True)
	else:
		print("[find_shot_window] no clear shot excursion found in nozzle_pressure -- showing full log")

	# Save the cleaned data, cropped to this same narrow shot window, next
	# to the input file as "<name>_temiz.csv".
	out_path = pathlib.Path(filename).with_name(pathlib.Path(filename).stem + "_temiz.csv")
	df.to_csv(out_path, index=False)
	print(f"[clean export] saved cleaned+cropped data to {out_path}")

	fig, ax = plt.subplots(3, sharex=True)
	fig.canvas.manager.set_window_title(filename)
	fig.tight_layout()

	# ---- Nozzle pressure & demand ----
	ax[0].set_title("Nozzle Pressure")
	for i in range(N_MOTORS):
		ax[0].plot(t, df[f"nozzle_pressure_{i}"], label=f"Nozzle Pressure{i}")
	for i in range(N_MOTORS):
		ax[0].plot(t, df[f"pressure_demand_{i}"], "-.", label=f"Nozzle demand{i}")
	ax[0].set_ylabel("Pressure [Psi]")
	ax[0].legend(fontsize=7, ncol=2)
	ax[0].grid(True)

	# ---- Force & demand ----
	ax[1].set_title("Force Feedback / Demand")
	for i in range(N_MOTORS):
		ax[1].plot(t, df[f"thrust_estimated_{i}"] , label=f"Thrust estimated{i}")
	for i in range(N_MOTORS):
		ax[1].plot(t, df[f"thrust_demand_{i}"] , "-.", label=f"Thrust demand{i}")
	ax[1].plot(t, df["thrust_measured"] , "k.", markersize=2, label="thrust_measured")
	ax[1].set_ylabel("Force [N]")
	ax[1].legend(fontsize=7, ncol=2)
	ax[1].grid(True)

	# ---- Valve position & demand ----
	ax[2].set_title("Valve Position & Demand")
	for i in range(N_MOTORS):
		ax[2].plot(t, df[f"valveAngle_{i}"], label=f"Position Feedback{i}")
	for i in range(N_MOTORS):
		ax[2].plot(t, df[f"pos_ref_{i}"], "-.", label=f"Position Referance{i}")
	ax[2].set_ylabel("Valve Angle [deg]")
	ax[2].set_xlabel("time [s]")
	ax[2].legend(fontsize=7, ncol=2)
	ax[2].grid(True)

	# ---- Lidar, cleaned the same way, cropped to its own activity window --
	# (not the narrow nozzle-pressure shot window above: the physical climb/
	# bounce/settle this sensor is watching plays out on its own, longer,
	# timescale)
	t_lidar, df_lidar = t_full, df_full
	lidar_window = find_settle_window(df_full["lidar_height"])
	if lidar_window is not None:
		start_idx, end_idx = lidar_window
		margin = 2.0
		lt0, lt1 = t_full[start_idx] - margin, t_full[end_idx] + margin
		print(f"[find_settle_window] lidar activity spans t={t_full[start_idx]:.3f}s..{t_full[end_idx]:.3f}s "
			  f"-> cropping lidar plot to t={lt0:.3f}s..{lt1:.3f}s")
		lkeep = (t_full >= lt0) & (t_full <= lt1)
		t_lidar = t_full[lkeep]
		df_lidar = df_full.loc[lkeep].reset_index(drop=True)
	else:
		print("[find_settle_window] no clear lidar excursion found -- showing full log")

	fig2, lidar_ax = plt.subplots(3, sharex=True)
	fig2.canvas.manager.set_window_title(f"{filename} - lidar")
	fig2.tight_layout()

	lidar_ax[0].set_title("Lidar Height")
	lidar_ax[0].plot(t_lidar, df_lidar["lidar_height"])
	lidar_ax[0].set_ylabel("Height")
	lidar_ax[0].grid(True)

	lidar_ax[1].set_title("Lidar Signal Strength")
	lidar_ax[1].plot(t_lidar, df_lidar["lidar_strength"])
	lidar_ax[1].set_ylabel("Strength")
	lidar_ax[1].grid(True)

	lidar_ax[2].set_title("Manifold Pressure")
	lidar_ax[2].plot(t_lidar, df_lidar["manifold_pressure"])
	lidar_ax[2].set_ylabel("Pressure [Psi]")
	lidar_ax[2].set_xlabel("time [s]")
	lidar_ax[2].grid(True)

	plt.show()


if __name__ == "__main__":
	main()
