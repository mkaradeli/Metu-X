clc;
clear;

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


q_matrisi = zeros(11, 1);

% 3D GRAFİK İÇİN TÜM HAM VERİLERİ BİRİKTİRECEĞİMİZ BOŞ HAVUZLAR
Tum_Pm = [];
Tum_Pn = [];
Tum_Aci = [];

close all

test_acilari = [50, 100, 150, 200, 300, 400, 500, 600, 800, 900, 1080];

%% Döngü ile her logun KENDİ açısına göre Q hesabı
for i = 1:11
    Pm = ts(i).manifold_pressure.Data;
    Pn = ts(i).nozzle_pressure.Data;
    valveAngle_raw = ts(i).valveAngle.Data;
    
    valveAngle = valveAngle_raw(1:4:end);
    
  
    hedef_aci = test_acilari(i) - 1;
    cutoff_index = find(valveAngle >= hedef_aci, 1);
    
    Pm_crop = Pm(cutoff_index:end);
    Pn_crop = Pn(cutoff_index:end);
    Aci_crop = valveAngle(cutoff_index:end); % 3D Grafik için Açı verisini de kırpıyoruz
    
    H = Pm_crop(:);
    Y = Pn_crop(:);
    Aci_crop = Aci_crop(:);
    
    q_anlik = inv(H' * H) * H' * Y;
    q_matrisi(i, 1) = q_anlik;
    
    % 3D GRAFİK İÇİN VERİLERİ HAVUZA EKLE (Alt alta birleştirme)
    Tum_Pm = [Tum_Pm; H];
    Tum_Pn = [Tum_Pn; Y];
    Tum_Aci = [Tum_Aci; Aci_crop];
end

test_acilari= [0 test_acilari];
q_matrisi = [0; q_matrisi];

% --- Sonucu Görüntüle ---
disp('Açılarına Göre Tüm Testlerin q Katsayıları:');
disp(q_matrisi);

figure('Name', 'Kontrolcü Modeli', 'Position', [100, 200, 600, 500]);
plot(q_matrisi, test_acilari, 'o', 'LineWidth', 1.5);
hold on; grid on;

Qx = linspace(0, 0.66, 1000)';
Hnew = q_matrisi .^ [1:6]; 
Coef = inv(Hnew' * Hnew) * Hnew' * test_acilari'; 
    
Hnew2 = Qx .^ [1:6];
Qy = Hnew2 * Coef;
plot(Qx, Qy, 'r-', 'LineWidth', 2);
legend({'Measured Data', '6. Derece Polinom'}, 'Location', 'best');
xlabel('q Katsayısı (Pn/Pm)');
ylabel('Valf Açısı (Derece)');
title('Kontrolcü Modeli (Açı = f(q))');


test_acilari_norm = test_acilari / 1080;
H_plant_norm = test_acilari_norm' .^ [1:6];
Plant_Coef_norm = inv(H_plant_norm' * H_plant_norm) * H_plant_norm' * q_matrisi;
Plant_Coef = Plant_Coef_norm ./ (1080 .^ [1:6]');
SimCoef = [flipud(Plant_Coef); 0]'; 

disp('------------------------------------------------------');
disp('Simulink Polynomial Bloğuna Yazılacak 6. Derece Katsayılar (SimCoef):');
disp(SimCoef);

%%  PLOTLAR

figure('Name', '3D Model ve Raw Data', 'Position', [750, 200, 600, 500]);


Pm_grid_vec = linspace(min(Tum_Pm), max(Tum_Pm), 50);
Aci_grid_vec = linspace(0, 1080, 50);
[Pm_grid, Aci_grid] = meshgrid(Pm_grid_vec, Aci_grid_vec);

q_grid = polyval(SimCoef, Aci_grid);


q_grid(q_grid > 1) = 1;
q_grid(q_grid < 0) = 0;


Pn_grid_est = q_grid .* Pm_grid;


plot3(Tum_Pm, Tum_Aci, Tum_Pn, 'b.', 'MarkerSize', 1, 'DisplayName', 'Raw Sensor Data');
hold on; grid on;


surf(Pm_grid, Aci_grid, Pn_grid_est, 'FaceAlpha', 0.6, 'EdgeColor', 'none', 'DisplayName', '6. Derece Model Yüzeyi');

xlabel('Manifold Basıncı (P_m)');
ylabel('Valf Açısı (\theta)');
zlabel('Nozzle Basıncı (P_n)');
title('3D Model ve Raw Data');
legend('show', 'Location', 'best');
view(45, 30); 


q_tum_est = polyval(SimCoef, Tum_Aci);
q_tum_est(q_tum_est > 1) = 1;
q_tum_est(q_tum_est < 0) = 0;

% Modelin Pn tahmini 
Pn_tum_est = q_tum_est .* Tum_Pm;

%Residual
Residuals = Tum_Pn - Pn_tum_est;

figure('Name', 'Sistem Hata Analizi', 'Position', [400, 50, 700, 500]);


scatter3(Tum_Pm, Tum_Aci, Residuals, 10, Residuals, 'filled');
hold on; grid on;


[X_ref, Y_ref] = meshgrid(linspace(min(Tum_Pm), max(Tum_Pm), 10), linspace(0, 1080, 10));
Z_ref = zeros(size(X_ref));
surf(X_ref, Y_ref, Z_ref, 'FaceColor', 'k', 'FaceAlpha', 0.2, 'EdgeColor', 'none');

xlabel('Manifold Basıncı (P_m)');
ylabel('Valf Açısı (\theta)');
zlabel('Residual (Gerçek P_n - Model P_n)');
title('3D Residual Haritası');
colorbar; 
view(45, 15);