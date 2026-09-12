
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
platform_targets.altitude.kP_hover = 24.4;
platform_targets.altitude.kI_hover = platform_targets.altitude.kP_hover^2/4.5;
%% hover 
platform_targets.hover.h_ref = 4;
platform_targets.hover.Kh = 4.5; % 1/s
platform_targets.hover.Khv = 8; % 1/s
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


