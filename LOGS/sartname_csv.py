import sys, os, numpy as np, pandas as pd
import matplotlib.pyplot as plt

# Yeni log csv'sini sartname Tablo 1 formatina cevirir; kayit hizi oldugu gibi korunur
TEAM_NAME = "Metu-X"
PHASE     = "Yarisma"      # "Deneme" ya da "Yarisma"
SHOT_NO   = 1
LOG_FILE  = "tlm_20260914_113838.csv" # bos birakilirsa komut satirindan alinir

SEP, DECIMAL = ";", ","    # Turkce Excel: sutun ayirici ';', ondalik ',' (sartname ornegi de boyle)

filename = LOG_FILE or sys.argv[1]
df = pd.read_csv(filename)
mode = df["system_modes"].to_numpy()

# quaternion (i, j, k, real) -> ZYX euler, derece
qi, qj, qk, qr = (df[c].to_numpy() for c in ["quaternion_i", "quaternion_j", "quaternion_k", "quaternion_r"])
roll  = np.degrees(np.arctan2(2*(qr*qi + qj*qk), 1 - 2*(qi**2 + qj**2)))
pitch = np.degrees(np.arcsin(np.clip(2*(qr*qj - qk*qi), -1, 1)))
yaw   = np.degrees(np.arctan2(2*(qr*qk + qi*qj), 1 - 2*(qj**2 + qk**2)))

# Dara: roll/pitch icin ARM ani (ilk mode 6), yaw icin ilk mode 2/3 ani.
# O andaki deger sonraki tum veriden cikarilir, sonuc [-180, 180) araligina sarilir
def first_idx(modes, fallback):
	hit = np.flatnonzero(np.isin(mode, modes))
	return int(hit[0]) if hit.size else fallback
wrap = lambda x: (x + 180) % 360 - 180

i_arm = first_idx([6],    0)
i_yaw = first_idx([2, 3], i_arm)
roll  = wrap(roll  - roll[i_arm])
pitch = wrap(pitch - pitch[i_arm])
yaw   = wrap(yaw   - yaw[i_yaw])
print(f"dara: roll/pitch satir {i_arm} (mode {mode[i_arm]}), yaw satir {i_yaw} (mode {mode[i_yaw]})")

ts = df["timestamp"].to_numpy().astype(float)
if np.median(np.diff(ts)) > 1:   # SD logu us cinsinden (1 kHz), telemetri csv'si zaten saniye
	ts = ts / 1e6

# Pencere: system_modes ilk kez 2/3/4 oldugu satirdan baslar, mode 2'ye ilk girisin
# uzerinden SURE_S gectiginde (ya da 2/3/4 daha erken biterse orada) biter
SURE_S = 5.0
aktif = np.flatnonzero(np.isin(mode, [2, 3, 4]))
if not aktif.size:
	sys.exit("system_modes hic 2/3/4 olmamis, cikti uretilmedi")
ilk, son = aktif[[0, -1]]
i2 = first_idx([2], ilk)
son = min(son, np.searchsorted(ts, ts[i2] + SURE_S, side="right") - 1)
sl = slice(ilk, son + 1)
print(f"pencere: satir {ilk}-{son} ({son - ilk + 1} satir, {ts[son] - ts[ilk]:.2f} s), "
      f"mode 2 girisi satir {i2}")

ts = ts[sl] - ts[ilk]

out = pd.DataFrame({
	"Zaman (sn)":          ts,
	"İrtifa (m)":          df["kf_altitude"].to_numpy()[sl],
	"İniş Hızı (m/s)":     -df["kf_velocity"].to_numpy()[sl],   # asagi pozitif
	"Yuvarlanma (Derece)": roll[sl],
	"Yunuslama (Derece)":  pitch[sl],
	"Yalpalama (Derece)":  yaw[sl],
})

# Windows dosya adinda ':' ve '/' olamadigi icin "Takim Adi-Deneme-Atis no 001.csv"
outpath = os.path.join(os.path.dirname(os.path.abspath(filename)), f"{TEAM_NAME}-{PHASE}-Atis no {SHOT_NO:03d}.csv")
out.to_csv(outpath, sep=SEP, decimal=DECIMAL, index=False, encoding="utf-8-sig")
print(f"{len(out)} satir -> {outpath}")

fig, axes = plt.subplots(len(out.columns) - 1, 1, sharex=True, figsize=(10, 9))
for ax, col in zip(axes, out.columns[1:]):
	ax.plot(out["Zaman (sn)"], out[col])
	ax.set_ylabel(col); ax.grid()
axes[-1].set_xlabel("Zaman (sn)")
fig.suptitle(os.path.basename(outpath))
fig.tight_layout()
fig.savefig(outpath.replace(".csv", ".png"), dpi=120)
plt.show()
