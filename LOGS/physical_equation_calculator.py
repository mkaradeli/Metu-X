'''
import numpy as np
import pandas as pd
from scipy.optimize import curve_fit
from sklearn.metrics import r2_score
from log_processor_lib import log_processor
import os
import sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# ==========================================
# AYARLAR
# ==========================================
TRIM_COUNT = 1100           
THETA_MAX = 1080.0         # Vana tam açıklığı

# ==========================================
# 1. FİZİKSEL MODEL (1080° Normalized & Lossy)
# ==========================================
def valve_loss_model(data, C_eff, alpha, k):
    """
    3D Plot için Fiziksel Model (Z = DeltaP)
    Girdiler: Pm (X), Theta (Y)
    Çıktı   : DeltaP (Z)
    """
    Pm, Theta = data
    
    # Normalizasyon
    theta_norm = Theta / THETA_MAX
    
    # İletim Fonksiyonu (Transmission)
    # Theta^k / (1 + alpha*Theta^k) yapısı
    # (1+alpha) çarpanı, theta=max iken fonksiyonu 1'e normalize eder.
    numerator = (1 + alpha) * (theta_norm ** k)
    denominator = 1 + alpha * (theta_norm ** k)
    
    transmission = numerator / denominator
    
    # Fiziksel koruma (Negatif olamaz)
    transmission = np.maximum(transmission, 0)
    
    # Delta P = Pm * (1 - Verim * İletim)
    return Pm * (1 - C_eff * transmission)

# ==========================================
# 2. VERİ İŞLEME (Data Pipeline)
# ==========================================
# Fitting için tüm veriyi tek havuzda, 
# Plotting için ayrı ayrı listelerde tutacağız.
combined_Pm = []
combined_Theta = []
combined_DeltaP = []

# Her bir log dosyasını (deneyi) ayrı ayrı saklamak için liste
log_trajectories = [] 

files = sorted([f for f in os.listdir(".") if "log" in f and f.endswith(".bin")])

print(f"Veriler işleniyor... Dosya Sayısı: {len(files)}")

for idx, filename in enumerate(files):
    try:
        myLog = log_processor(filename=filename)
        
        mp = myLog.df["manifold_pressure"].to_numpy()
        np_p = myLog.df["nozzle_pressure"].to_numpy()
        ang = myLog.valveAngle[0::4] 
        
        min_len = min(len(mp), len(np_p), len(ang))
        if min_len <= (2 * TRIM_COUNT): continue
            
        # Trimming
        mp_trim = mp[TRIM_COUNT : min_len - TRIM_COUNT]
        ang_trim = ang[TRIM_COUNT : min_len - TRIM_COUNT]
        np_trim = np_p[TRIM_COUNT : min_len - TRIM_COUNT]
        dp_trim = mp_trim - np_trim
        
        # 1. Havuza Ekle (Fitting için)
        combined_Pm.append(mp_trim)
        combined_Theta.append(ang_trim)
        combined_DeltaP.append(dp_trim)
        
        # 2. Ayrı Sakla (3D Line Plotting için)
        # Veriyi biraz seyrelterek saklayalım (örn: her 10. data) çizim performansı için
        step = 10 
        log_trajectories.append({
            'Pm': mp_trim[::step],
            'Theta': ang_trim[::step],
            'DeltaP': dp_trim[::step],
            'Name': f"Log {idx+1}"
        })
        
    except Exception as e:
        print(f"Dosya hatası ({filename}): {e}")
        continue

# Fitting için tek numpy array'e çevir
X_data = np.concatenate(combined_Pm)      # Pm (Manifold)
Y_data = np.concatenate(combined_Theta)   # Theta (Açı)
Z_data = np.concatenate(combined_DeltaP)  # Delta P (Hedef)

input_data = np.vstack((X_data, Y_data))

# ==========================================
# 3. FITTING (Model Eğitimi)
# ==========================================
# Bounds: C_eff [0, 1], alpha [0, inf], k [0.5, 5]
p0_guess = [0.90, 1.0, 2.0]
lower_bounds = [0.0, 0.0, 0.5]
upper_bounds = [0.999, 100.0, 5.0]

try:
    popt, pcov = curve_fit(valve_loss_model, input_data, Z_data, p0=p0_guess, bounds=(lower_bounds, upper_bounds))
    
    C_eff, alpha_val, k_val = popt
    
    # R2 Hesapla
    Z_pred = valve_loss_model(input_data, *popt)
    r2_val = r2_score(Z_data, Z_pred)
    
    print("\n" + "="*60)
    print(f"FİZİKSEL MODEL PARAMETRELERİ (R² = {r2_val:.4f})")
    print("="*60)
    print(f"C_eff (Max Verim) : {C_eff:.4f}")
    print(f"Alpha (Doygunluk) : {alpha_val:.4f}")
    print(f"k (Geometri Üssü) : {k_val:.4f}")
    print("-" * 60)

    # ==========================================
    # 4. 3D SURFACE PLOT OLUŞTURMA
    # ==========================================
    fig = plt.figure(figsize=(12, 9))
    ax = fig.add_subplot(111, projection='3d')

    # A) YÜZEY (Surface) Çizimi - Matematiksel Model
    # Grid oluştur (X: Pm 0-300 bar, Y: Theta 0-1100 derece)
    # Meshgrid çözünürlüğü (50x50 yeterli)
    # YENİ HALİ (Verinin maksimum değerini otomatik algılar)
    max_pm_data = X_data.max()  # Verindeki en yüksek basıncı bulur (örn: 4000)
    max_theta_data = Y_data.max()

    # Grid'i verinin %5 fazlasına kadar uzat ki grafik kenara yapışmasın
    pm_grid = np.linspace(0, max_pm_data * 1.05, 50)  
    theta_grid = np.linspace(0, THETA_MAX, 50)  
    X_surf, Y_surf = np.meshgrid(pm_grid, theta_grid)
    
    # Grid üzerindeki her nokta için Z (DeltaP) hesapla
    # Model fonksiyonuna array yapısında veriyoruz
    Z_surf = valve_loss_model((X_surf.ravel(), Y_surf.ravel()), *popt)
    Z_surf = Z_surf.reshape(X_surf.shape)

    # Yüzeyi çiz (Yarı şeffaf - alpha=0.6)
    surf = ax.plot_surface(X_surf, Y_surf, Z_surf, cmap='viridis', 
                           edgecolor='none', alpha=0.5, label='Fiziksel Model')

    # B) ÇİZGİLER (Lines) Çizimi - Gerçek Log Verileri
    # Her bir log dosyasını ayrı bir çizgi olarak ekle
    print("3D Çizgiler ekleniyor...")
    
    colors = plt.cm.jet(np.linspace(0, 1, len(log_trajectories)))
    
    for i, traj in enumerate(log_trajectories):
        # Her log dosyasını 3D uzayda bir çizgi olarak çiziyoruz
        # Genelde Theta sabit (veya az değişken), Pm düşüyor, DeltaP düşüyor.
        ax.plot(traj['Pm'], traj['Theta'], traj['DeltaP'], 
                color='black', linewidth=1.5, alpha=0.8)
        
        # Başlangıç noktasına nokta koyalım (Görsellik için)
        ax.scatter(traj['Pm'][0], traj['Theta'][0], traj['DeltaP'][0], color='red', s=10)

    # C) Eksen ve Etiketler
    ax.set_xlabel('\nManifold Basıncı (Pm) [Bar]', linespacing=3.0)
    ax.set_ylabel('\nValf Açısı (Theta) [Derece]', linespacing=3.0)
    ax.set_zlabel('\nBasınç Farkı (Delta P) [Bar]', linespacing=3.0)
    
    ax.set_title(f'Valf Karakteristik Yüzeyi ve Test Verileri\nR² = {r2_val:.4f} | K={k_val:.2f} | Eff={C_eff:.2f}', fontsize=12)

    # Bakış açısını ayarla (Döndürülebilir interaktif pencere açılacak)
    ax.view_init(elev=25, azim=135)
    
    # Colorbar ekle
    fig.colorbar(surf, ax=ax, shrink=0.5, aspect=10, label='Model Delta P (Bar)')
    
    plt.tight_layout()
    plt.show()

except Exception as e:
    print(f"Hata oluştu: {e}")
    import traceback
    traceback.print_exc()
'''
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

# ==========================================
# KULLANICI AYARLARI (LİSTE MODU)
# ==========================================
TRIM_COUNT = 700           
THETA_MAX = 1080.0         

# HANGİ DATALAR ÇİZİLSİN? (LİSTE FORMATI)
# Örnekler:
# [0, 2]      -> Sadece 0. ve 2. sıradaki dosyaları çizer.
# [1]         -> Sadece 1. dosyayı çizer.
# []          -> BOŞ bırakırsan HEPSİNİ çizer.
TARGET_LOG_INDICES = [187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198]  # <--- BURAYI LİSTE OLARAK DÜZENLE


# ==========================================
# 1. FİZİKSEL MODEL
# ==========================================
def valve_loss_model(data, C_eff, alpha, k):
    Pm, Theta = data
    theta_norm = Theta / THETA_MAX
    
    numerator = (1 + alpha) * (theta_norm ** k)
    denominator = 1 + alpha * (theta_norm ** k)
    transmission = numerator / denominator
    transmission = np.maximum(transmission, 0)
    
    return Pm * (1 - C_eff * transmission)

# ==========================================
# 2. VERİ İŞLEME VE FİLTRELEME
# ==========================================
combined_Pm = []
combined_Theta = []
combined_DeltaP = []
log_trajectories = [] 

files = sorted([f for f in os.listdir(".") if "log" in f and f.endswith(".bin")])

print(f"Toplam Dosya Sayısı: {len(files)}")
print("-" * 50)
print(f"{'INDEX':<6} {'DURUM':<12} {'DOSYA ADI'}")
print("-" * 50)

# Dosyaları listele ve hangilerinin seçildiğini göster
for i, f in enumerate(files):
    # Eğer liste boşsa HEPSİ seçilidir, doluysa sadece listedekiler seçilidir.
    is_selected = (len(TARGET_LOG_INDICES) == 0) or (i in TARGET_LOG_INDICES)
    status = "[SEÇİLDİ]" if is_selected else "..."
    print(f"{i:<6} {status:<12} {f}")
print("-" * 50)

print("\nBütün veriler model eğitimi için işleniyor...")

for idx, filename in enumerate(files):
    if not  ((len(TARGET_LOG_INDICES) == 0) or (idx in TARGET_LOG_INDICES)):
        continue
    print(idx, filename)
    myLog = log_processor(filename=filename)
    
    mp = myLog.df["manifold_pressure"].to_numpy()
    np_p = myLog.df["nozzle_pressure"].to_numpy()
    ang = myLog.valveAngle[0::4] 
    
    min_len = min(len(mp), len(np_p), len(ang))
    if min_len <= (2 * TRIM_COUNT): continue
        
    mp_trim = mp[TRIM_COUNT : min_len - TRIM_COUNT]
    ang_trim = ang[TRIM_COUNT : min_len - TRIM_COUNT]
    np_trim = np_p[TRIM_COUNT : min_len - TRIM_COUNT]
    dp_trim = mp_trim - np_trim
    
    # 1. Fitting Havuzu (Model hassasiyeti için HER ZAMAN tüm veriyi kullanırız)
    combined_Pm.append(mp_trim)
    combined_Theta.append(ang_trim)
    combined_DeltaP.append(dp_trim)
    
    # 2. Plotting Havuzu
    step = 10 
    log_trajectories.append({
        'Pm': mp_trim[::step],
        'Theta': ang_trim[::step],
        'DeltaP': dp_trim[::step],
        'Name': f"Log {idx}",
        'Index': idx
    })
        


X_data = np.concatenate(combined_Pm)
Y_data = np.concatenate(combined_Theta)
Z_data = np.concatenate(combined_DeltaP)
input_data = np.vstack((X_data, Y_data))

# ==========================================
# 3. FITTING (GLOBAL)
# ==========================================
p0_guess = [0.90, 1.0, 2.0]
lower_bounds = [0.0, 0.0, 0.5]
upper_bounds = [0.999, 100.0, 5.0]

popt, pcov = curve_fit(valve_loss_model, input_data, Z_data, p0=p0_guess, bounds=(lower_bounds, upper_bounds))

C_eff, alpha_val, k_val = popt
k_val = 2
popt[2] = 2

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
selected_trajs = [t for t in log_trajectories if (len(TARGET_LOG_INDICES)==0) or (t['Index'] in TARGET_LOG_INDICES)]
colors = cm.jet(np.linspace(0, 1, len(selected_trajs)))

for i, traj in enumerate(selected_trajs):
    ax1.plot(traj['Pm'], traj['Theta'], traj['DeltaP'], 
            color=colors[i], linewidth=2, label=f"Log {traj['Index']}")
    
    # Başlangıç noktası
    ax1.scatter(traj['Pm'][0], traj['Theta'][0], traj['DeltaP'][0], color=colors[i], s=20)

ax1.set_xlabel('Manifold P')
ax1.set_ylabel('Theta')
ax1.set_zlabel('Delta P')

title_str = "Tüm Veriler" if len(TARGET_LOG_INDICES) == 0 else f"Seçilen Loglar: {TARGET_LOG_INDICES}"
ax1.set_title(f"Fiziksel Model ve {title_str}")

# Legend (Eğer çok fazla değilse göster)
if len(selected_trajs) < 10:
    ax1.legend()
    
ax1.view_init(elev=25, azim=135)

# --- PLOT 2: ERROR TRAJECTORIES (SEÇİLENLER) ---
ax2 = fig.add_subplot(122, projection='3d')

# Gri Düzlem (0 Hata)
xx, yy = np.meshgrid(np.linspace(0, max_pm, 10), np.linspace(0, THETA_MAX, 10))
zz = np.zeros_like(xx)
ax2.plot_surface(xx, yy, zz, color='gray', alpha=0.2)

all_errors_for_limit = []

for i, traj in enumerate(selected_trajs):
    # Model Tahmini
    local_pred = valve_loss_model((traj['Pm'], traj['Theta']), *popt)
    local_error = traj['DeltaP'] - local_pred
    
    # DÜZELTME 1: extend içine direkt array'i veriyoruz.
    # max() alarak tek sayıya düşürme, çünkü tüm noktaları görmemiz lazım.
    all_errors_for_limit.extend(local_error)
    
    # Hata Çizgisi
    ax2.plot(traj['Pm'], traj['Theta'], local_error, 
             color=colors[i], linewidth=2, label=f"Log {traj['Index']}")
    
    # Referans noktası
    ax2.scatter(traj['Pm'][0], traj['Theta'][0], local_error[0], color=colors[i], s=10)

# ==========================================
# EKSEN LİMİTİ AYARI (DÖNGÜ DIŞI)
# ==========================================
if all_errors_for_limit:
    # Hataların mutlak değerini al (hem negatif hem pozitif hatalar için)
    abs_errors = np.abs(all_errors_for_limit)
    
    # DÜZELTME 2: Grafik kesilmesin diye 'percentile' yerine 'max' kullanıyoruz.
    # Böylece en uçtaki "outlier" hatayı bile kapsar.
    max_err = np.max(abs_errors)
    
    # Eğer max hata 0 ise (ideal durum), manuel bir aralık verelim (örn: 1.0)
    if max_err == 0: max_err = 1.0
    
    # Limiti %10 pay bırakarak ayarla
    ax2.set_zlim(-max_err * 1.1, max_err * 1.1)

ax2.set_xlabel('Manifold P')
ax2.set_ylabel('Theta')
ax2.set_zlabel('Hata (Residual)')
ax2.set_title('Seçilenlerin Hata Analizi')
ax2.view_init(elev=20, azim=120)

plt.tight_layout()
plt.show()
