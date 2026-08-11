function log = read_log_v13(filename)
%IMPORT_ACTUATOR_LOG  Load a formatID 13 actuator log CSV into a struct.
%
%   log = import_actuator_log("mylog.csv")
%
%   Output structure (mirrors the Python df / df_act split):
%     log.t                  timestamp vector [s], already zeroed & scaled by the logger
%     log.act(i).<field>     per-actuator signals, i = 1..4  (act(1) == _0 columns)
%     log.manifold_pressure  manifold pressure [same units as logged]
%     log.manifold_raw       raw manifold ADC counts
%     log.thrust_measured    load cell thrust
%     log.thrust_raw         raw load cell counts
%     log.T                  the full table as read, if you need anything else
%
%   Example:
%     log = import_actuator_log("flight_007.csv");
%     plot(log.t, log.act(2).valveAngle, log.t, log.act(2).pos_ref);
%     legend("valveAngle","pos\_ref"); xlabel("t [s]");

arguments
    filename (1,1) string
end

if ~isfile(filename)
    error("import_actuator_log:fileNotFound", ...
        "File '%s' does not exist.", filename);
end

T = readtable(filename, 'VariableNamingRule', 'preserve');

actFields = { ...
    'current_measured', ...
    'current_demand', ...
    'valveAngle', ...
    'valveAngleKalman', ...
    'valveVelocity', ...
    'duty', ...
    'speedDemand', ...
    'pos_ref', ...
    'pos_ref_rate_limited', ...
    'speed_ref_rate_limited', ...
    'nozzle_pressure', ...
    'pressure_demand', ...
    'thrust_demand', ...
    'thrust_estimated', ...
    'nozzle_raw'};

nAct = 4;

log   = struct();
log.t = T.("timestamp");

% Per-actuator struct array: log.act(1) holds the *_0 columns, etc.
for i = nAct:-1:1                       % reverse loop preallocates the array
    for k = 1:numel(actFields)
        col = sprintf('%s_%d', actFields{k}, i-1);
        if ~ismember(col, T.Properties.VariableNames)
            error("import_actuator_log:missingColumn", ...
                "Expected column '%s' not found in '%s'.", col, filename);
        end
        log.act(i).(actFields{k}) = T.(col);
    end
end

% Shared / tail signals
tailFields = ["manifold_pressure", "manifold_raw", ...
              "thrust_measured",   "thrust_raw"];
for f = tailFields
    if ismember(f, T.Properties.VariableNames)
        log.(f) = T.(f);
    end
end

% Keep the raw table around for anything not covered above (e.g. crc)
log.T = T;

fprintf("Loaded %d samples, t = [%.3f, %.3f] s (%.1f s), %d actuators\n", ...
    height(T), log.t(1), log.t(end), log.t(end) - log.t(1), nAct);

end
