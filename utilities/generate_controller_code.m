function generate_controller_code()


%generate_controller_code

% parametreleri workspace'e ekle

currentControllerInit;
% controllerGains

% controllerGains değişkenini workspace'e kopyala
assignin('base', 'controllerGains', controllerGains);
assignin('base', 'PI_debug', PI_debug);
assignin('base', 'controller_mode', controller_mode);

%% Akım Kontrolcüsü

% kontrolcü parametreleri dışa aktarılıyor.
controllerGains.CoderInfo.StorageClass = "ImportedExtern";
controllerGains.CoderInfo.Identifier = "currentControllerGains";
controller_mode.CoderInfo.StorageClass = "ImportedExtern";


currentController = 'currentController';
if ~bdIsLoaded(currentController)
    load_system(currentController);
end
set_param(currentController, ...
    'GenCodeOnly', 'on', ...           % set to 'on' to only generate code
    'GenerateReport', 'off', ...
    'SolverType', 'Fixed-step', ...
    'Solver', 'FixedStepDiscrete', ...
    'FixedStep', '1e-3/8');
save_system(currentController);
slbuild(currentController);


%% Aktuator Kontrolcüsü

controllerGains.CoderInfo.StorageClass = "ExportedGlobal";
controller_mode.CoderInfo.StorageClass = "ExportedGlobal";

actuatorController = 'actuatorController';
if ~bdIsLoaded(actuatorController)
    load_system(actuatorController);
end
set_param(actuatorController, ...
    'GenCodeOnly', 'on', ...           % set to 'on' to only generate code
    'GenerateReport', 'off', ...
    'SolverType', 'Fixed-step', ...
    'Solver', 'FixedStepDiscrete', ...
    'FixedStep', '1e-3');
save_system(actuatorController);
slbuild(actuatorController);


%% KALMAN Filter

kalman_filter = 'actuatorKalman';
slbuild(kalman_filter);


%% codu paketle
% sourceFolder = fullfile(pwd, 'codegen', actuatorController + "_ert_rtw");
destinationFolder = fullfile(pwd, 'Controller');

% Hedef klasör yoksa oluştur
if ~exist(destinationFolder, 'dir')
    mkdir(destinationFolder);
end
if ~exist(destinationFolder+"/inc", 'dir')
    mkdir(destinationFolder+"/inc");
end
if ~exist(destinationFolder+"/src", 'dir')
    mkdir(destinationFolder+"/src");
end



% .c ve .h dosyalarını kopyala
sourceFolder = fullfile(pwd, 'codegen', currentController + "_ert_rtw");
copyfile(fullfile(sourceFolder, '*.cpp'), destinationFolder+"/src");
copyfile(fullfile(sourceFolder, '*.h'), destinationFolder+"/inc");


% .c ve .h dosyalarını kopyala
sourceFolder = fullfile(pwd, 'codegen', kalman_filter + "_ert_rtw");
copyfile(fullfile(sourceFolder, '*.cpp'), destinationFolder+"/src");
copyfile(fullfile(sourceFolder, '*.h'), destinationFolder+"/inc");


% .c ve .h dosyalarını kopyala
sourceFolder = fullfile(pwd, 'codegen', actuatorController + "_ert_rtw");
copyfile(fullfile(sourceFolder, '*.cpp'), destinationFolder+"/src");
copyfile(fullfile(sourceFolder, '*.h'), destinationFolder+"/inc");


delete(fullfile(destinationFolder, 'src', "ert_main.cpp"));


if exist(fullfile(pwd,"../../STM32CubeIDE/workspace_1.19.0/metux-test/app/Controller/"), 'dir')
    copyfile(fullfile(destinationFolder), fullfile(pwd,"../../STM32CubeIDE/workspace_1.19.0/metux-test/app/Controller/"))
elseif exist(fullfile(pwd,"../../Metu-X-stm32/app/"), 'dir')
    copyfile(fullfile(destinationFolder), fullfile(pwd,"../../Metu-X-stm32/app/Controller/"))
    
end

end

