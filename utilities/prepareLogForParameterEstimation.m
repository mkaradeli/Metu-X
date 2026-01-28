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

%% Read CSV
T = readtable(filename, 'Delimiter', ',', 'TextType', 'string');

%% Base time
t = T.timestamp(:);
Ts_main = mean(diff(t));

ts = struct();

%% --------- Scalar signals ---------
scalarVars = {
    'motor_duty'
    'current_measured'
    'current_demand'
    'encoderButt'
    'vel_measured'
    'motor_pos_kalman'
    'angleRaw'
    'current_raw'
    'speedDemand'
    'pos_ref'
};

for i = 1:numel(scalarVars)
    v = scalarVars{i};
    ts.(v) = timeseries(T.(v), t, 'Name', v);
end

%% --------- Subsampled signals ---------
subsampledVars = {
    'current_subsample'
    'duty_subsample'
    'valveAngleKalman'
    'valveAngle'
    'valveVelocity'
};

for i = 1:numel(subsampledVars)
    v = subsampledVars{i};

    % "[...]" -> numeric vector
    dataCells = cellfun(@str2num, T.(v), 'UniformOutput', false); %#ok<ST2NM>

    Nsub = numel(dataCells{1});
    Ts_sub = Ts_main / Nsub;

    nMain = numel(t);
    t_sub = zeros(nMain * Nsub, 1);
    y_sub = zeros(nMain * Nsub, 1);

    idx = 1;
    for k = 1:nMain
        tk = t(k) + (0:Nsub-1)' * Ts_sub;

        t_sub(idx:idx+Nsub-1) = tk;
        y_sub(idx:idx+Nsub-1) = dataCells{k}(:);

        idx = idx + Nsub;
    end

    ts.(v) = timeseries(y_sub, t_sub, 'Name', v);
end

end
