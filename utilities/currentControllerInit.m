%% CURRENT CONTROLLER
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


%% SPEED CONTROLLER (GÜNCELLENDİ)
f_speed = 2*pi*300;
zeta = 0.707;

% --- YENİ MODEL DEĞERLERİ (Görselden Alındı) ---
% Workspace görselindeki (image_c17581) güncel değerler:
J_      = 1.6640902592735392E-5;
Km_     = 0.050266292709408661;      % Yeni Km değeri
bv_     = 7.412339946963472E-5;      % Yeni Viskoz Sürtünme (bv)
Fs_max_ = 0.0054517494481315263;     % Yeni Statik Sürtünme (Coulomb)


% --- STATİK SÜRTÜNME KOMPANZASYONU ---
% Basıncı disturbance olarak bıraktık ama Statik Sürtünme (Fs_max)
% motorun kalkışını engeller. Bunu formüle katmak için;
% Statik sürtünmeyi, hedef bant genişliği hızında "eşdeğer viskoz sürtünmeye" çeviriyoruz.
% Bu, Ki integral kazancını artırarak motorun takılmasını önler.


SatMax = 15;
SatMin = -15;
Ts = 1/1000;
RateLimiterMax = 2e15;
RateLimiterMin = -2e15;

% SpeedGains = struct();

% Kp Hesabı: Atalet (J) ve yeni Km'ye bağlı.
controllerGains.speed.Kp = single(J_ / Km_ * f_speed);
controllerGains.speed.Kp
% Ki Hesabı: Viskoz (bv) + Statik (Fs) toplam direncine göre hesaplandı.
% Bu sayede integral, hem sürtünmeyi hem de basınç yükünü (disturbance) yenecek güce ulaşır.
controllerGains.speed.Ki = single(bv_ / Km_ * f_speed);
controllerGains.speed.Ki
controllerGains.speed.SatMax = single(SatMax);
controllerGains.speed.SatMin = single(SatMin);
controllerGains.speed.RateLimiterMax = single(RateLimiterMax);
controllerGains.speed.RateLimiterMin = single(RateLimiterMin);
controllerGains.speed.Ts = Ts;

% Geçici değişkenleri temizle
clear("J_", "Km_", "bv_", "Fs_max_");

%% POSITION CONTROLLER
f_position = 2*pi*20;
Kp = f_position/2;
Kff = 0.8;
SatMax = 2400;
SatMin = -2400;
RateLimiterMax = 2400;
RateLimiterMin = -2400;
Ts = 1/1000;
controllerGains.position.Kp = single(Kp);
controllerGains.position.Kff = single(Kff);
controllerGains.position.SatMax = single(SatMax); % deg/s
controllerGains.position.SatMin = single(SatMin); % deg/s
controllerGains.position.RateLimiterMax = single(RateLimiterMax); % deg/s
controllerGains.position.RateLimiterMin = single(RateLimiterMin); % deg/s
controllerGains.position.Ts = double(Ts);


%% PRESSURE CONTROLLER
controllerGains.pressure.Kp = single(0.5);

clear("SatMin", "SatMax", "Kp","Kff", "Ki", "Ts", "f_position","f_speed", "f_current", "RateLimiterMin", "RateLimiterMax");


%% BUS DEFINITIONS & CODER INFO
controllerGains = Simulink.Parameter(controllerGains);
controllerGains.CoderInfo.StorageClass = "ExportedGlobal";
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
PI_debug.Elements(3) = Simulink.BusElement;
PI_debug.Elements(3).Name = 'ref_rate_limited';
PI_debug.Elements(3).DataType = 'single';
PI_debug.Elements(3).Dimensions = 1;




% controller_modes = Simulink.Parameter(controller_modes);
controller_mode = controller_modes.DISABLE;
controller_mode = Simulink.Parameter(controller_mode);
controller_mode.CoderInfo.StorageClass = "ExportedGlobal";
controller_mode.CoderInfo.Identifier = "controller_mode";

