% Define the filename
filename = 'log2005.csv';
% Read the data into a table
dataTable = readtable(filename, 'PreserveVariableNames', true);
headers = dataTable.Properties.VariableNames;

% Search for the specific column indices
nozzle_pressureColIdx = find(strcmp(headers, 'nozzle_pressure_0'));
thrustColIdx = find(strcmp(headers, 'thrust_measured'));
manifold_pressureColIdx = find(strcmp(headers, 'manifold_pressure'));
valve_velocityColIdx =  find(strcmp(headers, 'valveVelocity_0'));
valve_angleColIdx = find(strcmp(headers, 'valveAngle_0'));

% Extract the data series
nozzle_pressure = dataTable{:, nozzle_pressureColIdx};
thrust_kg = dataTable{:, thrustColIdx};
manifold_pressure = dataTable{:, manifold_pressureColIdx};
valve_velocity = dataTable{:, valve_velocityColIdx};
valve_angle = dataTable{:, valve_angleColIdx};

max_angle = max(valve_angle);
fprintf('Maksimum Valf Açısı: %f\n', max_angle);

% Load cell kalibrasyon katsayısı (regresyon.m ile hesaplandı, 200 N'e kadar fit)
LOADCELL_RATIO = 1.8361;

% Load cell okumasının kaldıraç oranı ile ölçeklenmiş gerçek itkisi
real_thrust = thrust_kg * 9.81 / LOADCELL_RATIO;

% --- 1. PLOT VE FİT İÇİN AKTİF VE STABİL DATAYI AYIRMA ---
% Vana açık (>5 deg), vana hareketsiz (|vel| < 30) ve itki negatif olmayan noktalar
plot_idx = (valve_angle > 5) & (abs(valve_velocity) < 30) & (real_thrust >= 1);

% Sadece stabil aktif test verilerini filtreleme
nozzle_pressure = nozzle_pressure(plot_idx);
manifold_pressure = manifold_pressure(plot_idx);
real_thrust = real_thrust(plot_idx);

% --- 2. Lineer Fit İşlemi ---
% 1. Derece (Normal Lineer Fit)
fit_coeffs = polyfit(nozzle_pressure, real_thrust, 1);
yeni_egim = fit_coeffs(1);
K = fit_coeffs(2);

% Çizim için hesaplanan teorik thrust değerleri
fitted_thrust = polyval(fit_coeffs, nozzle_pressure);

% --- 3. Sonuçları Grafiğe Döktürme ---
figure;
hold on;

%% scatter plot
% Map manifold_pressure (0..4570 psi) to a red-to-green colormap
cdata = manifold_pressure;
cmin = 0; cmax = 4570;
cdata_clamped = max(min(cdata, cmax), cmin);
t = (cdata_clamped - cmin) / (cmax - cmin);

% Create custom red-to-green colormap (256 entries)
nmap = 256;
rgmap = [linspace(1,0,nmap)' linspace(0,1,nmap)' zeros(nmap,1)];

% Filtrelenmiş stabil datayı çizdirme
scatter(nozzle_pressure, real_thrust, 15, t, 'filled');
colormap(rgmap);
cb = colorbar;
cb.Label.String = 'Manifold Pressure [psi] (mapped 0->4570)';
cb.Ticks = linspace(0,1,5);
cb.TickLabels = arrayfun(@(x) sprintf('%.0f', x), linspace(cmin,cmax,5), 'UniformOutput', false);
%%

% Normal lineer fit doğrusunu çizdiriyoruz (Kırmızı Düz Çizgi)
plot(nozzle_pressure, fitted_thrust, 'r-', 'LineWidth', 2);

grid on;
title(sprintf('Nozzle Pressure vs Real Thrust (1. Derece Eğim = %.4f)', yeni_egim));
ylabel('Real Thrust [N] (Kararlı Akış)');
xlabel('Nozzle Pressure [psi]');

legend('Aktif ve Kararlı Test Datası', ...
       sprintf('1. Derece Fit: F = %.4f*P + %.2f', yeni_egim, K), ...
       'Location', 'best');
hold off;

% Hesaplanan katsayıları komut penceresinde (Command Window) gösterme
fprintf('1. Derece Fit Eğimi (Cd): %f\n', yeni_egim);
fprintf('1. Derece Fit Sabiti (K): %f\n', K);
