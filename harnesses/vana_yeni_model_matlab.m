clc;

clear;

% 1. Logları struct array ('ts' dizisi) içine yüklüyoruz

ts(1) = prepareLogForParameterEstimation("log0471.csv");

ts(2) = prepareLogForParameterEstimation("log0472.csv");

ts(3) = prepareLogForParameterEstimation("log0475.csv");

ts(4) = prepareLogForParameterEstimation("log0477.csv");

ts(5) = prepareLogForParameterEstimation("log0479.csv");

ts(6) = prepareLogForParameterEstimation("log0481.csv");

ts(7) = prepareLogForParameterEstimation("log0488.csv");

ts(8) = prepareLogForParameterEstimation("log0492.csv");

ts(9) = prepareLogForParameterEstimation("log0493.csv");

ts(10) = prepareLogForParameterEstimation("log0494.csv");

ts(11) = prepareLogForParameterEstimation("log0495.csv");

% Read the CSV file
dataTable = readtable('C:\Users\Kaan Kalkandelen\OneDrive\Desktop\ROKET\git\Metu-X\LOGS\log1163.csv');

% Initialize the struct
Test1 = struct();

% Get the column names
varNames = dataTable.Properties.VariableNames;

% Loop through columns (starting from 2 to skip the timestamp column)
for col = 2:width(dataTable)
    % Create a timeseries object for each variable linked to the timestamp
    Test1.(varNames{col}) = timeseries(dataTable{:, col}, dataTable.timestamp);
end

% 11 adet log için sonuçları tutacak boş vektör

q_matrisi = zeros(11, 1);

close all

% HEDEF AÇILAR DİZİSİ (Senin test listene göre sıralı)

test_acilari = [50, 100, 150, 200, 300, 400, 500, 600, 800, 900, 1080];

%% Döngü ile her logun KENDİ açısına göre OLS (En Küçük Kareler) hesabı

for i = 1:11

Pm = ts(i).manifold_pressure.Data;

Pn = ts(i).nozzle_pressure.Data;

valveAngle_raw = ts(i).valveAngle.Data;


% Valf verisini 4'te 1 oranında seyrelt (Downsampling)

valveAngle = valveAngle_raw(1:4:end);


% O anki testin hedef açısını diziden çek ve 10 derece tolerans payı bırak

hedef_aci = test_acilari(i) - 1;


% Hizalanmış yeni valf verisinde HEDEF AÇIYA ulaşılan ilk anı bul

cutoff_index = find(valveAngle >= hedef_aci, 1);


% Verileri o andan itibaren sonuna kadar kırp

Pm_crop = Pm(cutoff_index:end);

Pn_crop = Pn(cutoff_index:end);


% Matris formülasyonu için sütun vektörüne çevir

H = Pm_crop(:);

Y = Pn_crop(:);


% q katsayısını hesapla

q_anlik = inv(H' * H) * H' * Y;


% Bulunan değeri sonuç matrisine kaydet

q_matrisi(i, 1) = q_anlik;

end

test_acilari= [0 test_acilari];

q_matrisi = [0; q_matrisi];

% --- Sonucu Görüntüle ---

disp('Açılarına Göre Tüm Testlerin q Katsayıları (1. testten 11. teste sırasıyla):');

disp(q_matrisi);

figure;

plot(q_matrisi, test_acilari, 'LineWidth', 1.5);

hold on;

grid on;

% =========================================================================

% --- 1. KONTROLCÜ İÇİN TERS MODEL (Açı = f(q)) ---

% =========================================================================

Qx = linspace(0, 0.66, 1000)';

Hnew = q_matrisi .^ [1:6];

% Kesinlikle istenen inv() formülü kullanıldı

Coef = inv(Hnew' * Hnew) * Hnew' * test_acilari';


disp('Tüm Testler İçin Kontrolcü Polinom Katsayıları (Coef):');

disp(Coef);


Hnew2 = Qx .^ [1:6];

Qy = Hnew2 * Coef;

plot(Qx, Qy, 'r:', 'LineWidth', 2);

legend({'Measured Data', '6th Degree Estimated Fit'}, 'Location', 'best');

xlabel('q Katsayısı (Pn/Pm)');

ylabel('Valf Açısı (Derece)');

title('Valf Açısı ile q Oranı İlişkisi');

% =========================================================================

% --- 2. SIMULINK PLANT MODELİ İÇİN KATSAYILAR (Normalizasyon + inv() Çözümü) ---

% =========================================================================

% Sayısal hassasiyet kaybını önlemek için açıları 0-1 arasına çekiyoruz

test_acilari_norm = test_acilari / 1080;

% Normalize edilmiş verilerle (0 ile 1 arasındaki sayılarla) matrisi kur

H_plant_norm = test_acilari_norm' .^ [1:6];

% Matris değerleri 1'i geçmediği için inv() formülü MÜKEMMEL kararlılıkla çalışır

Plant_Coef_norm = inv(H_plant_norm' * H_plant_norm) * H_plant_norm' * q_matrisi;

% Bulduğumuz katsayıları Simulink'in doğrudan ham açıları (0-1080)

% kullanabilmesi için orijinal ölçeğine geri döndürüyoruz (Un-scaling)

Plant_Coef = Plant_Coef_norm ./ (1080 .^ [1:6]');

% Simulink formatı: BÜYÜKTEN KÜÇÜĞE (K6, K5... K1) ve sonuna 0 (Sabit Terim)

SimCoef = [flipud(Plant_Coef); 0]';

disp('------------------------------------------------------');

disp('Normalizasyonlu ve inv() Formüllü 5. Derece Katsayılar (SimCoef):');

disp(SimCoef);
% Format the Controller coefficients (6th degree down to Constant) for Simulink
CtrlCoef = [flipud(Coef); 0]';