% Vana acikligi -> nozzle/manifold basinc orani look-up table
% Kucuk acilar log1991 (artan profil), buyuk acilar log1992 (azalan profil)
% Her iki logda da kullanilan basamaklar tank doluyken alinan ilk basamaklardir
% LUT her vana icin ayri ayri cikarilir

file_small = 'log1991.csv';
file_large = 'log1992.csv';

angles_small = 100:100:600;    % log1991'den alinacak acilar
angles_large = 700:100:1200;   % log1992'den alinacak acilar

N_VALVE     = 4;
ANGLE_TOL   =5;    % [deg]  basamak platosu toleransi
VEL_LIMIT   = 50;    % [deg/s] vana hareketsiz kabul esigi
MIN_MANIFOLD = 100;  % [psi]  bu degerin altindaki manifold verisi kullanilmaz

% --- Loglari oku ---
T_small = readtable(file_small, 'PreserveVariableNames', true);
T_large = readtable(file_large, 'PreserveVariableNames', true);

angles = [angles_small, angles_large];
source = [repmat("log1991", 1, numel(angles_small)), ...
          repmat("log1992", 1, numel(angles_large))];

n_point = numel(angles);
ratio         = zeros(n_point, N_VALVE);
nozzle_mean   = zeros(n_point, N_VALVE);
manifold_mean = zeros(n_point, N_VALVE);
sample_count  = zeros(n_point, N_VALVE);

for k = 1:n_point
	if k <= numel(angles_small)
		T = T_small;
	else
		T = T_large;
	end

	manifold = getCol(T, 'manifold_pressure');

	for v = 1:N_VALVE
		valve_angle    = getCol(T, sprintf('valveAngle_%d', v-1));
		valve_velocity = getCol(T, sprintf('valveVelocity_%d', v-1));
		nozzle         = getCol(T, sprintf('nozzle_pressure_%d', v-1));

		% Vana hedef acida, hareketsiz ve basinc verisi gecerli
		mask = (abs(valve_angle - angles(k)) < ANGLE_TOL) & ...
		       (abs(valve_velocity) < VEL_LIMIT) & ...
		       (manifold > MIN_MANIFOLD) & (nozzle > 0);

		% Bu acidaki ilk (tank en dolu) basamagi al
		seg = firstRun(mask);
		if isempty(seg)
			warning('%d deg / valf %d icin uygun veri bulunamadi.', angles(k), v-1);
			continue;
		end

		ratio(k, v)         = mean(nozzle(seg) ./ manifold(seg));
		nozzle_mean(k, v)   = mean(nozzle(seg));
		manifold_mean(k, v) = mean(manifold(seg));
		sample_count(k, v)  = numel(seg);
	end
end

% --- Look-up table (her vana icin ayri sutun) ---
LUT = [angles(:), ratio];

lut_table = table(angles(:), source(:), ratio(:,1), ratio(:,2), ratio(:,3), ratio(:,4), ...
	'VariableNames', {'valve_angle', 'log', 'ratio_0', 'ratio_1', 'ratio_2', 'ratio_3'});
disp(lut_table);

save('lookup_table.mat', 'LUT', 'lut_table', 'nozzle_mean', 'manifold_mean', 'sample_count');

idx_small = 1:numel(angles_small);
idx_large = numel(angles_small)+1 : n_point;
colors = lines(N_VALVE);

% --- Grafik 1: dort vana ayni plotta ---
figure;
hold on;
for v = 1:N_VALVE
	plot(angles, ratio(:,v), 'o-', 'LineWidth', 1.5, 'Color', colors(v,:), ...
	     'MarkerFaceColor', colors(v,:), 'DisplayName', sprintf('Vana %d', v-1));
end
grid on;
xlabel('Valve Angle [deg]');
ylabel('Nozzle / Manifold Basinc Orani');
title('Vana Acikligi Look-Up Table - Tum Vanalar');
legend('Location', 'best');
hold off;

% --- Grafik 2: her vana ayri ayri ---
figure;
for v = 1:N_VALVE
	subplot(2, 2, v);
	hold on;
	plot(angles(idx_small), ratio(idx_small,v), 'bo-', 'LineWidth', 1.5, 'MarkerFaceColor', 'b');
	plot(angles(idx_large), ratio(idx_large,v), 'rs-', 'LineWidth', 1.5, 'MarkerFaceColor', 'r');
	grid on;
	xlabel('Valve Angle [deg]');
	ylabel('Nozzle / Manifold Orani');
	title(sprintf('Vana %d', v-1));
	legend('log1991 (kucuk acilar)', 'log1992 (buyuk acilar)', 'Location', 'best');
	hold off;
end

% --- Koda gomulecek diziler ---
fprintf('\nLUT_ANGLE = [');
fprintf('%d ', angles);
fprintf('];\n');
for v = 1:N_VALVE
	fprintf('LUT_RATIO_%d = [', v-1);
	fprintf('%.5f ', ratio(:,v));
	fprintf('];\n');
end

% --- Yardimci fonksiyonlar ---
function col = getCol(T, name)
	idx = find(strcmp(T.Properties.VariableNames, name));
	col = T{:, idx};
end

function seg = firstRun(mask)
	% mask icindeki ilk kesintisiz true blogunun indisleri
	seg = [];
	d = diff([false; mask(:); false]);
	starts = find(d == 1);
	stops  = find(d == -1) - 1;
	if isempty(starts)
		return;
	end
	seg = starts(1):stops(1);
end
