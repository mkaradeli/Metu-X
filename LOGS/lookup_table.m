% Vana acikligi -> nozzle/manifold basinc orani look-up table
% Her aci grubu, o acinin tank doluyken alindigi testten cekilir
% LUT her vana icin ayri ayri cikarilir

% {log dosyasi, o logdan alinacak acilar}
sources = { ...
	'log1991.csv', 100:100:400;   ... % missionID 1 - artan profil
	'log2014.csv', 500:100:600;   ... % missionID 4 - 500 -> 800 profili
	'log2015.csv', 800:100:900;   ... % missionID 5 - 900 -> 500 profili
	'log1992.csv', 1100:100:1200};    % missionID 2 - azalan profil

N_VALVE     = 4;
ANGLE_TOL   =5;    % [deg]  basamak platosu toleransi
VEL_LIMIT   = 50;    % [deg/s] vana hareketsiz kabul esigi
MIN_MANIFOLD = 100;  % [psi]  bu degerin altindaki manifold verisi kullanilmaz

% --- Loglari oku ve aci listesini olustur ---
n_group = size(sources, 1);
T_all   = cell(n_group, 1);
angles   = [];
source   = strings(0, 1);
group_of = [];

for g = 1:n_group
	T_all{g} = readtable(sources{g,1}, 'PreserveVariableNames', true);
	a = sources{g,2};
	angles   = [angles, a];
	source   = [source; repmat(string(sources{g,1}), numel(a), 1)];
	group_of = [group_of, repmat(g, 1, numel(a))];
end

n_point = numel(angles);
ratio         = zeros(n_point, N_VALVE);
ratio_std     = zeros(n_point, N_VALVE);
nozzle_mean   = zeros(n_point, N_VALVE);
manifold_mean = zeros(n_point, N_VALVE);
sample_count  = zeros(n_point, N_VALVE);

for k = 1:n_point
	T = T_all{group_of(k)};

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
		ratio_std(k, v)     = std(nozzle(seg) ./ manifold(seg));
		nozzle_mean(k, v)   = mean(nozzle(seg));
		manifold_mean(k, v) = mean(manifold(seg));
		sample_count(k, v)  = numel(seg);
	end
end

% --- Monoton artan hale getirme (agirlikli izotonik regresyon / PAVA) ---
% Olculen oranlar hicbir noktada bir oncekinin altina dusmemeli
ratio_mono = zeros(n_point, N_VALVE);
for v = 1:N_VALVE
	w = sample_count(:,v);
	w(w == 0) = 1;
	ratio_mono(:,v) = isotonicFit(ratio(:,v), w);
end

% --- Look-up table (her vana icin ayri sutun) ---
LUT = [angles(:), ratio_mono];

lut_table = table(angles(:), source(:), ...
	ratio(:,1), ratio(:,2), ratio(:,3), ratio(:,4), ...
	ratio_mono(:,1), ratio_mono(:,2), ratio_mono(:,3), ratio_mono(:,4), ...
	'VariableNames', {'valve_angle', 'log', 'ratio_0', 'ratio_1', 'ratio_2', 'ratio_3', ...
	                  'mono_0', 'mono_1', 'mono_2', 'mono_3'});
disp(lut_table);

save('lookup_table.mat', 'LUT', 'lut_table', 'ratio', 'ratio_mono', 'ratio_std', ...
     'nozzle_mean', 'manifold_mean', 'sample_count');

colors = lines(N_VALVE);
group_colors = lines(n_group);

% --- Grafik 1: dort vana ayni plotta ---
figure;
hold on;
for v = 1:N_VALVE
	plot(angles, ratio_mono(:,v), 'o-', 'LineWidth', 1.5, 'Color', colors(v,:), ...
	     'MarkerFaceColor', colors(v,:), 'DisplayName', sprintf('Vana %d', v-1));
end
grid on;
xlabel('Valve Angle [deg]');
ylabel('Nozzle / Manifold Basinc Orani');
title('Vana Acikligi Look-Up Table - Tum Vanalar');
legend('Location', 'best');
hold off;

% --- Grafik 2: her vana ayri figurde ---
for v = 1:N_VALVE
	figure;
	hold on;
	for g = 1:n_group
		idx = (group_of == g);
		errorbar(angles(idx), ratio(idx,v), ratio_std(idx,v), 'o', ...
		     'LineWidth', 1.5, 'MarkerSize', 7, 'CapSize', 8, ...
		     'Color', group_colors(g,:), 'MarkerFaceColor', group_colors(g,:), ...
		     'DisplayName', sources{g,1});
	end
	plot(angles, ratio_mono(:,v), 'k-', 'LineWidth', 1.5, ...
	     'DisplayName', 'Monoton LUT');
	grid on;
	xlabel('Valve Angle [deg]');
	ylabel('Nozzle / Manifold Basinc Orani');
	title(sprintf('Vana Acikligi Look-Up Table - Vana %d', v-1));
	legend('Location', 'best');
	hold off;
end

% --- Koda gomulecek diziler ---
fprintf('\nLUT_ANGLE = [');
fprintf('%d ', angles);
fprintf('];\n');
for v = 1:N_VALVE
	fprintf('LUT_RATIO_%d = [', v-1);
	fprintf('%.5f ', ratio_mono(:,v));
	fprintf('];\n');
end

% --- Yardimci fonksiyonlar ---
function col = getCol(T, name)
	idx = find(strcmp(T.Properties.VariableNames, name));
	col = T{:, idx};
end

function y = isotonicFit(x, w)
	% PAVA (pool adjacent violators): monoton artan en kucuk kareler cozumu
	% Ihlal eden komsu noktalar agirlikli ortalamalari ile birlestirilir
	n = numel(x);
	val = zeros(n,1); wt = zeros(n,1); last = zeros(n,1);
	j = 0;
	for i = 1:n
		j = j + 1;
		val(j)  = x(i);
		wt(j)   = w(i);
		last(j) = i;
		while j > 1 && val(j) < val(j-1)
			val(j-1)  = (wt(j-1)*val(j-1) + wt(j)*val(j)) / (wt(j-1) + wt(j));
			wt(j-1)   = wt(j-1) + wt(j);
			last(j-1) = last(j);
			j = j - 1;
		end
	end
	y = zeros(n,1);
	first = 1;
	for b = 1:j
		y(first:last(b)) = val(b);
		first = last(b) + 1;
	end
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
