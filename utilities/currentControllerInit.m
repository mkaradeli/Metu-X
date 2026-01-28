f_current = 2*pi*800;
Ki = f_current * 3.4 / 24;
Kp = f_current * 3.7440493227724682E-5 / 24;
SatMax = 1;
SatMin = -1;
Ts = 1/8000;

clear("controllerGains");
controllerGains = struct();
controllerGains.current.Kp = single(Kp);
controllerGains.current.Ki = single(Ki);
controllerGains.current.SatMax = single(SatMax);
controllerGains.current.SatMin = single(SatMin);
controllerGains.current.Ts = double(Ts);


f_speed = 2*pi*100;

J_ = 1.6640902592735392E-5;
Km_ = 0.048589858612573242;
b_ = 0.00015997910300577089;
SatMax = 10;
SatMin = -10;
Ts = 1/1000;

% SpeedGains = struct();
controllerGains.speed.Kp = single(J_/Km_*f_speed*pi/180);
controllerGains.speed.Ki = single(0.7*b_/Km_*f_speed*pi/180);
controllerGains.speed.SatMax = single(SatMax);
controllerGains.speed.SatMin = single(SatMin);
controllerGains.speed.Ts = Ts;

clear("J_","Km_","b_");

f_position = 2*pi*20;
Kp = f_position/2;
SatMax = 25000;
SatMin = -25000;
Ts = 1/1000;

controllerGains.position.Kp = single(Kp);
controllerGains.position.SatMax = single(SatMax);
controllerGains.position.SatMin = single(SatMin)
controllerGains.position.Ts = double(Ts);
clear("SatMin", "SatMax", "Kp", "Ki", "Ts", "f_position","f_speed", "f_current");


controllerGains = Simulink.Parameter(controllerGains);



controllerGains.CoderInfo.StorageClass = "ImportedExtern";
controllerGains.CoderInfo.Identifier = "currentControllerGains";


PI_debug = Simulink.Bus;
PI_debug.Elements(1) = Simulink.BusElement;
PI_debug.Elements(1).Name = 'Up';
PI_debug.Elements(1).DataType = 'single';
PI_debug.Elements(1).Dimensions = 1;
PI_debug.Elements(2) = Simulink.BusElement;
PI_debug.Elements(2).Name = 'Ui';
PI_debug.Elements(2).DataType = 'single';
PI_debug.Elements(2).Dimensions = 1;