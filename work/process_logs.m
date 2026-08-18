function S = load_logs_to_timeseries()
% Read CSV, remove rows with timestamp < 0, convert to struct of timeseries
opts = detectImportOptions('../LOGS/live0020.csv');
T = readtable('../LOGS/live0020.csv', opts);

% Assume there's a timestamp column; try common names
tsNames = {'timestamp','time','t','Timestamp','Time'};
tsCol = intersect(tsNames, T.Properties.VariableNames);
if isempty(tsCol)
    % If no common name, assume first column is timestamp
    ts = T{:,1};
    dataVars = T.Properties.VariableNames(2:end);
else
    ts = T.(tsCol{1});
    dataVars = setdiff(T.Properties.VariableNames, tsCol{1}, 'stable');
end

% Ensure numeric timestamp
if ~isnumeric(ts)
    ts = datenum(ts); % attempt conversion (works for datetime/char)
end

% Filter rows with timestamp >= 0
mask = ts >= 0;
ts = ts(mask);
T = T(mask, :);

% Convert timestamp to seconds relative to start if needed
% (keep raw values; timeseries supports numeric time vectors)
S = struct();
for k = 1:numel(dataVars)
    y = T.(dataVars{k});
    % Ensure numeric vector
    if ~isnumeric(y)
        if iscell(y)
            y = cellfun(@str2double, y);
        else
            y = double(y);
        end
    end
    S.(dataVars{k}) = timeseries(y, ts, 'Name', dataVars{k});
end
end