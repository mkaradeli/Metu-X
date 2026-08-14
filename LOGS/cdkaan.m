% Define the filename
filename = 'log1247.csv';
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

manifold_pressure_bar = manifold_pressure * 0.0689476;
max_angle = max(valve_angle);
fprintf('Maksimum Valf Açısı: %f\n', max_angle);

% Orijinal denklemi hiç değiştirmeden dönüştürülmüş bar verisiyle çalıştırıyoruz
m_air = 1.6184 * 0.009 + (((299.24 * 0.009)-1.6184 * 0.009)/(300-1.035)) * (manifold_pressure_bar - 1.035);
m_air_force = m_air * 9.81;
thrust_newton = thrust_kg * 9.81;

% Havanın kütlesi çıkarılmış ham itki
without_air_thrust = thrust_newton - m_air_force;

figure
plot(without_air_thrust)

%% --- 1. DARA (TARE) İŞLEMİ ---
tare_idx = valve_angle <= 5;

tare_offset = mean(without_air_thrust(tare_idx));

real_thrust = without_air_thrust - tare_offset;
figure
plot(real_thrust)

% --- 2. PLOT VE FİT İÇİN AKTİF VE STABİL DATAYI AYIRMA ---

plot_idx = (~tare_idx) & valve_velocity <= 40;

% Sadece stabil aktif test verilerini filtreleme
nozzle_pressure = nozzle_pressure(plot_idx);
manifold_pressure_bar = manifold_pressure_bar(plot_idx);
real_thrust = real_thrust(plot_idx);


% --- 3. Lineer ve Polinom Fit İşlemleri ---
% 1. Derece (Normal Lineer Fit)
fit_coeffs = polyfit(nozzle_pressure, real_thrust, 1);
yeni_egim = fit_coeffs(1); 
K = fit_coeffs(2);         

% 1. Derece (Orijinden Geçen K=0 Fit)
yeni_egim_K0 = nozzle_pressure(:) \ real_thrust(:);

% 2. Derece (Kuadratik Polinom Fit)
fit_coeffs_2 = polyfit(nozzle_pressure, real_thrust, 2);

% Çizim için hesaplanan teorik thrust değerleri
fitted_thrust = polyval(fit_coeffs, nozzle_pressure);
fitted_thrust_K0 = yeni_egim_K0 * nozzle_pressure; 

% 2. derece eğrinin pürüzsüz çizilmesi için sıralı X (basınç) noktaları oluşturuyoruz
p_line = linspace(min(nozzle_pressure), max(nozzle_pressure), 100);
fitted_thrust_poly2 = polyval(fit_coeffs_2, p_line);

% --- 4. Sonuçları Grafiğe Döktürme ---
figure;
hold on;

%% scatter plot
% Map manifold_pressure (0..315) to a red-to-green colormap
cdata = manifold_pressure_bar;         
cmin = 0; cmax = 315;
cdata_clamped = max(min(cdata, cmax), cmin);
t = (cdata_clamped - cmin) / (cmax - cmin);

% Create custom red-to-green colormap (256 entries)
nmap = 256;
rgmap = [linspace(1,0,nmap)' linspace(0,1,nmap)' zeros(nmap,1)];

% Filtrelenmiş stabil datayı çizdirme
scatter(nozzle_pressure, real_thrust, 15, t, 'filled');
colormap(rgmap);
cb = colorbar;
cb.Label.String = 'Manifold Pressure (mapped 0->315)';
cb.Ticks = linspace(0,1,5);
cb.TickLabels = arrayfun(@(x) sprintf('%.0f', x), linspace(cmin,cmax,5), 'UniformOutput', false);
%%

% Normal lineer fit doğrusunu çizdiriyoruz (Kırmızı Düz Çizgi)
plot(nozzle_pressure, fitted_thrust, 'r-', 'LineWidth', 2); 

% Orijinden zorla geçirilen (K=0) fit doğrusunu çizdiriyoruz (Siyah Kesik Çizgi)
plot(nozzle_pressure, fitted_thrust_K0, 'k--', 'LineWidth', 2); 

% 2. Derece Polinom fit eğrisini çizdiriyoruz (Magenta Kesik-Noktalı Çizgi)
plot(p_line, fitted_thrust_poly2, 'm-.', 'LineWidth', 2);

grid on;
title(sprintf('Nozzle Pressure vs Real Thrust (1. Derece Eğim = %.4f)', yeni_egim));
ylabel('Real Thrust (Tare Alınmış, Kararlı Akış)');
xlabel('Nozzle Pressure');

% Legend'a 2. Derece fitini de ekledik
legend('Aktif ve Kararlı Test Datası', ...
       sprintf('1. Derece Fit: F = %.4f*P + %.2f', yeni_egim, K), ...
       sprintf('K=0 Fiti: F = %.4f*P', yeni_egim_K0), ...
       sprintf('2. Derece Fit: F = %.5f*P^2 + %.4f*P + %.2f', fit_coeffs_2(1), fit_coeffs_2(2), fit_coeffs_2(3)), ...
       'Location', 'best');
hold off;

% Hesaplanan katsayıları komut penceresinde (Command Window) gösterme
fprintf('Hesaplanan Ortalama Dara (Tare Offset): %f N\n', tare_offset);
fprintf('1. Derece Fit Eğimi (Cd): %f\n', yeni_egim);
fprintf('1. Derece Fit Sabiti (K): %f\n', K);
fprintf('K=0 Fit Eğimi: %f\n', yeni_egim_K0);
fprintf('2. Derece Fit Katsayıları: a=%f, b=%f, c=%f\n', fit_coeffs_2(1), fit_coeffs_2(2), fit_coeffs_2(3));