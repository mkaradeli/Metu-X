
from os.path import exists
import numpy as np
import pandas as pd
from scipy.optimize import curve_fit
from sklearn.metrics import r2_score
from log_processor_lib import log_processor
import os
import sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.cm as cm

import pickle


pickleFile = "pickleFile.pck"
TRIM_COUNT = 700           
THETA_MAX = 1080.0         

valid_log_files = ['log0308.bin', 'log0309.bin', 'log0310.bin', 'log0311.bin', 'log0312.bin', 'log0313.bin', 'log0314.bin', 'log0315.bin', 'log0316.bin', 'log0317.bin', 'log0318.bin', 'log0319.bin', 'log0325.bin', 'log0332.bin', 'log0333.bin', 'log0334.bin', 'log0335.bin', 'log0339.bin', 'log0345.bin', 'log0394.bin', 'log0395.bin', 'log0396.bin']
# valid_log_files = ['log0308.bin', 'log0309.bin']
def valve_loss_model(data, C_eff, alpha):
    Pm, Theta = data
    theta_norm = Theta / THETA_MAX
    numerator = (1 + alpha) * (theta_norm ** 2)
    denominator = 1 + alpha * (theta_norm ** 2)
    transmission = numerator / denominator
    transmission = np.maximum(transmission, 0)
    return Pm * (1 - C_eff * transmission)

# ==========================================
# 2. VERİ İŞLEME VE FİLTRELEME
# ==========================================





myLogs = []

if not exists(pickleFile):

    for idx, filename in enumerate(valid_log_files):
        # if not  ((len(TARGET_LOG_INDICES) == 0) or (idx in TARGET_LOG_INDICES)):
        #     continue
        print(idx, filename)
        aaaa = log_processor(filename=filename)

        myLogs.append((aaaa.df, aaaa.df_4kHz))
        


    with open(pickleFile,'wb') as f:

        pickle.dump(myLogs,f)
else:
    with open(pickleFile,'rb') as f:
        myLogs = pickle.load(f)
        



exit()
# ==========================================
# 3. FITTING (GLOBAL)
# ==========================================
p0_guess = [0.90, 1.0]
lower_bounds = [0.0, 0.0]
upper_bounds = [0.999, 100.0]



popt, pcov = curve_fit(valve_loss_model, input_data, Z_data, p0=p0_guess, bounds=(lower_bounds, upper_bounds))

C_eff, alpha_val = popt
k_val = 2
# popt[2] = 2

# Global R2
Z_pred_global = valve_loss_model(input_data, *popt)
r2_val = r2_score(Z_data, Z_pred_global)

print("\n" + "="*60)
print(f"MODEL SONUÇLARI (R² = {r2_val:.5f})")
print(f"C_eff : {C_eff:.4f} | Alpha : {alpha_val:.4f} | k : {k_val:.4f}")
print("="*60)

# ==========================================
# 4. GÖRSELLEŞTİRME (LİSTE FİLTRELİ)
# ==========================================
fig = plt.figure(figsize=(18, 8))

# --- PLOT 1: MODEL SURFACE + SEÇİLEN DATALAR ---
ax1 = fig.add_subplot(121, projection='3d')

# Grid
max_pm = X_data.max()
pm_grid = np.linspace(0, max_pm * 1.05, 50) 
theta_grid = np.linspace(0, THETA_MAX, 50)
X_surf, Y_surf = np.meshgrid(pm_grid, theta_grid)

Z_surf = valve_loss_model((X_surf.ravel(), Y_surf.ravel()), *popt)
Z_surf = Z_surf.reshape(X_surf.shape)

# Yüzey (Surface)
surf = ax1.plot_surface(X_surf, Y_surf, Z_surf, cmap='viridis', 
                       edgecolor='none', alpha=0.3)

# Seçilen Dataları Çiz
# Renk paleti oluştur (Seçilen sayısı kadar renk üret)
# selected_trajs = [t for t in log_trajectories if (len(TARGET_LOG_INDICES)==0) or (t['Index'] in TARGET_LOG_INDICES)]
# colors = cm.jet(np.linspace(0, 1, len(selected_trajs)))

for i, traj in enumerate(log_trajectories):
    ax1.plot(traj['Pm'], traj['Theta'], traj['DeltaP'], 
             linewidth=2, label=f"Log {traj['Index']}")
    
    # Başlangıç noktası
    ax1.scatter(traj['Pm'][0], traj['Theta'][0], traj['DeltaP'][0], s=20)

ax1.set_xlabel('Manifold P')
ax1.set_ylabel('Theta')
ax1.set_zlabel('Delta P')

# title_str = "Tüm Veriler" if len(TARGET_LOG_INDICES) == 0 else f"Seçilen Loglar: {TARGET_LOG_INDICES}"
ax1.set_title(f"Fiziksel Model ve measurement")

# Legend (Eğer çok fazla değilse göster)
if len(log_trajectories) < 10:
    ax1.legend()

# --- PLOT 2: ERROR TRAJECTORIES (SEÇİLENLER) ---
ax2 = fig.add_subplot(122, projection='3d')

# Gri Düzlem (0 Hata)
xx, yy = np.meshgrid(np.linspace(0, max_pm, 10), np.linspace(0, THETA_MAX, 10))
zz = np.zeros_like(xx)
ax2.plot_surface(xx, yy, zz, color='gray', alpha=0.2)

all_errors_for_limit = []

for i, traj in enumerate(log_trajectories):
    local_pred = valve_loss_model((traj['Pm'], traj['Theta']), *popt)
    local_error = traj['DeltaP'] - local_pred
    
    all_errors_for_limit.extend(local_error)
    
    # Hata Çizgisi
    ax2.plot(traj['Pm'], traj['Theta'], local_error, 
              linewidth=2, label=f"Log {traj['Index']}")
    
    # Referans noktası
    ax2.scatter(traj['Pm'][0], traj['Theta'][0], local_error[0], s=10)

ax2.set_xlabel('Manifold P')
ax2.set_ylabel('Theta')
ax2.set_zlabel('Hata (Residual)')
ax2.set_title('Seçilenlerin Hata Analizi')
# ax2.view_init(elev=20, azim=120)


plt.figure(2)
for i, traj in enumerate(log_trajectories):
    plt.plot(traj['Speed'], traj['DeltaP'])
    

plt.tight_layout()
plt.show()
