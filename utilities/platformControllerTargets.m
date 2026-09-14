
platform_targets = struct();
platform_targets.V_td = 0.6; % m/s 0.4
platform_targets.h_cut   = 0.15; % m 0.3
platform_targets.h_blend = 1; % m


platform_targets.a_dec =3; %
% platform_targets.a_freefall = 5; %
% platform_targets.a_dec_high = 15; % m/s2
platform_targets.a_dec_low = 5; % m/s2


platform_targets.V_max = 3; % m/s
platform_targets.Ts = 1/50;
platform_targets.fs = 50;
% platform_targets.v_blend = sqrt( platform_targets.V_td^2 + 2*platform_targets.a_dec_low*(platform_targets.h_blend - platform_targets.h_cut));  %  /* precompute, constant */


%% altitude
platform_targets.altitude.kP = 9.9;
platform_targets.altitude.kI = 24.6;
platform_targets.altitude.kP_hover = 24.4/1.3;
platform_targets.altitude.kI_hover = platform_targets.altitude.kP_hover^2/4.5;
%% hover 
platform_targets.hover.h_ref = 3;
platform_targets.hover.Kh = 4.5; % 1/s
platform_targets.hover.Khv = 8; % 1/s
platform_targets.hover.v_sat = [-1.0 2.2];

%% attitude
platform_targets.attitude.Kp_att = 4.0;    
platform_targets.attitude.w_sat  = 1.5;    
platform_targets.attitude.tilt_abort = 0.66;  
platform_targets.attitude.Kp_rate = 40.3; % 30.3
platform_targets.attitude.Ki_rate = 105; % 15
platform_targets.attitude.r = 0.33;
r = platform_targets.attitude.r;
platform_targets.attitude.Alloc = [ 1  1  1  1 ;
                                    0  0  r -r ;
                                   -r  r  0  0 ;
                                    0  0  0  0 ];


platform_targets.attitude.cog = [0 0.0 0];



%% lookup
load("drop_lookup_table.mat")