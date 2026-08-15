mass.empty=34;%28.43-3.0323; %kg empty mass
mass.full=37.3;%28.43; %kg initial mass
X0 = 0; % Başlangıç Yüksekliği, Hover için 0 yap.
nozzle_diameter = 3.0; % nozzle çapı

load('valveFit.mat'); % 12 point lookup table from log 1441


controller_mode = controller_modes.FORCE;