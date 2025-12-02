%% MOTOR CONSTANTS

% motor.R=6.172082533; % motor electrical resistance
% motor.J=9.467439627476024e-06; % 1e-9; % motor inertia
% motor.Km=3.163192298281e-2; % motor emf constant
% motor.bv= 1.012322351758325e-04 ;%1.349324224921219e-04; % 1.858846856203e-5; % motor viscous friction coeff`
% motor.h = 1e-6; % inductance
% motor.Vgain = 1.675777980994449;
% 
% motor.Kbump= 1e6;
% motor.bbump=0.01;
% 
% motor.KdynamicFriction = 2.241328866546425e-04;
% motor.KstaticFriction = 0.137052003641456;
% motor.n = 86.020903061780270;
% motor.epsilon = 6.693499897501587e-08;



% pressure_controller.kP = 0.0017;
% pressure_controller.kI = 0;
% pressure_controller.kD = 0.000;
% pressure_controller.kFF = 0.0012;
% pressure_controller.rateLimiter = 1800; % bar/s
% pressure_controller.activeBand = 10; % bar
% pressure_controller.integralSaturation = 0.4;

lidar_height = 0.54;

ref_step.step1 = 250; %bar
ref_step.t1 = 1; % s
ref_step.step2 = 10; % bar
ref_step.t2 = 2; % s
ref_step.tend = 2.5; % s

ref_sine.P0 = 20; % bar
ref_sine.P_amp = 20; % bar
ref_sine.freq = 1; % hz
ref_sine.t1 = 1; % s
ref_sine.tend = 3; % s

velocity_controller.kP = 0.000571428565*1.5*0.7;
velocity_controller.kI = 0.013*1.2*0.5;
velocity_controller.kD = 0;
velocity_controller.kFF = 3.75e-4*1.2*1.3*1.2;
velocity_controller.rateLimiter = 1e5; % deg/s2 % CURRENTLY WRONG
velocity_controller_Ts = 1e-3;

enableKalmanForVelocityEst = 1;
enableKalmanForPositionEst = 1;

position_controller.kP = 15;
position_controller.kI = 0.0;
position_controller.kD = 0.0;
position_controller.kFF = 1.0;
position_controller.saturation = 420/60*360;
position_controller.saturationInt = 380/60*360;
position_controller.rateLimiter = 380/60*360; % deg/s
position_controller.activeBand = 20; %deg
position_controller_Ts = 1e-3;

force_controller_Ts = 1e-2;
% 


%% platform controller
platform_controller_Ts = 1e-2;
kalkis_target_height = 5;

%% attitude controller
attitude_controller.kP = 10;
attitude_controller.kI = 0;
attitude_controller.enable = 0;

%% Hardware In The Loop
hwil.enable = 0;
hwil.height = 9;