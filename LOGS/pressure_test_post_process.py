'''
# from copy import deepcopy
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from log_processor_lib import log_processor
import os
import matplotlib.cm as cm
import sys

# --- AYARLAR ---
TRIM_COUNT = 1100  # 1kHz'de 1.1 saniye = 1100 veri noktası

# --- Dosya Listesi ---
all_files = sorted([f for f in os.listdir(".") if "log" in f and f.endswith(".bin")])
target_files = [sys.argv[1]] if len(sys.argv) == 2 else all_files


# --- Plot Kurulumu ---
fig = plt.figure(figsize=(12, 10))
ax = fig.add_subplot(projection='3d')
fig.canvas.manager.set_window_title(f"Trimmed Analysis (First/Last {TRIM_COUNT} samples cut)")
colors = cm.jet(np.linspace(0, 1, len(target_files)))

print(f"İşleniyor: {len(target_files)} dosya. (Baştan/Sondan {TRIM_COUNT} veri siliniyor)")

for idx, filename in enumerate(target_files):
    try:
        myLog = log_processor(filename=filename)
        
        # 1. Verileri Çek
        mp = myLog.df["manifold_pressure"].to_numpy()
        np_p = myLog.df["nozzle_pressure"].to_numpy()
        # Encoder 4 kat hızlıysa senkronize et (Yoksa zaman kayar)
        ang = myLog.valveAngle[0::4] 
        
        # 2. Boyut Eşitle (Array Mismatch Hatasına Karşı)
        min_len = min(len(mp), len(np_p), len(ang))
        
        # 3. Güvenlik Kontrolü (Veri kesilince elde bir şey kalıyor mu?)
        if min_len <= (2 * TRIM_COUNT):
            print(f"Skipping {filename}: Veri çok kısa, kesilemiyor.")
            continue
            
        # 4. Kesme İşlemi (Slicing) ve Eksen Atama
        # [1100 : -1100] -> Baştan 1100 geç, sondan 1100 geri gel.
        x = mp[TRIM_COUNT : min_len - TRIM_COUNT]
        y = ang[TRIM_COUNT : min_len - TRIM_COUNT]
        z = x - np_p[TRIM_COUNT : min_len - TRIM_COUNT] # Delta P
        
        # 5. Çizim
        ax.plot(x, y, z, color=colors[idx], linewidth=0.5, alpha=0.6, label=filename)

    except Exception as e:
        print(f"HATA - {filename}: {e}")

# --- Görsel Ayarlar ---
ax.set_xlabel("Manifold Pressure [Bar]")
ax.set_ylabel("Valve Angle [Deg]")
ax.set_zlabel("Delta P [Bar]")
ax.grid(True)

if len(target_files) < 20:
    ax.legend(fontsize='x-small', loc='upper right')

plt.tight_layout()
plt.show()
'''

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from log_processor_lib import log_processor
import os
import matplotlib.cm as cm
import sys

# --- AYARLAR ---
TRIM_COUNT = 1100  # 1kHz'de 1.1 saniye = 1100 veri noktası

# --- KATSAYILAR (Cubic Weighted Fit) ---
# Delta P = f(Pm, Theta)
# Pm = Manifold Pressure (x), Theta = Valve Angle (y)
A = 224.4800502031
B = 0.7818054101
C = -1.3815825788
D =  0.0000193782
E = 0.0026307555
F = -0.0020704538
G = 0.0000000015
H = -0.0000014546
I = -0.0000000322
J = 0.0000014008

# --- Dosya Listesi ---
all_files = sorted([f for f in os.listdir(".") if "log" in f and f.endswith(".bin")])
target_files = [sys.argv[1]] if len(sys.argv) == 2 else all_files

# --- Plot Kurulumu ---
fig = plt.figure(figsize=(12, 10))
ax = fig.add_subplot(projection='3d')
fig.canvas.manager.set_window_title(f"Trimmed Analysis & Cubic Fit Surface")
colors = cm.jet(np.linspace(0, 1, len(target_files)))

print(f"İşleniyor: {len(target_files)} dosya. (Baştan/Sondan {TRIM_COUNT} veri siliniyor)")

# Yüzey plotu için limitleri tutacak değişkenler (Sonsuz ile başlatıyoruz)
global_min_mp, global_max_mp = np.inf, -np.inf
global_min_ang, global_max_ang = np.inf, -np.inf
has_data = False

for idx, filename in enumerate(target_files):
    try:
        myLog = log_processor(filename=filename)
        
        # 1. Verileri Çek
        mp = myLog.df["manifold_pressure"].to_numpy()
        np_p = myLog.df["nozzle_pressure"].to_numpy()
        # Encoder 4 kat hızlıysa senkronize et
        ang = myLog.valveAngle[0::4] 
        
        # 2. Boyut Eşitle
        min_len = min(len(mp), len(np_p), len(ang))
        
        # 3. Güvenlik Kontrolü
        if min_len <= (2 * TRIM_COUNT):
            print(f"Skipping {filename}: Veri çok kısa, kesilemiyor.")
            continue
            
        # 4. Kesme İşlemi (Slicing) ve Eksen Atama
        x = mp[TRIM_COUNT : min_len - TRIM_COUNT]       # Pm
        y = ang[TRIM_COUNT : min_len - TRIM_COUNT]      # Theta
        z = x - np_p[TRIM_COUNT : min_len - TRIM_COUNT] # Delta P
        
        # Global limitleri güncelle (Surface plot aralığı için)
        if len(x) > 0:
            has_data = True
            global_min_mp = min(global_min_mp, x.min())
            global_max_mp = max(global_max_mp, x.max())
            global_min_ang = min(global_min_ang, y.min())
            global_max_ang = max(global_max_ang, y.max())

        # 5. Çizim (Scatter/Line)
        ax.plot(x, y, z, color=colors[idx], linewidth=0.5, alpha=0.6, label=filename)

    except Exception as e:
        print(f"HATA - {filename}: {e}")

# --- YÜZEY (SURFACE) PLOT ---
if has_data:
    print("Yüzey modeli oluşturuluyor...")
    
    # Veri aralığında bir grid oluştur (Resolution: 50x50)
    # Biraz pay bırakmak için %5 marj ekleyelim
    margin_mp = (global_max_mp - global_min_mp) * 0.05
    margin_ang = (global_max_ang - global_min_ang) * 0.05
    
    pm_range = np.linspace(global_min_mp - margin_mp, global_max_mp + margin_mp, 50)
    theta_range = np.linspace(global_min_ang - margin_ang, global_max_ang + margin_ang, 50)
    
    Pm_grid, Theta_grid = np.meshgrid(pm_range, theta_range)
    
    # Denklem: Delta P hesapla
    # Python'da üs alma operatörü ** kullanır
    Z_surface = (A 
                 + B * Pm_grid 
                 + C * Theta_grid 
                 + D * (Pm_grid**2) 
                 + E * (Theta_grid**2) 
                 + F * (Pm_grid * Theta_grid) 
                 + G * (Pm_grid**3) 
                 + H * (Theta_grid**3) 
                 + I * (Pm_grid**2 * Theta_grid) 
                 + J * (Pm_grid * Theta_grid**2))
    
    # Yüzeyi çizdir
    surf = ax.plot_surface(Pm_grid, Theta_grid, Z_surface, 
                           cmap='viridis',    # Verilerden ayrışması için farklı renk
                           alpha=0.4,         # Şeffaflık (alttaki veriyi görmek için)
                           edgecolor='none',  # Grid çizgilerini kaldır
                           rstride=1, cstride=1,
                           antialiased=True)
    
    # Renk barı (Opsiyonel, yüzeyin değerlerini görmek için)
    # fig.colorbar(surf, ax=ax, shrink=0.5, aspect=10, label='Model Delta P')

# --- Görsel Ayarlar ---
ax.set_xlabel("Manifold Pressure (Pm) [Bar]")
ax.set_ylabel("Valve Angle (Theta) [Deg]")
ax.set_zlabel("Delta P [Bar]")
ax.set_title(f"Data vs Cubic Fit Model ($R^2$: 0.98)")
ax.grid(True)

# Görüş açısını ayarla (Opsiyonel - veriye göre değiştirebilirsin)
ax.view_init(elev=30, azim=-60)

if len(target_files) < 20:
    ax.legend(fontsize='x-small', loc='upper right')

plt.tight_layout()
plt.show()



















'''
print(filename)
# filename = "log"
myLog = log_processor(filename=filename)
# print(myLog.df.axes)
# test = pd.DataFrame([])

# print( test.__dir__())
# exit()
# print(myLog.df.)
# aaa = np.diff(myLog.df.angleRaw, append=[myLog.df.angleRaw[myLog.dataLen-1]])
'''

'''
fig,ax= plt.subplots(3,sharex=True)
fig.canvas.manager.set_window_title(filename) 

fig.tight_layout()

ax[0].grid(True)
ax[0].set_title("pressure")
ax[0].plot(myLog.df["timestamp"], myLog.df["manifold_pressure"], label="manifold_pressure")
ax[0].plot(myLog.df["timestamp"], myLog.df["nozzle_pressure"], label="nozzle_pressure")




ax[1].set_title('position')
print(myLog.valveAngle)
ax[1].plot(myLog.df.timestamp, myLog.df.pos_ref, label="pos_ref")
ax[1].plot(myLog.df.timestamp, myLog.df.pos_ref_rate_limited, label="pos_ref rate limited")
ax[1].plot(myLog.positionTime, myLog.valveAngle, label="valveAngle")
ax[1].plot(myLog.positionTime, myLog.valveAngleKalman, label="valveAngleKalman")

ax[1].set_ylabel("deg")
# ax[1].plot(myLog.df.timestamp, myLog.df.angleRaw/13.7, label="angleRaw")

# ax[1].plot(myLog.df.timestamp, myLog.df.valveAngleKalman, label = "kalman")
ax[1].legend()
ax[1].grid(True)
ax[2].set_title('velocity')
ax[2].plot(myLog.df.timestamp, myLog.df.speedDemand/6, label="speedDemand")
ax[2].plot(myLog.df.timestamp, myLog.df.speed_ref_rate_limited/6, label="speed demand rate_limited")
ax[2].plot(myLog.positionTime, myLog.valveVelocity/6, label = "speed feedback")
# ax[2].plot(myLog.df["manifold_pressure"],myLog.valveAngle[0::4])
ax[2].set_ylabel("RPM")
ax[2].legend()
# ax[2].plot(myLog.df.timestamp, myLog.df.encoderButt)
ax[2].grid(True)
plt.savefig(filename[:-4]+'.png')

plt.figure()
ax = plt.gcf().add_subplot(projection='3d')



print((myLog.df["manifold_pressure"]- myLog.df.nozzle_pressure).to_numpy())
print(type(myLog.df["valveAngle"]))
# plt.plot(myLog.df.manifold_pressure - myLog.df.nozzle_pressure, myLog.df.valveAngle)

ax.plot(myLog.df.manifold_pressure,myLog.valveAngle[0::4], myLog.df.manifold_pressure - myLog.df.nozzle_pressure, ".")
ax.set_xlabel("manifold")
ax.set_ylabel("angle")
ax.set_zlabel("delta")


plt.show()

print(myLog.df.axes)
'''
