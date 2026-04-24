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
% 10 adet log için sonuçları tutacak boş vektör
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
    % (İstersen - 10 kısmını silebilirsin, sana kalmış)
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

plot(q_matrisi,test_acilari)
hold on;
Qx = linspace(0, 0.66, 1000)';
for index = 4:6
    Hnew = q_matrisi .^ [1:index];
    
    Coef = inv(Hnew'*Hnew)*Hnew'*test_acilari';
    
    
    
    disp('Tüm Testler İçin Polinom Gözlem Matrisi (Hnew):');
    disp(Hnew);
    disp(Coef);
    
    Hnew2 = Qx .^ [1:index];
    Qy = Hnew2 * Coef;
    plot(Qx, Qy, ':');
end

%legend({'measured', 'estimated'})
