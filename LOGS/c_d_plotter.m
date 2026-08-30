% 4 vana kayip orani - coklu test birlestirme
% oran = P_lule / P_manifold

sources = { ...
    'log1991.csv', 100:100:400;   ... % missionID 1 - artan profil
    'log2014.csv', 500:100:600;   ... % missionID 4 - 500 -> 800 profili
    'log2015.csv', 800:100:900;   ... % missionID 5 - 900 -> 500 profili
    'log1992.csv', 1100:100:1200};    % missionID 2 - azalan profil

nSources = size(sources, 1);

% Tum testlerden toplanan steady-state noktalari (birlesik havuz)
ratio_all       = [];
valve_angle_all = [];
lule_id_all     = [];   % hangi lule (1-4)
source_id_all   = [];   % hangi test dosyasindan geldi

for s = 1:nSources
    filename = sources{s, 1};

    dataTable = readtable(filename, 'PreserveVariableNames', true);
    headers = dataTable.Properties.VariableNames;

    manifold_pressure = dataTable{:, find(strcmp(headers, 'manifold_pressure'))};

    nozzle_pressure = zeros(height(dataTable), 4);
    valve_angle     = zeros(height(dataTable), 4);
    valve_velocity  = zeros(height(dataTable), 4);

    for i = 0:3
        nozzle_pressure(:, i+1) = dataTable{:, find(strcmp(headers, sprintf('nozzle_pressure_%d', i)))};
        valve_angle(:, i+1)     = dataTable{:, find(strcmp(headers, sprintf('valveAngle_%d', i)))};
        valve_velocity(:, i+1)  = dataTable{:, find(strcmp(headers, sprintf('valveVelocity_%d', i)))};
    end

    n = height(dataTable);
    t = (0:n-1)';   % zaman kolonu varsa: t = dataTable{:, find(strcmp(headers,'time'))};

    % --- Oran ---
    ratio = nan(n, 4);
    for i = 1:4
        ok = (manifold_pressure > 300) & (valve_angle(:,i) > 5) & (nozzle_pressure(:,i) > 0);
        ratio(ok, i) = nozzle_pressure(ok, i) ./ manifold_pressure(ok);
    end

    % --- Bu teste ait zaman grafikleri ---
    figure('Name', sprintf('%s - zaman serisi', filename));

    subplot(3,1,1);
    plot(t, manifold_pressure, 'k', 'LineWidth', 1.5); hold on;
    for i = 1:4
        plot(t, nozzle_pressure(:,i), 'LineWidth', 1);
    end
    grid on; ylabel('Basinc [psi]'); title(filename, 'Interpreter', 'none');
    legend('Manifold','Lule 0','Lule 1','Lule 2','Lule 3','Location','best');

    subplot(3,1,2);
    for i = 1:4
        plot(t, ratio(:,i), 'LineWidth', 1.2); hold on;
    end
    grid on; ylabel('P_{lule} / P_{manifold}'); ylim([0 1]);
    legend('Lule 0','Lule 1','Lule 2','Lule 3','Location','best');

    subplot(3,1,3);
    for i = 1:4
        plot(t, valve_angle(:,i), 'LineWidth', 1.2); hold on;
    end
    grid on; ylabel('Vana Acisi [deg]'); xlabel('time');
    legend('Vana 0','Vana 1','Vana 2','Vana 3','Location','best');

    % --- Steady-state noktalarini birlesik havuza ekle ---
    for i = 1:4
        steady = isfinite(ratio(:,i)) & (abs(valve_velocity(:,i)) < 30);
        k = sum(steady);
        ratio_all       = [ratio_all;       ratio(steady, i)];
        valve_angle_all = [valve_angle_all; valve_angle(steady, i)];
        lule_id_all     = [lule_id_all;     repmat(i, k, 1)];
        source_id_all   = [source_id_all;   repmat(s, k, 1)]; %#ok<AGROW>
    end
end

% --- Tum testler birlesik: Oran vs vana acisi ---
figure('Name', 'Tum testler - Oran vs Vana Acisi');
colors = lines(4);
for i = 1:4
    m = (lule_id_all == i);
    plot(valve_angle_all(m), ratio_all(m), '.', 'MarkerSize', 8, 'Color', colors(i,:)); hold on;
end
grid on; xlabel('Vana Acisi [deg]'); ylabel('P_{lule} / P_{manifold}'); ylim([0 1]);
legend('Lule 0','Lule 1','Lule 2','Lule 3','Location','best');
title('Tum test loglari birlestirilmis (log1991, log2014, log2015, log1992)');

% --- Tam acikta oran (tum testlerin birlesik verisiyle) ---
for i = 1:4
    m = (lule_id_all == i);
    thr = 0.9 * max(valve_angle_all(m));
    m_full = m & (valve_angle_all > thr);
    fprintf('Lule %d tam acik oran: %.4f\n', i-1, median(ratio_all(m_full), 'omitnan'));
end
