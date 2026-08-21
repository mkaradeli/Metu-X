import numpy as np
import pandas as pd
import os

import sys


# Kendi log_processor_lib csv'sini sartname Tablo 1 formatina cevirir
# Zaman (sn), Irtifa (m), Inis Hizi (m/s), Yuvarlanma, Yunuslama, Yalpalama (Derece)

TEAM_NAME = "Metu-X"      # Takim adi
PHASE     = "Deneme"      # "Deneme" ya da "Yarisma"
SHOT_NO   = 1             # Atis no

DOWNSAMPLE_HZ = 30        # sartname en az 30 Hz istiyor, 0 = ham hizda birak
DECIMAL = ","             # ondalik ayirici (sartname ornegi virgul kullaniyor)
SEP     = ";"             # DECIMAL virgul ise sutun ayirici noktali virgul olmali

ALTITUDE_COL   = "lidar_height"   # kalman duzgun calismadigi icin dogrudan lidar
ALTITUDE_SCALE = 1.0      # kaynak metre degilse olcek (orn. cm ise 0.01)
DESCENT_POSITIVE = True   # inis hizi asagi dogru pozitif olsun

# Hiz irtifadan turetilir: once irtifa yumusatilir, sonra kayan pencerede
# dogru fit edilip egimi hiz olarak alinir (gurultuyu turev buyutmesin diye)
ALT_SMOOTH_MS = 100       # irtifa yumusatma penceresi
VEL_WINDOW_MS = 300       # hiz icin dogru fit penceresi
TILT_CORRECT  = False     # lidar egik bakiyorsa irtifayi cos(egim) ile duzelt


dirlist = sorted(os.listdir("."))

for _ in dirlist:
	if "log" in _ and ".csv" in _:
		filename = _
if len(sys.argv) == 2:
	filename = sys.argv[1]
print(filename)


def quat_to_euler(qi, qj, qk, qr):
	# ZYX (yaw-pitch-roll) donusumu, derece cinsinden
	norm = np.sqrt(qi**2 + qj**2 + qk**2 + qr**2)
	norm[norm == 0] = 1.0
	qi, qj, qk, qr = qi/norm, qj/norm, qk/norm, qr/norm

	roll  = np.arctan2(2*(qr*qi + qj*qk), 1 - 2*(qi**2 + qj**2))
	pitch = np.arcsin(np.clip(2*(qr*qj - qk*qi), -1.0, 1.0))
	yaw   = np.arctan2(2*(qr*qk + qi*qj), 1 - 2*(qj**2 + qk**2))

	return np.degrees(roll), np.degrees(pitch), np.degrees(yaw)


def fmt(x, n):
	return ["" if np.isnan(val) else f"{val:.{n}f}".replace(".", DECIMAL) for val in x]


def is_recorded(x):
	# Sensor hic yazmamissa sutun bastan sona tam sifirdir
	return np.any(x != 0)


def slope_velocity(alt, t, window):
	# Kayan pencerede en kucuk kareler dogru fitinin egimi = hiz
	# (merkezi fark tek ornek gurultusunu buyutur, bu yontem buyutmez)
	half = max(1, window // 2)
	n = len(alt)
	vel = np.zeros(n)
	for i in range(n):
		i0 = max(0, i - half)
		i1 = min(n, i + half + 1)
		tw = t[i0:i1] - t[i]
		aw = alt[i0:i1]
		denom = np.sum(tw*tw)
		vel[i] = np.sum(tw * (aw - aw.mean())) / denom if denom > 0 else 0.0
	return vel


df = pd.read_csv(filename)

timestamp = df["timestamp"].to_numpy()

if ALTITUDE_COL not in df.columns:
	print(f"irtifa sutunu bulunamadi: {ALTITUDE_COL}")
	exit()

altitude_raw = df[ALTITUDE_COL].to_numpy() * ALTITUDE_SCALE
altitude_ok = is_recorded(altitude_raw)

qi, qj, qk, qr = (df["quaternion_i"].to_numpy(), df["quaternion_j"].to_numpy(),
                  df["quaternion_k"].to_numpy(), df["quaternion_r"].to_numpy())
attitude_ok = is_recorded(qi) or is_recorded(qj) or is_recorded(qk)

if altitude_ok:
	altitude = altitude_raw
	print(f"irtifa kaynagi: {ALTITUDE_COL}")
else:
	altitude = np.full_like(altitude_raw, np.nan)
	print(f"irtifa kaydedilmemis ({ALTITUDE_COL} tamamen 0), sutun bos birakilacak")

if attitude_ok:
	roll, pitch, yaw = quat_to_euler(qi, qj, qk, qr)
	print("attitude kaynagi: quaternion")
else:
	roll  = np.full_like(qi, np.nan)
	pitch = np.full_like(qi, np.nan)
	yaw   = np.full_like(qi, np.nan)
	print("quaternion kaydedilmemis, yuvarlanma/yunuslama/yalpalama bos birakilacak")

if TILT_CORRECT and altitude_ok and attitude_ok:
	# lidar egik bakiyorsa olctugu mesafe irtifadan buyuktur
	tilt_cos = np.cos(np.radians(roll)) * np.cos(np.radians(pitch))
	altitude = altitude * np.clip(tilt_cos, 0.1, 1.0)
	print("irtifa egim duzeltmesi uygulandi")

# --- Hiz: yumusatilmis irtifanin kayan pencere egimi ---
if altitude_ok:
	dt = np.median(np.diff(timestamp))
	alt_smooth = pd.Series(altitude).rolling(
		max(1, int(ALT_SMOOTH_MS*1e-3/dt)), center=True, min_periods=1).mean().to_numpy()
	velocity = slope_velocity(alt_smooth, timestamp, max(3, int(VEL_WINDOW_MS*1e-3/dt)))
	descent = -velocity if DESCENT_POSITIVE else velocity
	print(f"hiz kaynagi: {ALTITUDE_COL} turevi "
	      f"({ALT_SMOOTH_MS} ms yumusatma, {VEL_WINDOW_MS} ms fit penceresi)")
else:
	descent = np.full_like(altitude_raw, np.nan)
	print("irtifa yok, inis hizi da bos birakilacak")

# --- Ornekleme frekansini dusurme ---
# Adim asagi yuvarlanir, boylece sonuc her zaman DOWNSAMPLE_HZ'in ustunde kalir
if DOWNSAMPLE_HZ:
	fs = 1.0 / np.median(np.diff(timestamp))
	step = max(1, int(fs / DOWNSAMPLE_HZ))
	idx = np.arange(0, len(timestamp), step)
else:
	idx = np.arange(len(timestamp))

print(f"{len(timestamp)} satir -> {len(idx)} satir "
      f"({len(idx)/(timestamp[-1]-timestamp[0]):.1f} Hz)")

out = pd.DataFrame({
	"Zaman (sn)":          fmt(timestamp[idx] - timestamp[idx][0], 3),
	"İrtifa (m)":          fmt(altitude[idx], 2),
	"İniş Hızı (m/s)":     fmt(descent[idx], 2),
	"Yuvarlanma (Derece)": fmt(roll[idx], 4),
	"Yunuslama (Derece)":  fmt(pitch[idx], 4),
	"Yalpalama (Derece)":  fmt(yaw[idx], 4),
})

# Dosya adi: "Takim Adi-Deneme/Yarisma-Atis no:###"
# Windows dosya adinda ':' ve '/' kullanilamadigi icin ayirici olarak '-' ve bosluk
outname = f"{TEAM_NAME}-{PHASE}-Atis no {SHOT_NO:03d}.csv"
outpath = os.path.join(os.path.dirname(os.path.abspath(filename)), outname)

out.to_csv(outpath, sep=SEP, index=False, encoding="utf-8-sig")
print(f"kaydedildi: {outpath}")
print(out.head())
