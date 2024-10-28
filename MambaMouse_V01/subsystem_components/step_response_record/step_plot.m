
fclose all; close all; clear all; clc;% Load data with original column names
data = readtable('step_full.csv', 'VariableNamingRule', 'preserve');

% data = readtable('step_half.csv', 'VariableNamingRule', 'preserve');

%%
% Display the variable names to confirm column headers
disp(data.Properties.VariableNames);

% Extract variables using exact names
time = data.("Timestamp (ms)");
leftPosition = data.("Left Motor Position (mm)");
rightPosition = data.("Right Motor Position (mm)");
leftDelta = data.("Left Motor Delta (mm)");
rightDelta = data.("Right Motor Delta (mm)");

% Convert time to seconds and calculate velocity
time = time / 1000; 
time_diff = diff(time);
leftVelocity = diff(leftPosition) ./ time_diff;
rightVelocity = diff(rightPosition) ./ time_diff;

% Adjust time to match size of velocity data
time = time(1:end-1);

% Find the first point where velocity starts increasing for left and right motors
left_start_idx = find(leftVelocity > 0, 1, 'first');
right_start_idx = find(rightVelocity > 0, 1, 'first');
start_idx = min(left_start_idx, right_start_idx);  % Start from the earliest increase

% Crop data starting from the calculated index
time = time(start_idx:end);
leftPosition = leftPosition(start_idx:end-1);
rightPosition = rightPosition(start_idx:end-1);
leftDelta = leftDelta(start_idx:end-1);
rightDelta = rightDelta(start_idx:end-1);
leftVelocity = leftVelocity(start_idx:end);
rightVelocity = rightVelocity(start_idx:end);

% Reset time to start from 0
time = time - time(1);

% Apply moving average filter (window size = 5 samples)
windowSize = 100;
filteredLeftVelocity = movmean(leftVelocity, windowSize);
filteredRightVelocity = movmean(rightVelocity, windowSize);

% Plot positions, deltas, and velocities
figure;

subplot(3, 1, 1);
hold on;
plot(time, leftPosition, 'b-', 'DisplayName', 'Left Motor Position');
plot(time, rightPosition, 'r-', 'DisplayName', 'Right Motor Position');
xlabel('Time (s)');
ylabel('Position (mm)');
title('Motor Positions Over Time');
legend;
grid on;
hold off;

subplot(3, 1, 2);
hold on;
plot(time, leftDelta, 'b-', 'DisplayName', 'Left Motor Delta');
plot(time, rightDelta, 'r-', 'DisplayName', 'Right Motor Delta');
xlabel('Time (s)');
ylabel('Position Delta (mm)');
title('Motor Position Deltas Over Time');
legend;
grid on;
hold off;

subplot(3, 1, 3);
hold on;
plot(time, leftVelocity, 'b-', 'DisplayName', 'Left Motor Velocity (Original)');
plot(time, rightVelocity, 'r-', 'DisplayName', 'Right Motor Velocity (Original)');
plot(time, filteredLeftVelocity, 'c-', 'LineWidth', 1.5, 'DisplayName', 'Left Motor Velocity (Filtered)');
plot(time, filteredRightVelocity, 'm-', 'LineWidth', 1.5, 'DisplayName', 'Right Motor Velocity (Filtered)');
xlabel('Time (s)');
ylabel('Velocity (mm/s)');
title('Motor Velocities Over Time');
legend;
grid on;
hold off;