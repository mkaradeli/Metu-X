%% Nozzle Verimliligi: Itki Impulsu Karsilastirmasi
%
% AMAC: Ayni test standinda, farkli capta 3 nozzle (4.7mm, 2.8mm, 3.2mm)
% "tam acik" (valf sonuna kadar acilip sabit tutulmus) halde test edilmis.
% Hangi nozzle'in depolanan basinc enerjisini itkiye en verimli cevirdigini
% anlamak icin, her testin tam-acik penceresindeki toplam IMPULS'u (kuvvetin
% zaman uzerinden integrali) karsilastiriyoruz.
%
% MATEMATIKSEL ACIKLAMA
% ----------------------
% Impuls, kuvvetin zaman uzerinden integralidir:
%
%     J = integral( F(t) dt )      [N*s]
%
% Newton'un 2. yasasindan (F = dp/dt, p = momentum) impuls, sisteme
% aktarilan TOPLAM MOMENTUM DEGISIMINE esittir: J = Delta(m*v). Roket
% motorlari icin bu, "ne kadar gaz harcandi" ile "o gaz ne kadar hizli
% firlatildi" carpiminin bir olcusudur: J = m_gaz * v_ekzoz_efektif.
%
% ADIL KARSILASTIRMA: AYNI MIKTAR GAZ
% ------------------------------------
% Impuslu doğru karsilastirmak icin, ayni miktarda gaz (m_gaz) harcanmis
% olmasi gerekir -- yoksa daha uzun sure/daha fazla gaz kullanan bir test
% haksiz yere daha yuksek impuls gosterir. manifold_pressure, tanktaki
% kalan gazin dolayli bir olcusudur, o yuzden:
%
%   1) Her testin "tam acik" penceresi sonundaki manifold basincina bakilir.
%   2) Bu 3 deger arasindaki EN YUKSEK olan (= en AZ gaz harcanan test)
%      referans alinir.
%   3) Butun testler, manifold basinci bu referans seviyesine ilk
%      dustugu ana kadar KESILIR -- yani hepsi ayni miktarda gaz
%      harcanmis olacak sekilde karsilastirilir.
%
% Bu sekilde, DAHA YUKSEK IMPULS ureten nozzle, AYNI miktardaki gazi DAHA
% YUKSEK bir ekzoz hizina cevirmis demektir -- yani basinc enerjisini
% itkiye daha verimli aktarmistir (standart "ozgul impuls" Isp=J/(m_gaz*g)
% mantiginin, gaz kutlesini olcmeden yapilan pratik bir uygulamasi).
%
% "TAM ACIK" PENCERESI NASIL BULUNUYOR?
% Her testte valveAngle_0, komut edilen pozisyona (~1080) ulasip orada
% (PID ile) sabit kaliyor. Impuls SADECE bu "tam acik ve sabit" pencerede
% (ve yukaridaki adil-kesme kuraliyla) hesaplanir.

clear; clc;

FILES = {'log2003.csv', 'log2232.csv', 'log2238.csv'};
NOZZLE_MM = [4.7, 2.8, 3.2];
KGF_TO_N = 9.80665;   % thrust_measured kgf cinsinden -> N

n = numel(FILES);

%% 1. gecis: her testin verisini yukle, "tam acik" penceresini bul
t_all = cell(n, 1);
force_all = cell(n, 1);
manifold_all = cell(n, 1);
open_idx_all = zeros(n, 1);
close_idx_all = zeros(n, 1);
final_manifold_psi = zeros(n, 1);

for k = 1:n
	T = readtable(FILES{k}, 'PreserveVariableNames', true);
	t_all{k} = T.timestamp;
	force_all{k} = KGF_TO_N * T.thrust_measured / 1.8361;
	manifold_all{k} = T.manifold_pressure;

	% "Tam acik" penceresi: valveAngle_0 kendi tepe degerinin en az
	% %90'ina ulastigi ilk ve son an arasi.
	is_open = T.valveAngle_0 > 0.90 * max(T.valveAngle_0);
	open_idx_all(k) = find(is_open, 1, 'first');
	close_idx_all(k) = find(is_open, 1, 'last');

	% Penceresinin son ~0.2s'sindeki manifold basincinin MEDYANI: tek bir
	% son ornege bakmak yerine (o ornek bozuk/gurultulu cikabilir), kisa
	% bir pencerenin medyanini kullanmak daha guvenilir.
	dt_k = median(diff(t_all{k}(1:1000)));
	tail_len = round(0.2 / dt_k);
	tail = manifold_all{k}(max(1, close_idx_all(k) - tail_len):close_idx_all(k));
	final_manifold_psi(k) = median(tail);

	fprintf('%-14s (%.1fmm nozzle): tam acik t=%.2f-%.2fs, bitisteki manifold basinci ~ %.0f psi\n', ...
		FILES{k}, NOZZLE_MM(k), t_all{k}(open_idx_all(k)), t_all{k}(close_idx_all(k)), final_manifold_psi(k));
end

%% 2. gecis: adil kesme seviyesini uygula (en yuksek bitis basincina kadar)
ref_level_psi = max(final_manifold_psi);
[~, ref_k] = max(final_manifold_psi);
fprintf('\nReferans seviyesi (en az gaz harcanan test, %.1fmm nozzle): %.0f psi\n', NOZZLE_MM(ref_k), ref_level_psi);
fprintf('-> Butun testler, manifold basinci bu seviyeye kalici olarak dustugu ana kadar kesiliyor.\n\n');

PERSIST_S = 0.05;   % kalicilik suresi: tek ornekluk bozuk bir dususu "vardik" sanmamak icin

impulse_Ns = zeros(n, 1);
mean_force_N = zeros(n, 1);
fair_duration_s = zeros(n, 1);
fair_seg = cell(n, 1);

figure;
tiledlayout(n, 1);

for k = 1:n
	t = t_all{k};
	dt_k = median(diff(t(1:1000)));
	persist_samples = round(PERSIST_S / dt_k);

	from_open = manifold_all{k}(open_idx_all(k):end) <= ref_level_psi;
	fair_close_idx = open_idx_all(k) - 1 + firstSustained(from_open, persist_samples);

	seg = open_idx_all(k):fair_close_idx;
	fair_seg{k} = seg;

	impulse_Ns(k) = trapz(t(seg), force_all{k}(seg));
	mean_force_N(k) = mean(force_all{k}(seg));
	fair_duration_s(k) = t(fair_close_idx) - t(open_idx_all(k));

	fprintf('%-14s (%.1fmm nozzle): adil pencere t=%.2f-%.2fs (%.2fs), ort. kuvvet=%.1fN, impuls J=%.1f N*s\n', ...
		FILES{k}, NOZZLE_MM(k), t(open_idx_all(k)), t(fair_close_idx), fair_duration_s(k), mean_force_N(k), impulse_Ns(k));

	nexttile;
	plot(t(seg), force_all{k}(seg));
	grid on;
	xlabel('time [s]'); ylabel('Force [N]');
	title(sprintf('%.1fmm nozzle (%s): J = %.1f N*s', NOZZLE_MM(k), FILES{k}, impulse_Ns(k)));
	ylim([0, max(force_all{k}(seg)) * 1.05]);
end

%% Ozet ve karsilastirma
fprintf('\n--- OZET: Nozzle Impuls Karsilastirmasi (adil kesme ile) ---\n');
[~, order] = sort(impulse_Ns, 'descend');
for i = 1:n
	k = order(i);
	fprintf('%d) %.1fmm nozzle  ->  J = %.1f N*s  (ort. %.1f N, %.2fs)\n', ...
		i, NOZZLE_MM(k), impulse_Ns(k), mean_force_N(k), fair_duration_s(k));
end
fprintf('\n==> En yuksek impuls -> en verimli nozzle: %.1fmm\n', NOZZLE_MM(order(1)));

exportgraphics(gcf, 'nozzle_impulse_comparison.png', 'Resolution', 130);

%% Manifold basinci karsilastirmasi (ayri sekme/figur, ayni adil pencere ile)
figure;
hold on;
for k = 1:n
	t = t_all{k};
	seg = fair_seg{k};
	plot(t(seg) - t(seg(1)), manifold_all{k}(seg), 'DisplayName', sprintf('%.1fmm nozzle (%s)', NOZZLE_MM(k), FILES{k}));
end
hold off;
grid on;
xlabel('tam acik baslangicina gore zaman [s]'); ylabel('Manifold Pressure [psi]');
title('3 Testin Manifold Basinci Karsilastirmasi (adil kesme ile)');
legend('Location', 'best');

exportgraphics(gcf, 'nozzle_manifold_comparison.png', 'Resolution', 130);

%% ==================== Yardimci fonksiyon ====================

function idx = firstSustained(cond, min_run_length)
	% cond (mantiksal dizi) icinde en az min_run_length ornek boyunca
	% KESINTISIZ dogru kalan ilk bolgenin SON indeksini (yani kosulun
	% kalici olarak saglandigi ilk anin kendisini) dondurur.
	run_length = movsum(double(cond), [min_run_length - 1, 0]);
	idx = find(run_length >= min_run_length, 1, 'first');
end
