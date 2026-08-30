
platform_targets = struct();
platform_targets.V_td = 0.1; % m/s
platform_targets.h_cut = 0.25; % m
platform_targets.h_blend = 1; % m


platform_targets.a_dec =9; %
platform_targets.a_dec_high = 15; % m/s2
platform_targets.a_dec_low = 5; % m/s2


platform_targets.V_max = 12; % m/s
platform_targets.Ts = 1/50;
platform_targets.fs = 50;
platform_targets.v_blend = sqrt( platform_targets.V_td^2 + 2*platform_targets.a_dec_low*(platform_targets.h_blend - platform_targets.h_cut));  %  /* precompute, constant */


%% altitude
platform_targets.altitude.kP = 9.8;
platform_targets.altitude.kI = platform_targets.altitude.kP^2/3;

%% hover 
platform_targets.hover.h_ref = 5;
platform_targets.hover.Kh = 3; % 1/s
platform_targets.hover.Kha = 3;
platform_targets.hover.v_sat = [-1.0 2.2];

%% attitude
platform_targets.attitude.Kp_att = 4.0;    
platform_targets.attitude.w_sat  = 1.5;    
platform_targets.attitude.tilt_abort = 0.66;  
platform_targets.attitude.Kp_rate = 30.3;
platform_targets.attitude.Ki_rate = 15;
platform_targets.attitude.r = 0.33;
r = platform_targets.attitude.r;
platform_targets.attitude.Alloc = [ 1  1  1  1 ;
                                    0  0  r -r ;
                                   -r  r  0  0 ;
                                    0  0  0  0 ];

%% test duzenegi (askı halatı)
rig.k       = 145;                                  % N/m
rig.h_rest  = 2.0;                                  % m, itki yokken asili durdugu irtifa
rig.m_test  = mass.empty + 2.83;                    % 34.33 kg
rig.h_slack = rig.h_rest + rig.m_test*9.81/rig.k;   % 4.32 m
rig.zeta    = 0.05;                                 % <-- log dekrementten cikar
rig.c       = 2*rig.zeta*sqrt(rig.k*rig.m_test);    % 7.1 N.s/m

