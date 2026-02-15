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
% if(~bdIsLoaded(currentController))
%     open_system(currentController);
% end

slbuild(currentController);
% coder.report.generate(controllerModel);
% coder.report.open(controllerModel);




%% Hız ve Pozisyon Kontrolcüsü

% kontrolcü parametreleri bir kere dışa aktarıldığı için tekrar dışa
% aktarılmayacak.
controllerGains.CoderInfo.StorageClass = "ExportedGlobal";
controllerGains.CoderInfo.Identifier = "currentControllerGains";
controller_mode.CoderInfo.StorageClass = "ExportedGlobal";


positionController = 'positionController';
% if(~bdIsLoaded(positionController))
%     open_system(positionController);
% end
slbuild(positionController);
% coder.report.generate(controllerModel);
% coder.report.open(controllerModel);

%% KALMAN Filter

kalman_filter = 'actuatorKalman';
slbuild(kalman_filter);


%% PRESSURE Controller

controller_mode.CoderInfo.StorageClass = "ImportedExtern";
pressureController = "pressureController";
slbuild(pressureController);



%% codu paketle
sourceFolder = fullfile(pwd, 'codegen', positionController + "_ert_rtw");
destinationFolder = fullfile(pwd, 'Controller');

% Hedef klasör yoksa oluştur
if ~exist(destinationFolder, 'dir')
    mkdir(destinationFolder);
end
if ~exist(destinationFolder+"/inc", 'dir')
    mkdir(destinationFolder);
end
if ~exist(destinationFolder+"/src", 'dir')
    mkdir(destinationFolder);
end

% .c ve .h dosyalarını kopyala
sourceFolder = fullfile(pwd, 'codegen', positionController + "_ert_rtw");
copyfile(fullfile(sourceFolder, '*.cpp'), destinationFolder + "/src");
copyfile(fullfile(sourceFolder, '*.h'), destinationFolder + "/inc");



% .c ve .h dosyalarını kopyala
sourceFolder = fullfile(pwd, 'codegen', currentController + "_ert_rtw");
copyfile(fullfile(sourceFolder, '*.cpp'), destinationFolder+"/src");
copyfile(fullfile(sourceFolder, '*.h'), destinationFolder+"/inc");


% .c ve .h dosyalarını kopyala
sourceFolder = fullfile(pwd, 'codegen', kalman_filter + "_ert_rtw");
copyfile(fullfile(sourceFolder, '*.cpp'), destinationFolder+"/src");
copyfile(fullfile(sourceFolder, '*.h'), destinationFolder+"/inc");


% .c ve .h dosyalarını kopyala
sourceFolder = fullfile(pwd, 'codegen', pressureController + "_ert_rtw");
copyfile(fullfile(sourceFolder, '*.cpp'), destinationFolder+"/src");
copyfile(fullfile(sourceFolder, '*.h'), destinationFolder+"/inc");


delete(fullfile(destinationFolder, 'src', "ert_main.cpp"));


if exist(fullfile(pwd,"../../STM32CubeIDE/workspace_1.19.0/metux-test/app/Controller/"), 'dir')
    copyfile(fullfile(destinationFolder), fullfile(pwd,"../../STM32CubeIDE/workspace_1.19.0/metux-test/app/Controller/"))
elseif exist(fullfile(pwd,"../../Metu-X-stm32/app/"), 'dir')
    copyfile(fullfile(destinationFolder), fullfile(pwd,"../../Metu-X-stm32/app/Controller/"))
    
end

end

