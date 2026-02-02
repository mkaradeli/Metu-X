function generate_controller_code()
%generate_controller_code

% parametreleri workspace'e ekle

currentControllerInit;
% controllerGains

% controllerGains değişkenini workspace'e kopyala
assignin('base', 'controllerGains', controllerGains);
assignin('base', 'PI_debug', PI_debug);

%% Akım Kontrolcüsü

% kontrolcü parametreleri dışa aktarılıyor.
controllerGains.CoderInfo.StorageClass = "ImportedExtern";
controllerGains.CoderInfo.Identifier = "currentControllerGains";

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
copyfile(fullfile(sourceFolder, '*.cpp'), destinationFolder + "/src");
copyfile(fullfile(sourceFolder, '*.h'), destinationFolder + "/inc");


sourceFolder = fullfile(pwd, 'codegen', currentController + "_ert_rtw");

% .c ve .h dosyalarını kopyala
copyfile(fullfile(sourceFolder, '*.cpp'), destinationFolder+"/src");
copyfile(fullfile(sourceFolder, '*.h'), destinationFolder+"/inc");

sourceFolder = fullfile(pwd, 'codegen', kalman_filter + "_ert_rtw");

% .c ve .h dosyalarını kopyala
copyfile(fullfile(sourceFolder, '*.cpp'), destinationFolder+"/src");
copyfile(fullfile(sourceFolder, '*.h'), destinationFolder+"/inc");


delete(fullfile(destinationFolder, 'src', "ert_main.cpp"));



copyfile(fullfile(destinationFolder), fullfile(pwd,"../../STM32CubeIDE/workspace_1.19.0/metux-test/app/Controller/"))

end

