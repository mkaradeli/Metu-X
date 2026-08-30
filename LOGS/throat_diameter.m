% Darbogaz (throat) capi hesaplama
%
% F = mdot * Ve                                     (sikisik/choked akis)
% mdot = 0.6847 * A_t * P0 / sqrt(R*T0)              (gamma=1.4 sabiti 0.6847 icinde)
% Ve   = Me * sqrt(K*R*T0 / (1 + 0.2*Me^2))          (nozzle geometrisine bagli, P0'dan bagimsiz)
% F_teorik = mdot*Ve = f(P0)                         (P0'a lineer)
% F_gercek = Cd * F_teorik
%
% Test datasindan elde edilen dF/dP0 egimi (N/psi, nozzle_pressure'a karsi
% olculen itki) ile, sabit K, R, T0, Me, Cd icin A_t (ve darbogaz capi)
% geri cozulur.

% --- Gaz sabitleri (nozzle tasarimindan bagimsiz) ---
K  = 1.4;     % ozgul isi orani
R  = 287;     % ozgul gaz sabiti [J/(kg*K)]
T0 = 300;     % stagnasyon sicakligi [K]

% --- Nozzle tasarimina bagli parametreler (tasarim degisirse guncelle) ---
Me = 3.5;      % <-- cikis Mach sayisi
Cd = 0.95;      % <-- desarj katsayisi

PSI_TO_PA = 6894.76;

% --- Test sonuclarindan elde edilen N/psi egimleri (nozzle_pressure -> itki) ---
% cdkaan.m'deki lineer fit egimleri (yeni_egim), her vana icin kendi testinden
valve_names = {'Vana 0', 'Vana 1', 'Vana 2', 'Vana 3'};
slope_N_per_psi = [0.065, 0.0845, 0.1730, 0.1763];   % <-- her vana icin kendi egimini gir

% --- Teorik akis buyuklukleri ---
Ve = Me * sqrt(K*R*T0 / (1 + 0.2*Me^2));    % [m/s], sadece Me'ye bagli
c_star_inv = 0.6847 / sqrt(R*T0);           % mdot = c_star_inv * A_t * P0

% Teorik itki egimi, birim darbogaz alani basina [N / (Pa*m^2)]
theoretical_slope_per_At = c_star_inv * Ve;

% --- Her vana icin darbogaz capini geri coz ---
slope_N_per_Pa = slope_N_per_psi / PSI_TO_PA;

A_t = slope_N_per_Pa ./ (Cd * theoretical_slope_per_At);   % [m^2]
d_bogaz_mm = sqrt(4*A_t/pi) * 1000;                          % [mm]

result = table(valve_names(:), slope_N_per_psi(:), A_t(:)*1e6, d_bogaz_mm(:), ...
	'VariableNames', {'valve', 'slope_N_per_psi', 'A_t_mm2', 'd_bogaz_mm'});
disp(result);

fprintf('\nOrtalama darbogaz capi: %.4f mm\n', mean(d_bogaz_mm, 'omitnan'));

figure;
bar(d_bogaz_mm);
set(gca, 'XTickLabel', valve_names);
grid on;
ylabel('Darbogaz Capi [mm]');
title('Test Verisinden Cikarilan Darbogaz Capi');
