% Iki test profilinin manifold/nozzle basinc oranini ust uste cizdirme
% log1991: artan aci profili, log1992: azalan aci profili

file_1 = 'log1991.csv';
file_2 = 'log1992.csv';

N_VALVE      = 4;
VEL_LIMIT    = 30;   % [deg/s] vana hareketsiz kabul esigi
MIN_ANGLE    = 50;   % [deg]   vana kapaliyken veri alinmaz
MIN_MANIFOLD = 100;  % [psi]
MIN_NOZZLE   = 20;   % [psi]   sifira bolme patlamasini engeller

T1 = readtable(file_1, 'PreserveVariableNames', true);
T2 = readtable(file_2, 'PreserveVariableNames', true);

[angle_1, ratio_1] = pressureRatio(T1, N_VALVE, VEL_LIMIT, MIN_ANGLE, MIN_MANIFOLD, MIN_NOZZLE);
[angle_2, ratio_2] = pressureRatio(T2, N_VALVE, VEL_LIMIT, MIN_ANGLE, MIN_MANIFOLD, MIN_NOZZLE);

figure;
hold on;
scatter(ratio_1, angle_1, 12, 'b', 'filled');
scatter(ratio_2, angle_2, 12, 'r', 'filled');

grid on;
xlabel('Manifold / Nozzle Basinc Orani');
ylabel('Valve Angle [deg]');
title('Basinc Orani - Iki Test Profili');
legend('log1991 (artan profil)', 'log1992 (azalan profil)', 'Location', 'best');
hold off;

% --- Yardimci fonksiyonlar ---
function col = getCol(T, name)
	idx = find(strcmp(T.Properties.VariableNames, name));
	col = T{:, idx};
end

function [angle_out, ratio_out] = pressureRatio(T, N_VALVE, VEL_LIMIT, MIN_ANGLE, MIN_MANIFOLD, MIN_NOZZLE)
	manifold = getCol(T, 'manifold_pressure');

	angle_out = [];
	ratio_out = [];

	for v = 1:N_VALVE
		valve_angle    = getCol(T, sprintf('valveAngle_%d', v-1));
		valve_velocity = getCol(T, sprintf('valveVelocity_%d', v-1));
		nozzle         = getCol(T, sprintf('nozzle_pressure_%d', v-1));

		mask = (abs(valve_velocity) < VEL_LIMIT) & (valve_angle > MIN_ANGLE) & ...
		       (manifold > MIN_MANIFOLD) & (nozzle > MIN_NOZZLE);

		angle_out = [angle_out; valve_angle(mask)];
		ratio_out = [ratio_out; manifold(mask) ./ nozzle(mask)];
	end
end
