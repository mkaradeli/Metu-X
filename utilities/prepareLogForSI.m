% 1. Hazırlık
clear; clc;
files = dir('C:\Users\Kaan Kalkandelen\OneDrive\Desktop\ROKET\git\Metu-X\LOGS\*.csv'); % Klasördeki tüm CSV dosyalarını listele
merged_data = [];     % Boş bir konteyner oluştur

disp([num2str(length(files)) ' adet veri seti bulundu. İşleniyor...']);

TARGET_Ts = 0.001;

%% 2. Döngü: Oku -> Resample Et -> Merge Yap
for i = 1:length(files)
    baseFileName = files(i).name;
    fullFileName = fullfile(files(i).folder, baseFileName);
    
    try
        % A. Veriyi Oku
        raw = readtable(fullFileName);
        
        % Veriyi double array'e çevir
        u_raw = double(raw.nozzle_pressure);
        y_raw = double(raw.manifold_pressure);
        t_raw = double(raw.timestamp);
        
        % B. NAN Kontrolü (Veri temizliği)
        valid_idx = ~isnan(u_raw) & ~isnan(y_raw) & ~isnan(t_raw);
        u_raw = u_raw(valid_idx);
        y_raw = y_raw(valid_idx);
        t_raw = t_raw(valid_idx);
        
        if isempty(t_raw), continue; end % Boş dosya varsa atla

        % --- C. RESAMPLING (ENTERPOLASYON) ---
        % Sorunu çözen kısım burasıdır.
        
        % 1. Yeni, mükemmel bir zaman vektörü oluştur
        % Dosyanın başından sonuna kadar, TARGET_Ts adımlarıyla git.
        t_start = t_raw(1);
        t_end = t_raw(end);
        t_new = (t_start : TARGET_Ts : t_end)'; 
        
        % 2. Verileri bu yeni zaman vektörüne göre enterpole et (Linear Interpolation)
        u_new = interp1(t_raw, u_raw, t_new, 'linear', 'extrap');
        y_new = interp1(t_raw, y_raw, t_new, 'linear', 'extrap');
        
        % D. IDDATA Oluştur (Artık Ts hepsinde sabit!)
        temp_data = iddata(y_new, u_new, TARGET_Ts);
        temp_data.Name = ['Exp_' num2str(i)]; % Deney ismi ver
        
        % E. Merge İşlemi
        if isempty(merged_data)
            merged_data = temp_data;
        else
            merged_data = merge(merged_data, temp_data);
        end
        
        fprintf('OK: %s (Süre: %.1f sn)\n', baseFileName, t_end-t_start);
        
    catch ME
        warning(['HATA: ' baseFileName ' işlenemedi. Sebep: ' ME.message]);
    end
end

%% 3. Sonuç Kontrolü ve Yükleme
if ~isempty(merged_data)
    merged_data.InputName = 'Nozzle Pressure';
    merged_data.OutputName = 'Manifold Pressure';
    merged_data.TimeUnit = 'seconds';

    disp('------------------------------------------------');
    disp('BAŞARILI: Tüm veriler eşitlendi ve birleştirildi.');
    disp(['Toplam Deney Sayısı: ' num2str(size(merged_data, 4))]); % 4. boyut deney sayısıdır
    
    % System Identification App'i aç
    systemIdentification;
else
    disp('HATA: Hiçbir veri birleştirilemedi.');
end