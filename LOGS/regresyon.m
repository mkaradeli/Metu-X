% Load cell kalibrasyonu: uygulanan gercek yuk vs load cell okumasi
% 300 N noktalari haric tutuldu (gercek testte ~200 N civarina cikiyoruz)

% [uygulanan_newton, okunan_kg, okunan_newton]
% 2 counter balance
set1 = [  0,  7.67,  75.24;
        100, 26.17, 256.73;
        200, 45.16, 443.02];

% 1 counter balance, kaldiracta esneme var
set2 = [  0,  7.73,  75.83;
        100, 26.06, 255.65;
        200, 45.36, 444.98;
        300, 64.95, 637.16];

% yangin sondurme + 1 counter balance, esneme minimal
set3 = [  0,  7.80,  76.52;
        100, 26.22, 257.22;
        200, 44.98, 441.25;
        300, 64.28, 630.59];

data = [set1; set2; set3];

applied = data(:,1);
reading = data(:,3);

% --- 300 N ve uzerini disla ---
MAX_LOAD = 200;
fit_idx = applied <= MAX_LOAD;

applied_fit = applied(fit_idx);
reading_fit = reading(fit_idx);

% --- Lineer regresyon: reading = ratio * applied + offset ---
fit_coeffs = polyfit(applied_fit, reading_fit, 1);
ratio  = fit_coeffs(1);
offset = fit_coeffs(2);

% Okunan kuvveti gercek kuvvete ceviren katsayi
correction_factor = 1 / ratio;

% Fit kalitesi (R^2)
fitted = polyval(fit_coeffs, applied_fit);
residual = reading_fit - fitted;
R2 = 1 - sum(residual.^2) / sum((reading_fit - mean(reading_fit)).^2);

% --- Grafik ---
figure;
hold on;
scatter(applied_fit, reading_fit, 40, 'b', 'filled');
scatter(applied(~fit_idx), reading(~fit_idx), 40, 'k', 'x', 'LineWidth', 1.5);

p_line = linspace(0, MAX_LOAD, 100);
plot(p_line, polyval(fit_coeffs, p_line), 'r-', 'LineWidth', 2);

grid on;
xlabel('Uygulanan Yuk [N]');
ylabel('Load Cell Okumasi [N]');
title(sprintf('Load Cell Kalibrasyonu (Ratio = %.4f)', ratio));
legend('Fit Datasi (<= 200 N)', ...
       'Fit Disi (300 N)', ...
       sprintf('Lineer Fit: okuma = %.4f*F + %.2f', ratio, offset), ...
       'Location', 'best');
hold off;

% --- Sonuclar ---
fprintf('Load Cell Ratio (okuma / gercek kuvvet): %f\n', ratio);
fprintf('Offset (dara okumasi): %f N\n', offset);
fprintf('Duzeltme Katsayisi (gercek = okuma / ratio): %f\n', correction_factor);
fprintf('R^2: %f\n', R2);
