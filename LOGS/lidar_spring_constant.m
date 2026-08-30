%% Yay Sabiti (k) Hesabi
%
% Roket, itki kesildikten sonra ucunda asili oldugu esnek halat etrafinda
% sonumlu (giderek kuculen) bir salinim yapiyor. Boyle bir salinim icin
% Newton'un 2. yasasindan (m = roketin kutlesi):
%
%     m*x'' + c*x' + k*x = 0
%
% Bu sistem su ACISAL FREKANSTA (omega_n, birimi rad/s) salinir:
%
%     omega_n = sqrt(k/m)      =>      k = m * omega_n^2
%
% Yani roketin kutlesini (31.5 kg, yakitsiz) ve salinimin frekansini
% biliyorsak, yay sabitini dogrudan hesaplayabiliriz. Asagida frekansi 3
% farkli sekilde tahmin edip ucunu de karsilastiriyoruz.
%
% FFT (Hizli Fourier Donusumu) NEDIR?
% Bir sinyalin -- burada zamanla degisen yukseklik -- HANGI FREKANS(LAR)DAN
% olustugunu bulan bir yontemdir. "Bu sinyal saniyede kac kere salindi?"
% sorusunu, tepe noktalarini tek tek sayip aralarindaki zamani olcmek
% yerine, TUM sinyali bir kerede isleyerek cevaplar. Gurultulu/duzensiz
% gercek verilerde (tam bizim durumumuzda oldugu gibi) tepe-sayma
% yontemine gore cok daha guvenilirdir.

clear; clc;

FILENAME = 'live_atis.csv';
ROCKET_MASS_KG = 32;   % roketin kuru (yakitsiz) kutlesi
NOZZLE_END_PSI = 50;     % nozzle basinci bunun altina inince itki "bitti" sayilir
REST_BAND_M = 0.20;      % salinim genligi bunun altina inince "durdu" sayilir

T = readtable(FILENAME, 'PreserveVariableNames', true);
t = fixTimestamp(T.timestamp);
dt = median(diff(t(diff(t) > 0 & diff(t) < 1)));   % ornekleme araligi (~2 ms)

%% 1) Veriyi temizle
% lidar_strength'te Hampel filtresiyle (yerel medyandan asiri sapan
% ornekleri bulan bir yontem) tespit edilen bozuk ornekler, AYNI zaman
% indekslerinde lidar_height'tan da atilir.
[~, bad_strength] = hampel(T.lidar_strength, 5, 50);
height_mm = T.lidar_height;
height_mm(bad_strength) = NaN;
height_mm(height_mm > 6000) = NaN;   % fiziksel olarak imkansiz (tek ornek bit hatasi)

% Elle tespit edilen 2 kucuk (gercek salinima ait olmayan) tumsek de cikarilir.
height_mm(t >= 117.00 & t <= 117.40) = NaN;
height_mm(t >= 118.40 & t <= 118.70) = NaN;

% Itki ve nozzle basinci da ayni sekilde (Hampel ile) temizlenir.
total_thrust_N = zeros(height(T), 1);
max_nozzle_psi = zeros(height(T), 1);
for i = 0:3
	total_thrust_N = total_thrust_N + hampel(T.(sprintf('thrust_estimated_%d', i)), 5, 50);
	max_nozzle_psi = max(max_nozzle_psi, hampel(T.(sprintf('nozzle_pressure_%d', i)), 5, 50));
end

%% 2) Itkinin ne zaman kesildigini bul
% Once itkinin gercekten BASLADIGI an bulunur -- yoksa "itki~0" kosulu
% atistan ONCEKI bekleme suresinde de (yanlislikla) saglanir.
shot_start_idx = find(max_nozzle_psi > 100, 1, 'first');
after_shot = t > t(shot_start_idx);
thrust_off = after_shot & abs(total_thrust_N) < 0.05 * max(abs(total_thrust_N)) & max_nozzle_psi < NOZZLE_END_PSI;
cutoff_idx = firstSustained(thrust_off, round(0.05 / dt));
fprintf('Itki t=%.2fs''de basliyor, t=%.2fs''de kesiliyor.\n', t(shot_start_idx), t(cutoff_idx));

%% 3) Kesilme sonrasi salinimin tepe noktalarini bul
rest_height_mm = median(height_mm(t < t(shot_start_idx) - 1), 'omitnan');   % itkisiz dinlenme yuksekligi

window_idx = cutoff_idx:min(numel(t), cutoff_idx + round(30 / dt));   % kesilmeden sonraki 30 saniye
h_window = fillmissing(height_mm(window_idx), 'linear', 'EndValues', 'nearest');

[peak_vals_mm, peak_locs] = findpeaks(h_window, ...
	'MinPeakDistance', round(0.5 / dt), 'MinPeakProminence', 30);
peak_times = t(window_idx(1) - 1 + peak_locs);

% Sadece denge seviyesinin USTUNDEKI gercek tepeleri tut, ve genligi
% REST_BAND_M'nin altina inen ilk tepeden sonrasini (artik "durdu" sayilan
% kismi) at.
above_rest = peak_vals_mm > rest_height_mm;
peak_vals_mm = peak_vals_mm(above_rest);
peak_times = peak_times(above_rest);
amp_m = (peak_vals_mm - rest_height_mm) / 1000;
last_valid = find(amp_m > REST_BAND_M, 1, 'last');
peak_vals_mm = peak_vals_mm(1:last_valid);
peak_times = peak_times(1:last_valid);

fprintf('\nKullanilan %d salinim tepesi:\n', numel(peak_times));
for i = 1:numel(peak_times)
	fprintf('  t=%.3fs  h=%.1fmm\n', peak_times(i), peak_vals_mm(i));
end

%% 4) Frekansi (omega_n) 3 farkli sekilde tahmin et
% (a) sadece ILK 2 tepe (bir periyot yeter)
omega_first2 = 2 * pi / (peak_times(2) - peak_times(1));

% (b) TUM tepelerin ortalama araligi
omega_allpeaks = 2 * pi / mean(diff(peak_times));

% (c) FFT: sinyali denge etrafinda duzlestirip hangi frekansta en guclu
% oldugunu buluyoruz (bkz. yukaridaki "FFT nedir" aciklamasi).
h_seg = fillmissing(height_mm(cutoff_idx:window_idx(end)), 'linear', 'EndValues', 'nearest');
h_seg = detrend(h_seg - rest_height_mm, 'linear');
spectrum = abs(fft(h_seg .* hann(numel(h_seg)), 4 * numel(h_seg)));
freqs = (1 / dt) * (0:numel(spectrum) - 1)' / numel(spectrum);
half = 1:floor(numel(spectrum) / 2);
[~, i_peak] = max(spectrum(half));
omega_fft = 2 * pi * freqs(i_peak);

%% 5) Yay sabiti: k = m * omega_n^2
k_first2 = ROCKET_MASS_KG * omega_first2^2;
k_allpeaks = ROCKET_MASS_KG * omega_allpeaks^2;
k_fft = ROCKET_MASS_KG * omega_fft^2;

fprintf('\n--- Sonuclar: k = m * omega_n^2  (m = %.1f kg) ---\n', ROCKET_MASS_KG);
fprintf('ilk 2 tepe  : omega_n = %.3f rad/s  ->  k = %.1f N/m\n', omega_first2, k_first2);
fprintf('tum tepeler : omega_n = %.3f rad/s  ->  k = %.1f N/m\n', omega_allpeaks, k_allpeaks);
fprintf('FFT         : omega_n = %.3f rad/s  ->  k = %.1f N/m\n', omega_fft, k_fft);

%% Gorsellestirme
figure;
plot(t(cutoff_idx:window_idx(end)), height_mm(cutoff_idx:window_idx(end)), '.-'); hold on;
plot(peak_times, peak_vals_mm, 'rv', 'MarkerFaceColor', 'r');
yline(rest_height_mm, '--k', 'denge');
grid on;
xlabel('time [s]'); ylabel('Lidar Height [mm]');
title(sprintf('k = %.1f N/m (tum tepeler ile, m = %.1f kg)', k_allpeaks, ROCKET_MASS_KG));
legend('lidar height (temizlenmis)', 'tepe noktalari', 'Location', 'best');

exportgraphics(gcf, 'lidar_spring_constant.png', 'Resolution', 130);

%% ==================== Yardimci fonksiyonlar ====================

function t_fixed = fixTimestamp(t)
	% Dosyada tek bir satirin zaman damgasi bozuk (ör. 209.27s -> -414.02s
	% -> 210.20s: sadece ortadaki deger yanlis, bir sonraki satir dogru
	% yerden devam ediyor). Bu tek ornek, komsularina bakilarak interpole
	% edilir.
	t_fixed = t;
	d = diff(t_fixed);
	normal_dt = median(d(d > 0 & d < 1));
	bad_rows = find(d < 0)';
	for i = bad_rows
		t_fixed(i + 1) = t_fixed(i) + normal_dt;
	end
end

function idx = firstSustained(cond, min_run_length)
	% cond (mantiksal dizi) icinde en az min_run_length ornek boyunca
	% KESINTISIZ dogru kalan ilk bolgenin BASLANGIC indeksini dondurur.
	% (Tek bir ornekluk gurultu/bozuk veriyi "kalici degisim" sanmamak icin.)
	run_length = movsum(double(cond), [min_run_length - 1, 0]);
	last_of_run = find(run_length >= min_run_length, 1, 'first');
	idx = last_of_run - min_run_length + 1;
end
