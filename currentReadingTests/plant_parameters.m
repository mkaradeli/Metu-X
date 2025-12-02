%% COORDINATES

% X front
% Y right
% Z bottom

% clear;

g=[0 0 -9.80665]; %m/s2 gravity constant

rho=1.293;
Cp=0.3;
A=0.5*0.5*pi/4;

drag_coeff=1/2*rho*Cp*A; % drag coefficiant
% TODO: add drag to the model

CONOPS.time = [0 0.09081081081081081 0.1891891891891892 0.47675675675675677 0.8778378378378379 1.2562162162162163 1.4416216216216216 1.627027027027027 1.8502702702702702 2.1794594594594594 2.4935135135135136 2.8189189189189188 3.1443243243243244 3.481081081081081];
CONOPS.velocity = [0 0.8506849315068493 1.8493150684931505 2.4164383561643836 3.180821917808219 3.9020547945205477 4.234931506849315 3.9452054794520546 3.563013698630137 2.995890410958904 2.4287671232876713 1.8184931506849316 1.1835616438356165 0.5178082191780822];

% lidar_height = 0.03;


%% INERTIAS

mass.empty=31.7;%28.43-3.0323; %kg empty mass
mass.full=35;%28.43; %kg initial mass
mass.fuel = mass.full - mass.empty;
inertia.full=[3284124266.87 -10646579.64 13079243.23;
            -10646579.64 3274195206.25 -31919601.52;
            13079243.23 -31919601.52 3028453281.08] / 1e9; %kg*m2 full inertia
inertia.empty= inertia.full; %kg*m2 empty inertia - assume same

%% MAIN THRUSTER
%main_m_dot = 0.4836;% kg/s main thruster mass flow rate
nozzle_pos.thrust_norm_front = [0 0 1];%1073.489]; % F thruster normalized
nozzle_pos.thrust_norm_rear = [0 0 1];%1073.489]; % F thruster normalized
nozzle_pos.thrust_norm_right = [0 0 1];%1073.489]; % F thruster normalized
nozzle_pos.thrust_norm_left = [0 0 1];%1073.489]; % F thruster normalized

%thrust=255.27;  %N main thrust force
nozzle_pos.height = 8;
nozzle_pos.dist = 0.3;
nozzle_pos.r_front = [nozzle_pos.dist 0 -nozzle_pos.height]; % nozzle position
nozzle_pos.r_rear = [-nozzle_pos.dist 0 -nozzle_pos.height]; % nozzle position
nozzle_pos.r_right = [0 nozzle_pos.dist -nozzle_pos.height]; % nozzle position
nozzle_pos.r_left = [0 -nozzle_pos.dist -nozzle_pos.height]; % nozzle position

%% INITIAL CONDITIONS

IC.xme_0=[0 0 9]; %inital positions in world axes [xe, ye, ze]
IC.Vm_0=[0 0 0];% initial velocity in body axes [u v w]
IC.eul_0=deg2rad([0.0 0.0 0.0]); % initial euler oriantation [roll pitch yaw]
IC.pm_0=deg2rad([0.0 0.0 0.0]); % initial body rotations [p q r]

IC.ground_height = 0; % m

%% pnuematic

Cmdot = 1.2827224;
cp = 1005;
cv = 718;
m0 = 3.1359;
T0 = 300;
tank_volume = 0.009;



%% Nozzle Parameters
Nozzle.M = 3.5;
% Nozzle.d = 4.5;
% Nozzle.Cd = [0.91; 0.91; 0.92; 0.9];

Nozzle.d = 2.8;
Nozzle.Cd = [0.92; 0.916; 0.867; 0.92];
