% =========================================================================
%  LULE PARAMETRELERININ TAMAMEN TEST DATASINDAN COZULMESI
%
%  Kullanilan denklemler (el yazisi notundaki):
%     mdot = 0.6847 * A_t * P0 / sqrt(R*T0)
%     Ve   = Me * sqrt(k*R*T0 / (1 + 0.2*Me^2))
%     F    = Cd * mdot * Ve   (+ basinc itkisi)
%
%  VARSAYILAN HICBIR SAYI YOK. Sadece:
%     - gaz ozellikleri (k, R)  -> hava, tasarim parametresi degil
%     - tank hacmi              -> olculebilir geometri
%     - ortam sicakligi         -> termometre
%
%  COZULEN:
%     Cd_m * A_bogaz   (etkin bogaz alani)  <- kutle dengesinden
%     Cd_F * Ve        (etkin egzoz hizi)   <- itkiden
%     Me, A_cikis                           <- ikisinin birlesiminden
% =========================================================================

clear; clc; close all;

%% ================= GIRDILER ============================================
LOGS = {'log1991.csv', 'log1992.csv'};   % .bin -> CSV export
N_NOZZLES = [1, 4];                      % her log'da kac lule akiyordu

k = 1.4;                % hava
R = 287;                % [J/kgK]
V_TANK = 9e-3;          % [m^3]  <-- su ile doldurup dogrula
T_AMB = 293;            % [K]    <-- test gunu ortam sicakligi, OLC
P_ATM = 101325;         % [Pa]
PSI2PA = 6894.76;

LOADCELL_RATIO = 1.8361;

% Tanki tarttiysan buraya yaz, termodinamik varsayim devre disi kalir.
% [] birakirsan izentropik/izotermal arasi bant hesaplanir.
DM_WEIGHED = { [], [] };     % [kg] her log icin

CHOKED = sqrt(k) * (2/(k+1))^((k+1)/(2*(k-1)));   % 0.6847

results = struct([]);

%% ================= HER LOG ICIN COZUM ==================================
for L = 1:numel(LOGS)

    T = readtable(LOGS{L}, 'PreserveVariableNames', true);
    h = T.Properties.VariableNames;
    has = @(n) any(strcmp(h, n));
    col = @(n) T{:, strcmp(h, n)};

    N = N_NOZZLES(L);
    fprintf('\n########## %s  (%d lule) ##########\n', LOGS{L}, N);

    % --- zaman ---
    tname = '';
    for c = {'time','timestamp','t','time_us'}
        if has(c{1}), tname = c{1}; break; end
    end
    t = col(tname);
    if max(t) > 1e5, t = (t - t(1))/1e6; else, t = t - t(1); end

    % --- tank / manifold basinci ---
    if has('tank_pressure')
        P_up = col('tank_pressure') * PSI2PA;
        src = 'tank';
    else
        P_up = col('manifold_pressure') * PSI2PA;
        src = 'manifold';
    end
    fprintf('Yukari akis basinci kanali: %s\n', src);

    % --- lule basinclari (aktif olanlarin TOPLAMI gerekiyor) ---
    Psum = zeros(height(T), 1);
    Pn = cell(N,1);
    for i = 0:N-1
        Pn{i+1} = col(sprintf('nozzle_pressure_%d', i)) * PSI2PA;
        Psum = Psum + Pn{i+1};
    end

    % --- vana acisi ---
    ang = col('valveAngle_0');

    % --- akis penceresi ---
    act = (ang > 5) & (Psum > 100*PSI2PA);
    i0 = find(act, 1, 'first');
    i1 = find(act, 1, 'last');
    seg = i0:i1;

    %% ---------- 1) ETKIN BOGAZ ALANI --------------------------------
    % Tank durumu: P(t) -> m(t).  n = 1/k (izentropik) ... 1 (izotermal)
    m0_ideal = P_up(i0) * V_TANK / (R * T_AMB);
    Z = 1 + 1.7e-9 * P_up(i0);          % kaba sikistirilabilirlik
    m0 = m0_ideal / Z;

    Pr = P_up / P_up(i0);

    cases = struct('name', {'izentropik','izotermal'}, ...
                   'n',    {1/k, 1}, ...
                   'Texp', {(k-1)/k, 0});

    A_range = zeros(1,2);
    for c = 1:2
        m_t  = m0 * Pr.^cases(c).n;
        dm   = m_t(i0) - m_t(i1);
        T0_t = T_AMB * Pr.^cases(c).Texp;

        I = trapz(t(seg), Psum(seg) ./ sqrt(T0_t(seg)));
        A_range(c) = dm * sqrt(R) / (CHOKED * I);

        fprintf('  %-12s : dm = %.3f kg -> A_t = %.4e m^2, d_t = %.3f mm\n', ...
                cases(c).name, dm, A_range(c), 2000*sqrt(A_range(c)/pi));
    end

    % Tartim varsa tek degere in
    if ~isempty(DM_WEIGHED{L})
        dm = DM_WEIGHED{L};
        T0_t = T_AMB * Pr.^((k-1)/k);      % sicaklik icin yine izentropik
        I = trapz(t(seg), Psum(seg) ./ sqrt(T0_t(seg)));
        A_throat = dm * sqrt(R) / (CHOKED * I);
        fprintf('  TARTIM       : dm = %.3f kg -> d_t = %.3f mm  <-- KULLANILAN\n', ...
                dm, 2000*sqrt(A_throat/pi));
    else
        A_throat = mean(A_range);
        T0_t = T_AMB * Pr.^((k-1)/k);
        fprintf('  --> orta deger kullaniliyor, belirsizlik %%%.1f\n', ...
                100*(sqrt(A_range(2))-sqrt(A_range(1)))/sqrt(A_throat));
    end

    d_throat = 2000 * sqrt(A_throat/pi);

    %% ---------- 2) ITKI VARSA: Me VE CIKIS ALANI ---------------------
    Me = NaN; d_exit = NaN; Cd_est = NaN;

    if has('thrust_measured')
        F_tot = col('thrust_measured') * 9.81 / LOADCELL_RATIO;

        % Anlik toplam debi (cozulen A_t ile)
        mdot = CHOKED * A_throat * Psum ./ sqrt(R * T0_t);

        ok = act & (F_tot > 1) & (Psum > 300*PSI2PA*N);
        Ve_eff = F_tot(ok) ./ mdot(ok);          % = Cd * Ve

        % Me'yi Ve'den coz:  Me^2 = Ve^2 / (k*R*T0 - 0.2*Ve^2)
        T0s = T0_t(ok);
        Me_t = sqrt(Ve_eff.^2 ./ (k*R*T0s - 0.2*Ve_eff.^2));

        Me = median(Me_t, 'omitnan');
        eps_ratio = (1/Me) * ((1 + 0.2*Me^2)/1.2)^3;
        d_exit = d_throat * sqrt(eps_ratio);

        fprintf('\n  Etkin egzoz hizi : %.1f m/s\n', median(Ve_eff,'omitnan'));
        fprintf('  Cozulen Me       : %.3f  (std %%%.1f)\n', ...
                Me, 100*std(Me_t,'omitnan')/Me);
        fprintf('  Alan orani       : %.3f\n', eps_ratio);
        fprintf('  Cikis capi       : %.3f mm\n', d_exit);

        % Me basinca gore sabit mi? Sabit degilse model eksik.
        figure('Name', [LOGS{L} ' - Me kontrolu']);
        subplot(1,2,1);
        plot(Psum(ok)/(PSI2PA*N), Me_t, '.'); hold on;
        yline(Me, 'r--', 'LineWidth', 1.5);
        grid on; xlabel('Ort. lule basinci [psi]'); ylabel('M_e');
        title('M_e sabit olmali (degilse ayrilma/model hatasi)');

        subplot(1,2,2);
        F_pred = mdot(ok) .* (Me*sqrt(k*R*T0s./(1+0.2*Me^2)));
        scatter(Psum(ok)/(PSI2PA*N), F_tot(ok), 10, 'filled'); hold on;
        scatter(Psum(ok)/(PSI2PA*N), F_pred, 10, 'r');
        grid on; xlabel('Ort. lule basinci [psi]'); ylabel('Itki [N]');
        legend('Olculen','Model','Location','best');
        fprintf('  Model RMS hatasi : %%%.2f\n', ...
                100*rms((F_pred-F_tot(ok))./F_tot(ok)));
    else
        fprintf('\n  (thrust kanali yok -> Me ve cikis capi bu logdan cozulemez)\n');
    end

    %% ---------- 3) KAYIT ---------------------------------------------
    results(L).log = LOGS{L};
    results(L).N = N;
    results(L).A_throat = A_throat;
    results(L).d_throat = d_throat;
    results(L).d_range = 2000*sqrt(A_range/pi);
    results(L).Me = Me;
    results(L).d_exit = d_exit;

    % Bosalma egrisi
    figure('Name', [LOGS{L} ' - bosalma']);
    subplot(2,1,1);
    plot(t(seg), P_up(seg)/PSI2PA, 'k', 'LineWidth', 1.5); hold on;
    for i = 1:N, plot(t(seg), Pn{i}(seg)/PSI2PA, 'LineWidth', 1); end
    grid on; ylabel('psi'); title('Basinclar');
    subplot(2,1,2);
    plot(t(seg), CHOKED*A_throat*Psum(seg)./sqrt(R*T0_t(seg)), 'b', 'LineWidth', 1.5);
    grid on; ylabel('mdot toplam [kg/s]'); xlabel('t [s]');
end

%% ================= CAPRAZ DOGRULAMA ====================================
fprintf('\n\n########## CAPRAZ DOGRULAMA ##########\n');
for L = 1:numel(results)
    fprintf('%-16s (%d lule): d_t = %.3f mm  [%.3f - %.3f]\n', ...
            results(L).log, results(L).N, results(L).d_throat, ...
            results(L).d_range(1), results(L).d_range(2));
end

if numel(results) == 2
    dev = 100*abs(results(1).d_throat - results(2).d_throat) / ...
          mean([results.d_throat]);
    fprintf('\nIki log arasi sapma: %%%.1f\n', dev);
    if dev < 5
        fprintf('-> UYUMLU. Tank modeli ve sensorler tutarli.\n');
    else
        fprintf('-> SAPMA VAR. Olasi sebepler:\n');
        fprintf('   - 4 lule testinde tank<>manifold farki ihmal edilmis\n');
        fprintf('   - tank hacmi veya baslangic sicakligi yanlis\n');
        fprintf('   - lulelerin capi gercekten farkli\n');
    end
end

%% ================= SIMULINK PARAMETRELERI ==============================
best = results(1);
for L = 1:numel(results)
    if ~isnan(results(L).Me), best = results(L); end
end

fprintf('\n########## SIMULINK ##########\n');
fprintf('d_throat = %.4f;   %% mm\n', best.d_throat);
if ~isnan(best.Me)
    fprintf('M_e      = %.4f;\n', best.Me);
    fprintf('d_exit   = %.4f;   %% mm\n', best.d_exit);
    fprintf('\nkMdot gain (psi girisi): 0.6847*(pi*d_throat^2/4*1e-6)*6894.76/sqrt(287*T0)\n');
    fprintf('Ve gain                : M_e*sqrt(1.4*287*T0/(1+0.2*M_e^2))\n');
    fprintf('Cd gain                : 1.0   (geometri olculdugu icin ayrica carpma)\n');
end