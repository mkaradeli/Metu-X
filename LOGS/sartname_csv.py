import numpy as np
import pandas as pd
import os

import sys


# Kendi log_processor_lib csv'sini sartname Tablo 1 formatina cevirir
# Zaman (sn), Irtifa (m), Inis Hizi (m/s), Yuvarlanma, Yunuslama, Yalpalama (Derece)

TEAM_NAME = "Metu-X"      # Takim adi
PHASE     = "Deneme"      # "Deneme" ya da "Yarisma"
SHOT_NO   = 1             # Atis no

LOG_FILE = "log2155.csv"             # doldurulursa (orn. "log2029.csv") bu dosya kullanilir,
                          # bos birakilirsa sys.argv, o da yoksa klasordeki son log*.csv
                          # ham log_processor_lib ciktisi verilir, kirpma script icinde yapilir

DOWNSAMPLE_HZ = 30        # sartname en az 30 Hz istiyor, 0 = ham hizda birak
DECIMAL = "."             # ondalik ayirici: nokta (virgul + noktali virgul Excel'in
SEP     = ","             # sutun ayiricisiyla karisip degerleri bozuyordu, bkz. son test)

ALTITUDE_COL     = "kf_altitude"    # lidarla beslenen kalman irtifasi
VELOCITY_COL     = "kf_velocity"    # lidarla beslenen kalman hizi
ALTITUDE_SCALE   = 1.0    # kaynak metre degilse olcek (orn. cm ise 0.01)
DESCENT_POSITIVE = True   # inis hizi asagi dogru pozitif olsun

LIDAR_COL        = "lidar_height"   # ham lidar mesafesi (mm), kf bos kaldiginda kullanilir
LIDAR_SCALE      = 0.001            # mm -> m

# --- Atis anini bulup log'u kirpma ---
# Uzun bir log alinip icinde kisa bir atis penceresi varsa, sartnameye sadece o
# pencere gonderilir. Atis, force demand sutunlarindan biri CROP_THRESHOLD'u
# gectigi an (yani komut gelmeye basladigi an) baslamis sayilir.
CROP_ENABLED     = True   # False -> log oldugu gibi (kirpilmadan) islenir
CROP_DEMAND_COLS = ["thrust_demand_0", "thrust_demand_1", "thrust_demand_2", "thrust_demand_3"]  # force demand
CROP_THRESHOLD   = 0.0    # N, bu degerin ustune cikan ilk ornek atisin baslangici
CROP_LEAD_IN_S   = 1.0    # atistan kac sn once baslasin


if LOG_FILE:
	filename = LOG_FILE
elif len(sys.argv) == 2:
	filename = sys.argv[1]
else:
	dirlist = sorted(os.listdir("."))
	filename = None
	for _ in dirlist:
		if "log" in _ and ".csv" in _:
			filename = _
	if filename is None:
		print("islenecek log*.csv bulunamadi, LOG_FILE ile dosya belirt")
		exit()

if not filename.endswith(".csv"):
	print(f"'{filename}' bir .csv degil. Bu script log_processor_lib.py'nin "
	      f".bin'den urettigi .csv'yi isler; ham binary logu degil.")
	exit()
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


def fmt(x):
	# repr: double (8 byte) hassasiyetini bozmadan en kisa round-trip gosterim
	return ["" if np.isnan(val) else repr(float(val)).replace(".", DECIMAL) for val in x]


def is_recorded(x):
	# Sensor hic yazmamissa sutun bastan sona tam sifirdir
	return np.any(x != 0)


def find_crop_start(ts, demand, threshold, lead_in_s):
	# demand: (N, k) dizisi. Sutunlardan herhangi biri esigi ilk gectigi satir
	# atisin baslangici sayilir. Geriye (baslangic index'i, atis zamani) doner;
	# esik hic gecilmediyse (0, None) doner.
	above = np.any(demand > threshold, axis=1)
	if not np.any(above):
		return 0, None
	fire_idx = int(np.argmax(above))
	t0 = ts[fire_idx]
	target = t0 - lead_in_s

	# atistan hemen once, lead_in_s'den daha buyuk bir kayit bosluğu varsa (orn.
	# ARM -> ates gecisinde SD yazma gecikmesi) o kadar geriye gidecek veri yok
	# demektir; bu durumda atisin ilk orneginden itibaren baslanir.
	if fire_idx > 0 and (t0 - ts[fire_idx - 1]) > lead_in_s:
		return fire_idx, t0

	start_idx = 0
	for i in range(fire_idx + 1):
		if ts[i] <= target:
			start_idx = i
		else:
			break
	return start_idx, t0


df = pd.read_csv(filename)

if CROP_ENABLED:
	ts_full = df["timestamp"].to_numpy()
	missing_cols = [c for c in CROP_DEMAND_COLS if c not in df.columns]
	if missing_cols:
		print(f"kirpma icin sutun bulunamadi: {missing_cols}, kirpma atlanacak")
	else:
		demand = df[CROP_DEMAND_COLS].to_numpy()
		start_idx, fire_t = find_crop_start(ts_full, demand, CROP_THRESHOLD, CROP_LEAD_IN_S)
		if fire_t is None:
			print(f"valf komutu hic {CROP_THRESHOLD} dereceyi gecmedi, log kirpilmadan islenecek")
		else:
			satir_once = len(df)
			df = df.iloc[start_idx:].reset_index(drop=True)
			print(f"atis tespit edildi: t={fire_t:.3f} s, kirpma baslangici: "
			      f"t={ts_full[start_idx]:.3f} s (satir {start_idx}), "
			      f"{satir_once} satir -> {len(df)} satir")

timestamp = df["timestamp"].to_numpy()

if ALTITUDE_COL not in df.columns:
	print(f"irtifa sutunu bulunamadi: {ALTITUDE_COL}")
	exit()

altitude_raw = df[ALTITUDE_COL].to_numpy() * ALTITUDE_SCALE
altitude_ok = is_recorded(altitude_raw)

qi, qj, qk, qr = (df["quaternion_i"].to_numpy(), df["quaternion_j"].to_numpy(),
                  df["quaternion_k"].to_numpy(), df["quaternion_r"].to_numpy())
attitude_ok = is_recorded(qi) or is_recorded(qj) or is_recorded(qk)

lidar_ok = LIDAR_COL in df.columns and is_recorded(df[LIDAR_COL].to_numpy())
if lidar_ok:
	lidar_altitude = df[LIDAR_COL].to_numpy() * LIDAR_SCALE

if altitude_ok:
	altitude = altitude_raw
	print(f"irtifa kaynagi: {ALTITUDE_COL}")
elif lidar_ok:
	altitude = lidar_altitude
	print(f"{ALTITUDE_COL} kaydedilmemis, irtifa kaynagi lidara dusuruldu: {LIDAR_COL}")
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

if VELOCITY_COL not in df.columns:
	print(f"hiz sutunu bulunamadi: {VELOCITY_COL}")
	exit()

velocity_raw = df[VELOCITY_COL].to_numpy()
velocity_ok = is_recorded(velocity_raw)

if velocity_ok:
	descent = -velocity_raw if DESCENT_POSITIVE else velocity_raw
	print(f"hiz kaynagi: {VELOCITY_COL}")
elif lidar_ok:
	lidar_rate = np.gradient(lidar_altitude, timestamp)   # d(irtifa)/dt, yukari pozitif
	descent = -lidar_rate if DESCENT_POSITIVE else lidar_rate
	print(f"{VELOCITY_COL} kaydedilmemis, hiz kaynagi lidarin turevine dusuruldu: {LIDAR_COL}")
else:
	descent = np.full_like(velocity_raw, np.nan)
	print(f"{VELOCITY_COL} kaydedilmemis (tamamen 0), inis hizi bos birakilacak")

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
	"Zaman (sn)":          fmt(timestamp[idx] - timestamp[idx][0]),
	"İrtifa (m)":          fmt(altitude[idx]),
	"İniş Hızı (m/s)":     fmt(descent[idx]),
	"Yuvarlanma (Derece)": fmt(roll[idx]),
	"Yunuslama (Derece)":  fmt(pitch[idx]),
	"Yalpalama (Derece)":  fmt(yaw[idx]),
})

# Dosya adi: "Takim Adi-Deneme/Yarisma-Atis no:###"
# Windows dosya adinda ':' ve '/' kullanilamadigi icin ayirici olarak '-' ve bosluk
outname = f"{TEAM_NAME}-{PHASE}-Atis no {SHOT_NO:03d}.csv"
outpath = os.path.join(os.path.dirname(os.path.abspath(filename)), outname)

out.to_csv(outpath, sep=SEP, index=False, encoding="utf-8-sig")
print(f"kaydedildi: {outpath}")
print(out.head())
