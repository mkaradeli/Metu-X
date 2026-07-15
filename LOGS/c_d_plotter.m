% Define the filename
filename = 'log1164.csv';

% ---------------------------------------------------------
% Optional Filtering Parameters
% ---------------------------------------------------------
applyPressureFilter = true;   % Set to true to enable filtering, false to disable
minPressureThreshold = 150;   % Minimum nozzle pressure to include in the analysis

% Read the data into a table
dataTable = readtable(filename, 'PreserveVariableNames', true);
headers = dataTable.Properties.VariableNames;

% Search for the specific column indices
pressureColIdx = find(strcmp(headers, 'nozzle_pressure_0'));
thrustColIdx = find(strcmp(headers, 'thrust_measured'));

% Error handling
if isempty(pressureColIdx) || isempty(thrustColIdx)
    error('Could not find "nozzle_pressure_0" or "thrust_measured" in the CSV headers.');
end

% Extract the data series
pressure = dataTable{:, pressureColIdx};
thrust = dataTable{:, thrustColIdx};

% 1. Initial Cleaning: Remove NaNs
validData = ~isnan(pressure) & ~isnan(thrust);
pressure = pressure(validData);
thrust = thrust(validData);

% 2. Optional Filtering: Skip data below the pressure threshold
if applyPressureFilter
    % Create a logical index of points that meet the condition
    filterIdx = pressure >= minPressureThreshold;
    
    % Inform the user in the command window
    pointsRemoved = sum(~filterIdx);
    fprintf('Pressure filter active: Removed %d points below %.2f.\n', pointsRemoved, minPressureThreshold);
    
    % Apply the filter
    pressure = pressure(filterIdx);
    thrust = thrust(filterIdx);
end

% 3. Outlier Detection:
% Perform an initial fit to establish a baseline
initialCoeffs = polyfit(pressure, thrust, 1);
initialFit = polyval(initialCoeffs, pressure);

% Calculate the residuals
residuals = thrust - initialFit;

% Identify outliers based on the Median Absolute Deviation (MAD)
outlierFlags = isoutlier(residuals, 'median');

% Separate the data into clean points and outliers
pressure_outliers = pressure(outlierFlags);
thrust_outliers = thrust(outlierFlags);
pressure_clean = pressure(~outlierFlags);
thrust_clean = thrust(~outlierFlags);

% 4. Final Fit: Calculate c_d using only the clean data
finalCoeffs = polyfit(pressure_clean, thrust_clean, 1);
c_d = finalCoeffs(1);
offset = finalCoeffs(2);

% Display the result in the command window
fprintf('Removed %d outlier points.\n', sum(outlierFlags));
fprintf('The constant gain (c_d) is calculated as: %.4f\n', c_d);
fprintf('The linear offset is: %.4f\n', offset);

% ---------------------------------------------------------
% Plotting the data, the fit, and the c_d value
% ---------------------------------------------------------
figure;
hold on;

% Plot Outliers (Red Crosses) and Clean Data (Blue Dots)
scatter(pressure_outliers, thrust_outliers, 'rx', 'DisplayName', 'Outliers');
scatter(pressure_clean, thrust_clean, 'b.', 'DisplayName', 'Clean Data');

% Create points for the fitted line using the clean data range
[pressure_sorted, sortIdx] = sort(pressure_clean);
fitLine = polyval(finalCoeffs, pressure_sorted);
plot(pressure_sorted, fitLine, 'k-', 'LineWidth', 2, 'DisplayName', 'Linear Fit (Clean)');

% Write the c_d value directly onto the figure
c_d_Text = sprintf('Constant Gain (c_d) = %.4f', c_d);
text(0.05, 0.90, c_d_Text, 'Units', 'normalized', ...
    'FontSize', 12, 'FontWeight', 'bold', 'BackgroundColor', 'white', ...
    'EdgeColor', 'black');

% Formatting the plot
xlabel('Nozzle Pressure (nozzle\_pressure\_0)');
ylabel('Measured Thrust (thrust\_measured)');
title('Thrust vs. Pressure with Outlier Rejection');
legend('Location', 'best');
grid on;
hold off;