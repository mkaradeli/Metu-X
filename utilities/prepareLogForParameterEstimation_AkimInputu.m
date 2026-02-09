function dataArray = prepareLogForParameterEstimation(folderPath)
% folderPath = 'C:\Users\egeel\Desktop\metux-son\Metu-X\LOGS';
% prepareLogForParameterEstimation  Convert all CSV logs in a folder to timeseries
%
%   prepareLogForParameterEstimation(folderPath)
%
%   Inputs:
%       folderPath - Path to folder containing CSV log files
%
%   Outputs:
%       Creates ans1, ans2, ans3, ... structs in base workspace
%       Position and velocity signals are downsampled from 4kHz to 1kHz
%       to match current measurement sampling rate (4:1 averaging)
%
% Assumptions:
%   - timestamp column is in seconds
%   - subsampled vectors are uniformly spaced
%   - subsamples start at timestamp(k)
%   - subsample length is constant across rows
%   - Position/velocity: 4kHz, Current: 1kHz

%% Get all CSV files in the folder
if nargin < 1
    % folderPath = uigetdir('', 'Select folder containing log files');
    folderPath = "../LOGS/";

end


% Karadeli
csvFiles = dir(fullfile(folderPath, '*.csv'));




if isempty(csvFiles)
    error('No CSV files found in the specified folder');
end

fprintf('Found %d CSV files in folder: %s\n', numel(csvFiles), folderPath);
% global_ts = struct()
%% Process each file

    numFiles = length(csvFiles);
    dataCell = cell(numFiles, 1);
    validIdx = false(numFiles, 1);

    for i = 1:numFiles
        filename =  csvFiles(i).name;
        if contains(filename,"4kHz") || contains(filename,"8kHz")
            continue;
        end

            fprintf('Processing file %d/%d: %s\n', i, numFiles, filename);
            
            % Call your function
            dataCell{i} = prepareLogForParameterEstimation(filename);
            validIdx(i) = true;
            dataCell{i}.filename = filename;

        
    end
     if any(validIdx)
        dataArray = [dataCell{validIdx}];
    else
        error('No files were successfully processed');
    end

% fprintf('\nProcessing complete. Created %d ans structures in workspace.\n', numel(csvFiles));
% fprintf('Variables created: ans1, ans2, ..., ans%d\n', numel(csvFiles));
assignin('base', "ts", dataArray);
end

