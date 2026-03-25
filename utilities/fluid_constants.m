%% Global Constants
fluid.R = 287;
fluid.gamma = 1.4; 
fluid.Gamma = sqrt(fluid.gamma)*(2/(1+fluid.gamma))^((fluid.gamma+1)/(2*(fluid.gamma -1)));
fluid.Patm = 1.01325e5;
fluid.Cv = 717;
fluid.air_Cp_constants = [3.5575 -1.3606e-4 4.8601e-7 -3.2270e-10 7.3531e-14];


%% Tank Constant
fluid.V = 0.008; % m3
%% Nozzle Constants
fluid.A_throat = (2.8e-3/2)^2*pi; 
fluid.mdotGain = 1.325047107111672E-8;