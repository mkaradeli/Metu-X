%% Global Constants
R = 287;
gamma = 1.4; 
Gamma = sqrt(gamma)*(2/(1+gamma))^((gamma+1)/(2*(gamma -1)));
Patm = 1.01325e5;
Cv = 717;
air_Cp_constants = [3.5575 -1.3606e-4 4.8601e-7 -3.2270e-10 7.3531e-14];


%% Tank Constant
V = 0.008; % m3
%% Nozzle Constants
A_throat = (2.8e-3/2)^2*pi; 
mdotGain = 1.325047107111672E-8;