
platform_targets = struct();
platform_targets.V_td = 0.5; % m/s
platform_targets.h_cut = 0.2; % m
platform_targets.h_blend = 1; % m

platform_targets.a_dec_high = 15; % m/s2
platform_targets.a_dec = 15; % m/s2
platform_targets.a_dec_low = 5; % m/s2


platform_targets.V_max = 12; % m/s
platform_targets.Ts = 1/50;
platform_targets.fs = 50;
platform_targets.beta_max = 5;
platform_targets.v_blend = sqrt( platform_targets.V_td^2 + 2*platform_targets.a_dec_low*(platform_targets.h_blend - platform_targets.h_cut))  %  /* precompute, constant */


%% altitude
platform_targets.altitude.kP = 9.8;
platform_targets.altitude.kI = platform_targets.altitude.kP^2/8;

%% hover 
platform_targets.hover.h_ref = 5;
platform_targets.hover.Kh = 2.5; % 1/s
platform_targets.hover.v_sat = [-1.0 2.2];
