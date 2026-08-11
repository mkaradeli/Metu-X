%% Global Constants
fluid.R = 287;
fluid.gamma = 1.4; 
fluid.Gamma = sqrt(fluid.gamma)*(2/(1+fluid.gamma))^((fluid.gamma+1)/(2*(fluid.gamma -1)));
fluid.Patm = 1.01325e5;
fluid.Cv = 717;
fluid.air_Cp_constants = [3.5575 -1.3606e-4 4.8601e-7 -3.2270e-10 7.3531e-14];


%% Tank Constant
fluid.V = 0.009; % m3
%% Nozzle Constants
fluid.A_throat = (4.3e-3/2)^2*pi; 
fluid.mdotGain = 1.325047107111672E-8*3*1.05;


% fluid.mdotGain = 0.6847 *(fluid.A_throat) /sqrt(287*300);
simCoef = [9.963541300115264e-19	-5.638521979549971e-15	1.190871790366917e-11	-1.175632806688227e-08	4.809807875021960e-06	3.275236631208533e-04	0];

