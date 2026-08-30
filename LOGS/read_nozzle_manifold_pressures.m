% live_atis.csv'deki 4 nozzle basinci ve manifold basincini workspace'e cek
%
%   Bu betigi calistirdiginda su degiskenler workspace'e timeseries
%   olarak eklenir (Simulink "From Workspace" bloklarinin bekledigi format):
%     nozzle_pressure_0..3 - her vana icin nozzle basinci
%     manifold_pressure    - manifold basinci
%
%   -100..5000 psi araligi disindaki (sensor hatasi/asiri deger) noktalar
%   once NaN yapilir, sonra komsu gecerli noktalardan lineer interpolasyonla
%   doldurulur; From Workspace blogu NaN/Inf kabul etmez.
%
%   Veri, atisin baslamasindan (manifold basinci esigi asildiginda) bitmesine
%   (esigin altina dustugu son ana) kadar zaman ekseninde de kirpilir; T_START_APPROX
%   sadece atisin beklendigi yaklasik zamani isaretler, gercek baslangic/bitis
%   FIRE_PRESSURE_THRESH esigine gore otomatik bulunur.

PRESSURE_MIN = -100;   % [psi]
PRESSURE_MAX = 5000;   % [psi]

T_START_APPROX      = 103;  % [s] atisin yaklasik baslama zamani (atisin hemen oncesi)
FIRE_PRESSURE_THRESH = 50;  % [psi] manifold basinci bu esigi astiginda "atis aktif" kabul edilir

filename = fullfile(fileparts(mfilename('fullpath')), 'live_atis.csv');

T = readtable(filename, 'VariableNamingRule', 'preserve');

t_full = T.timestamp;

raw_0 = cleanPressure(T.nozzle_pressure_0, PRESSURE_MIN, PRESSURE_MAX);
raw_1 = cleanPressure(T.nozzle_pressure_1, PRESSURE_MIN, PRESSURE_MAX);
raw_2 = cleanPressure(T.nozzle_pressure_2, PRESSURE_MIN, PRESSURE_MAX);
raw_3 = cleanPressure(T.nozzle_pressure_3, PRESSURE_MIN, PRESSURE_MAX);
raw_m = cleanPressure(T.manifold_pressure, PRESSURE_MIN, PRESSURE_MAX);

% --- Atisin baslangic/bitis indekslerini bul ---
isFiring = raw_m > FIRE_PRESSURE_THRESH;

idxStart = find(t_full >= T_START_APPROX & isFiring, 1, 'first');
if isempty(idxStart)
    warning('read_nozzle_manifold_pressures:noStartFound', ...
        'T_START_APPROX civarinda esigi asan atis bulunamadi, veri kirpilmiyor.');
    idxStart = 1;
end

idxEnd = find(isFiring, 1, 'last');
if isempty(idxEnd) || idxEnd < idxStart
    idxEnd = numel(t_full);
end

idx = idxStart:idxEnd;
t   = t_full(idx) - t_full(idxStart);   % atis basiyla t = 0 olacak sekilde sifirla

raw_0 = raw_0(idx);
raw_1 = raw_1(idx);
raw_2 = raw_2(idx);
raw_3 = raw_3(idx);
raw_m = raw_m(idx);

nozzle_pressure_0 = timeseries(raw_0, t, 'Name', 'nozzle_pressure_0');
nozzle_pressure_1 = timeseries(raw_1, t, 'Name', 'nozzle_pressure_1');
nozzle_pressure_2 = timeseries(raw_2, t, 'Name', 'nozzle_pressure_2');
nozzle_pressure_3 = timeseries(raw_3, t, 'Name', 'nozzle_pressure_3');
manifold_pressure = timeseries(raw_m, t, 'Name', 'manifold_pressure');

fprintf('Loaded %d samples from %s\n', height(T), filename);
fprintf('Atis penceresi: t_full = [%.3f, %.3f] s -> kirpilmis t = [%.3f, %.3f] s (%d ornek)\n', ...
    t_full(idxStart), t_full(idxEnd), t(1), t(end), numel(idx));

figure;
plot(t, raw_0, t, raw_1, t, raw_2, t, raw_3, t, raw_m, 'LineWidth', 1.2);
grid on;
xlabel('t [s]');
ylabel('Basinc [psi]');
legend('nozzle\_0', 'nozzle\_1', 'nozzle\_2', 'nozzle\_3', 'manifold', 'Location', 'best');
title('Nozzle ve Manifold Basinclari (atis penceresi)');

clear raw_0 raw_1 raw_2 raw_3 raw_m PRESSURE_MIN PRESSURE_MAX T_START_APPROX ...
    FIRE_PRESSURE_THRESH filename T t_full isFiring idxStart idxEnd idx;

function x = cleanPressure(x, lo, hi)
    x(x < lo | x > hi) = NaN;
    if any(isnan(x))
        x = fillmissing(x, 'linear', 'EndValues', 'nearest');
    end
end
