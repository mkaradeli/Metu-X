function ts = prepareLogForParameterEstimation(filename)
% csvToTimeseries  Convert logged CSV data into timeseries objects
%
%   ts = csvToTimeseries(filename)
%
% Assumptions:
%   - timestamp column is in seconds
%   - subsampled vectors are uniformly spaced
%   - subsamples start at timestamp(k)
%   - subsample length is constant across rows

if nargin < 1
    filename = "log0345.csv";
    % if folderPath == 0
        % error('No folder selected');
    % end
end
filename = "../LOGS/" + filename;
% create filename with '_4kHz' before the .csv extension

[filepath,name,ext] = fileparts(filename);

filename_4kHz = fullfile(filepath, name + '_4kHz' + ext);
filename_8kHz = fullfile(filepath, name + '_8kHz' + ext);


%% Read CSV

T = readtable(filename, 'Delimiter', ',');
T_4kHz = readtable(filename_4kHz, 'Delimiter', ',');
T_8kHz = readtable(filename_8kHz, 'Delimiter', ',');


%% Base time
t = T.timestamp(:);
t_4kHz = T_4kHz.timestamp(:);
t_8kHz = T_8kHz.timestamp(:);
% Ts_main = mean(diff(t));
ts = struct();

%% --------- Scalar signals ---------
scalarVars = {
    "timestamp"
    "current_measured"
    "current_demand"
    "speedDemand"
    "pos_ref"
    "pos_ref_rate_limited"
    "speed_ref_rate_limited"
    "manifold_pressure"
    "nozzle_pressure"
};

for i = 1:numel(scalarVars)
    v = scalarVars{i};
    ts.(v) = timeseries(T.(v), t, 'Name', v);
end
%% --------- Subsampled signals ---------
subsampledVars_4kHz = {
    % 'current_subsample'
    % 'duty_subsample'
    'valveAngleKalman'
    'valveAngle'
    'valveVelocity'
};

for i = 1:numel(subsampledVars_4kHz)
    v = subsampledVars_4kHz{i};
    ts.(v) = timeseries(T_4kHz.(v), t_4kHz, 'Name', v);
end


subsampledVars_8kHz = {
    'current_subsample'
    'duty_subsample'
    % 'valveAngleKalman'
    % 'valveAngle'
    % 'valveVelocity'
};

for i = 1:numel(subsampledVars_8kHz)
    v = subsampledVars_8kHz{i};
    ts.(v) = timeseries(T_8kHz.(v), t_8kHz, 'Name', v);
end



% for i = 1:numel(subsampledVars)
%     v = subsampledVars{i};
% 
%     % "[...]" -> numeric vector
% 
%     dataCells = cellfun(@str2num, T.(v), 'UniformOutput', false); %#ok<ST2NM>
% 
%     Nsub = numel(dataCells{1});
%     Ts_sub = Ts_main / Nsub;
% 
%     nMain = numel(t);
%     t_sub = zeros(nMain * Nsub, 1);
%     y_sub = zeros(nMain * Nsub, 1);
% 
%     idx = 1;
% 
%     for k = 1:nMain
%         tk = t(k) + (0:Nsub-1)' * Ts_sub;
% 
%         t_sub(idx:idx+Nsub-1) = tk;
%         y_sub(idx:idx+Nsub-1) = dataCells{k}(:);
% 
%         idx = idx + Nsub;
%     end
% 
%     ts.(v) = timeseries(y_sub, t_sub, 'Name', v);
% end


end
