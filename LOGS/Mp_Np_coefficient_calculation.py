'''
import numpy as np
import pandas as pd
from scipy.optimize import curve_fit
from sklearn.metrics import r2_score
from log_processor_lib import log_processor
import os
import sys
import matplotlib.pyplot as plt

# ==========================================
# MÜHENDİSLİK PARAMETRELERİ
# ==========================================
TRIM_COUNT = 700            # Baştan/Sondan atılacak (1.1 sn @ 1kHz)
PRIORITY_LAST_N_FILES = 12    # Son 8 teste yüksek öncelik
HISTORY_WEIGHT_FACTOR = 10.0  # Tarihsel ağırlık çarpanı
LOW_ANGLE_CUTOFF = 500.0     # Sigmoid orta noktası
SIGMOID_SLOPE = 0.3         # Eğim yumuşaklığı

# --- Sigmoid Ağırlık Fonksiyonu ---
def calculate_physics_weight(angle_array):
    return 1 / (1 + np.exp(-SIGMOID_SLOPE * (angle_array - LOW_ANGLE_CUTOFF)))

# --- Model Fonksiyonu (Quadratic) ---
def model_func(data, a, b, c, d, e, f):
    x, y = data # x=Pm, y=Theta
    return a + b*x + c*y + d*x**2 + e*y**2 + f*x*y

# ==========================================
# VERİ İŞLEME (Data Processing Pipeline)
# ==========================================
all_Pm = []    
all_Theta = [] 
all_DeltaP = []
all_Weights = [] 

files = sorted([f for f in os.listdir(".") if "log" in f and f.endswith(".bin")])
total_files = len(files)

print(f"HESAPLANIYOR... Dosya Sayısı: {total_files}")
print(f"Trim: {TRIM_COUNT} sample | Weight Range: 0-1080 deg")

count_used = 0
count_skipped = 0

for idx, filename in enumerate(files):
    try:
        myLog = log_processor(filename=filename)
        
        # 1. Ham Veri Çekme
        mp = myLog.df["manifold_pressure"].to_numpy()
        np_p = myLog.df["nozzle_pressure"].to_numpy()
        ang = myLog.valveAngle[0::4] # Encoder Sync (4:1)
        
        # 2. Boyut Eşitleme (Safety)
        min_len = min(len(mp), len(np_p), len(ang))
        
        # 3. Yetersiz Veri Kontrolü
        if min_len <= (2 * TRIM_COUNT):
            count_skipped += 1
            continue
            
        # 4. TRIMMING (Kesme) - İlk ve Son 1.1 saniye çöp
        mp_trim = mp[TRIM_COUNT : min_len - TRIM_COUNT]
        ang_trim = ang[TRIM_COUNT : min_len - TRIM_COUNT]
        np_trim = np_p[TRIM_COUNT : min_len - TRIM_COUNT]
        
        # Hedef Değişken (Delta P)
        dp_trim = mp_trim - np_trim
        
        # 5. WEIGHTING (Ağırlıklandırma)
        # Tarihsel
        w_h = HISTORY_WEIGHT_FACTOR if idx >= (total_files - PRIORITY_LAST_N_FILES) else 1.0
        # Fiziksel
        w_p = calculate_physics_weight(ang_trim)
        
        w_total = w_h * w_p
        
        # Havuza Ekle
        all_Pm.append(mp_trim)
        all_Theta.append(ang_trim)
        all_DeltaP.append(dp_trim)
        all_Weights.append(w_total)
        count_used += 1
        
    except Exception:
        count_skipped += 1
        continue

print(f"Kullanılan Log: {count_used} | Atlanan (Kısa/Hatalı): {count_skipped}")

# Tek Matrise Dönüştür
X_data = np.concatenate(all_Pm)      # P_manifold
Y_data = np.concatenate(all_Theta)   # Angle
Z_data = np.concatenate(all_DeltaP)  # Delta_P
W_data = np.concatenate(all_Weights) # Weights

# ==========================================
# CURVE FITTING
# ==========================================
# Sigma = 1/Weight (Yüksek ağırlık = Düşük Hata Toleransı)
sigma_vals = 1.0 / (W_data + 1e-6)
input_data = np.vstack((X_data, Y_data))

popt, pcov = curve_fit(model_func, input_data, Z_data, sigma=sigma_vals, absolute_sigma=False)

# R2 Skorunu Hesapla (Weighted)
Z_pred = model_func(input_data, *popt)
r2_weighted = r2_score(Z_data, Z_pred, sample_weight=W_data)

# ==========================================
# ÇIKTI (OUTPUT)
# ==========================================
a, b, c, d, e, f = popt

print("\n" + "="*60)
print(f"VALF KARAKTERİSTİK DENKLEMİ (Weighted Fit)")
print("="*60)
print(f"Delta P = A + B*Pm + C*Theta + D*Pm^2 + E*Theta^2 + F*Pm*Theta")
print("-" * 40)
print(f"A (Sabit)   : {a:.10f}")
print(f"B (Pm)      : {b:.10f}")
print(f"C (Theta)   : {c:.10f}")
print(f"D (Pm^2)    : {d:.10f}")
print(f"E (Theta^2) : {e:.10f}")
print(f"F (Cross)   : {f:.10f}")
print("-" * 40)
print(f"Weighted R² Score: {r2_weighted:.5f}")
print("="*60)

print("\n--- Kopyalanabilir Format (Python/MATLAB) ---")
print(f"DeltaP = ({a:.8f}) + ({b:.8f})*Pm + ({c:.8f})*Theta + ({d:.8f})*Pm**2 + ({e:.8f})*Theta**2 + ({f:.8f})*Pm*Theta")
print("-" * 60)

# 6. GÖRSEL SAĞLAMA (Gerçek vs Tahmin)
plt.figure(figsize=(10,6))
plt.scatter(Z_data[::100], Z_pred[::100], alpha=0.1, s=3)
plt.plot([Z_data.min(), Z_data.max()], [Z_data.min(), Z_data.max()], 'r--', lw=2)
plt.xlabel("Gerçek Delta P")
plt.ylabel("Formülün Tahmin Ettiği Delta P")
plt.title(f"Model Doğrulama (R² = {r2_weighted:.3f})")
plt.grid(True)
plt.show()
'''
'''
import numpy as np
import pandas as pd
from scipy.optimize import curve_fit
from sklearn.metrics import r2_score
from log_processor_lib import log_processor
import os
import sys
import matplotlib.pyplot as plt

# ==========================================
# MÜHENDİSLİK PARAMETRELERİ
# ==========================================
TRIM_COUNT = 700            # Baştan/Sondan atılacak (1.1 sn @ 1kHz)

# --- Model Fonksiyonu (Cubic - 3. Derece) ---
def model_func(data, a, b, c, d, e, f, g, h, i, j):
    x, y = data # x=Pm, y=Theta
    return (a + 
            b*x + c*y + 
            d*x**2 + e*y**2 + f*x*y + 
            g*x**3 + h*y**3 + i*x**2*y + j*x*y**2)

# ==========================================
# VERİ İŞLEME (Data Processing Pipeline)
# ==========================================
all_Pm = []    
all_Theta = [] 
all_DeltaP = []

files = sorted([f for f in os.listdir(".") if "log" in f and f.endswith(".bin")])
total_files = len(files)

print(f"HESAPLANIYOR... Dosya Sayısı: {total_files}")
print(f"Trim: {TRIM_COUNT} sample | Weighting: UNIFORM (Eşit Ağırlık)")

count_used = 0
count_skipped = 0

for idx, filename in enumerate(files):
    try:
        myLog = log_processor(filename=filename)
        
        # 1. Ham Veri Çekme
        mp = myLog.df["manifold_pressure"].to_numpy()
        np_p = myLog.df["nozzle_pressure"].to_numpy()
        ang = myLog.valveAngle[0::4] # Encoder Sync (4:1)
        
        # 2. Boyut Eşitleme (Safety)
        min_len = min(len(mp), len(np_p), len(ang))
        
        # 3. Yetersiz Veri Kontrolü
        if min_len <= (2 * TRIM_COUNT):
            count_skipped += 1
            continue
            
        # 4. TRIMMING (Kesme) - İlk ve Son kısımlar atılıyor
        mp_trim = mp[TRIM_COUNT : min_len - TRIM_COUNT]
        ang_trim = ang[TRIM_COUNT : min_len - TRIM_COUNT]
        np_trim = np_p[TRIM_COUNT : min_len - TRIM_COUNT]
        
        # Hedef Değişken (Delta P)
        dp_trim = mp_trim - np_trim
        
        # Havuza Ekle
        all_Pm.append(mp_trim)
        all_Theta.append(ang_trim)
        all_DeltaP.append(dp_trim)
        count_used += 1
        
    except Exception:
        count_skipped += 1
        continue

print(f"Kullanılan Log: {count_used} | Atlanan (Kısa/Hatalı): {count_skipped}")

# Tek Matrise Dönüştür
X_data = np.concatenate(all_Pm)      # P_manifold
Y_data = np.concatenate(all_Theta)   # Angle
Z_data = np.concatenate(all_DeltaP)  # Delta_P

# ==========================================
# CURVE FITTING (Unweighted / OLS)
# ==========================================
input_data = np.vstack((X_data, Y_data))

# sigma parametresi kaldırıldı -> Tüm noktalar eşit önemde
popt, pcov = curve_fit(model_func, input_data, Z_data)

# R2 Skorunu Hesapla (Standart R2)
Z_pred = model_func(input_data, *popt)
r2_score_val = r2_score(Z_data, Z_pred)

# ==========================================
# ÇIKTI (OUTPUT)
# ==========================================
a, b, c, d, e, f, g, h, i, j = popt

print("\n" + "="*60)
print(f"VALF KARAKTERİSTİK DENKLEMİ (Cubic Uniform Fit)")
print("="*60)
print(f"Delta P = A + B*Pm + C*Theta + D*Pm^2 + E*Theta^2 + F*Pm*Theta")
print(f"          + G*Pm^3 + H*Theta^3 + I*Pm^2*Theta + J*Pm*Theta^2")
print("-" * 60)
print(f"A (Sabit)      : {a:.10f}")
print(f"B (Pm)         : {b:.10f}")
print(f"C (Theta)      : {c:.10f}")
print(f"D (Pm^2)       : {d:.10f}")
print(f"E (Theta^2)    : {e:.10f}")
print(f"F (Pm*Theta)   : {f:.10f}")
print(f"G (Pm^3)       : {g:.10f}")
print(f"H (Theta^3)    : {h:.10f}")
print(f"I (Pm^2*Theta) : {i:.10f}")
print(f"J (Pm*Theta^2) : {j:.10f}")
print("-" * 60)
print(f"R² Score: {r2_score_val:.5f}")
print("="*60)

print("\n--- Kopyalanabilir Format (Python/MATLAB) ---")
print(f"DeltaP = ({a:.8f}) + ({b:.8f})*Pm + ({c:.8f})*Theta + ({d:.8f})*Pm**2 + ({e:.8f})*Theta**2 + ({f:.8f})*Pm*Theta + ({g:.8f})*Pm**3 + ({h:.8f})*Theta**3 + ({i:.8f})*Pm**2*Theta + ({j:.8f})*Pm*Theta**2")
print("-" * 80)

# 6. GÖRSEL SAĞLAMA (Gerçek vs Tahmin)
plt.figure(figsize=(10,6))
# Veri yoğunluğunu azaltarak plot et (her 100. veri)
plt.scatter(Z_data[::100], Z_pred[::100], alpha=0.1, s=3, label='Veri Noktaları')
plt.plot([Z_data.min(), Z_data.max()], [Z_data.min(), Z_data.max()], 'r--', lw=2, label='İdeal Fit (y=x)')
plt.xlabel("Gerçek Delta P")
plt.ylabel("Formülün Tahmin Ettiği Delta P")
plt.title(f"Model Doğrulama - Cubic Uniform (R² = {r2_score_val:.3f})")
plt.legend()
plt.grid(True)
plt.show()
'''

import numpy as np
import pandas as pd
from scipy.optimize import curve_fit
from sklearn.metrics import r2_score
from log_processor_lib import log_processor
import os
import sys
import matplotlib.pyplot as plt

# ==========================================
# MÜHENDİSLİK PARAMETRELERİ
# ==========================================
TRIM_COUNT = 700            # Baştan/Sondan atılacak (1.1 sn @ 1kHz)

# --- Model Fonksiyonu (Cubic - 3. Derece) ---
def model_func(data, a, b, c, d, e, f, g, h, i, j):
    x, y = data # x=Pm, y=Theta
    return (a + 
            b*x + c*y + 
            d*x**2 + e*y**2 + f*x*y + 
            g*x**3 + h*y**3 + i*x**2*y + j*x*y**2)

# ==========================================
# VERİ İŞLEME (Data Processing Pipeline)
# ==========================================
all_Pm = []    
all_Theta = [] 
all_DeltaP = []

files = sorted([f for f in os.listdir(".") if "log" in f and f.endswith(".bin")])
total_files = len(files)

print(f"HESAPLANIYOR... Dosya Sayısı: {total_files}")
print(f"Trim: {TRIM_COUNT} sample | Weighting: UNIFORM (Eşit Ağırlık)")

count_used = 0
count_skipped = 0

for idx, filename in enumerate(files):
    try:
        myLog = log_processor(filename=filename)
        
        # 1. Ham Veri Çekme
        mp = myLog.df["manifold_pressure"].to_numpy()
        np_p = myLog.df["nozzle_pressure"].to_numpy()
        ang = myLog.valveAngle[0::4] # Encoder Sync (4:1)
        
        # 2. Boyut Eşitleme (Safety)
        min_len = min(len(mp), len(np_p), len(ang))
        
        # 3. Yetersiz Veri Kontrolü
        if min_len <= (2 * TRIM_COUNT):
            count_skipped += 1
            continue
            
        # 4. TRIMMING (Kesme) - İlk ve Son kısımlar atılıyor
        mp_trim = mp[TRIM_COUNT : min_len - TRIM_COUNT]
        ang_trim = ang[TRIM_COUNT : min_len - TRIM_COUNT]
        np_trim = np_p[TRIM_COUNT : min_len - TRIM_COUNT]
        
        # Hedef Değişken (Delta P)
        dp_trim = mp_trim - np_trim
        
        # Havuza Ekle
        all_Pm.append(mp_trim)
        all_Theta.append(ang_trim)
        all_DeltaP.append(dp_trim)
        count_used += 1
        
    except Exception:
        count_skipped += 1
        continue

print(f"Kullanılan Log: {count_used} | Atlanan (Kısa/Hatalı): {count_skipped}")

# Tek Matrise Dönüştür
X_data = np.concatenate(all_Pm)      # P_manifold
Y_data = np.concatenate(all_Theta)   # Angle
Z_data = np.concatenate(all_DeltaP)  # Delta_P

# ==========================================
# CURVE FITTING (Unweighted / OLS)
# ==========================================
input_data = np.vstack((X_data, Y_data))

# sigma parametresi kaldırıldı -> Tüm noktalar eşit önemde
popt, pcov = curve_fit(model_func, input_data, Z_data)

# R2 Skorunu Hesapla (Standart R2)
Z_pred = model_func(input_data, *popt)
r2_score_val = r2_score(Z_data, Z_pred)

# ==========================================
# ÇIKTI (OUTPUT)
# ==========================================
a, b, c, d, e, f, g, h, i, j = popt

print("\n" + "="*60)
print(f"VALF KARAKTERİSTİK DENKLEMİ (Cubic Uniform Fit)")
print("="*60)
print(f"Delta P = A + B*Pm + C*Theta + D*Pm^2 + E*Theta^2 + F*Pm*Theta")
print(f"          + G*Pm^3 + H*Theta^3 + I*Pm^2*Theta + J*Pm*Theta^2")
print("-" * 60)
print(f"A (Sabit)      : {a:.10f}")
print(f"B (Pm)         : {b:.10f}")
print(f"C (Theta)      : {c:.10f}")
print(f"D (Pm^2)       : {d:.10f}")
print(f"E (Theta^2)    : {e:.10f}")
print(f"F (Pm*Theta)   : {f:.10f}")
print(f"G (Pm^3)       : {g:.10f}")
print(f"H (Theta^3)    : {h:.10f}")
print(f"I (Pm^2*Theta) : {i:.10f}")
print(f"J (Pm*Theta^2) : {j:.10f}")
print("-" * 60)
print(f"R² Score: {r2_score_val:.5f}")
print("="*60)

print("\n--- Kopyalanabilir Format (Python/MATLAB) ---")
print(f"DeltaP = ({a:.8f}) + ({b:.8f})*Pm + ({c:.8f})*Theta + ({d:.8f})*Pm**2 + ({e:.8f})*Theta**2 + ({f:.8f})*Pm*Theta + ({g:.8f})*Pm**3 + ({h:.8f})*Theta**3 + ({i:.8f})*Pm**2*Theta + ({j:.8f})*Pm*Theta**2")
print("-" * 80)

# 6. GÖRSEL SAĞLAMA (Gerçek vs Tahmin)
plt.figure(figsize=(10,6))
# Veri yoğunluğunu azaltarak plot et (her 100. veri)
plt.scatter(Z_data[::100], Z_pred[::100], alpha=0.1, s=3, label='Veri Noktaları')
plt.plot([Z_data.min(), Z_data.max()], [Z_data.min(), Z_data.max()], 'r--', lw=2, label='İdeal Fit (y=x)')
plt.xlabel("Gerçek Delta P")
plt.ylabel("Formülün Tahmin Ettiği Delta P")
plt.title(f"Model Doğrulama - Cubic Uniform (R² = {r2_score_val:.3f})")
plt.legend()
plt.grid(True)
plt.show()