function [ interpolatedSteps, time ] = interpolateSupportPhases( feetCoordinates, gaitBasicParams, doPlot )
%INTERPOLATESUPPORTPHASES Summary of this function goes here
%   [ interpolatedSteps, time ] = interpolateSupportPhases( feetCoordinates, gaitBasicParams, doPlot )

%% Create timeline
tSS = gaitBasicParams.timeSS;
tDS = gaitBasicParams.timeDS;
tTrans = gaitBasicParams.timeTransition;
tStep = gaitBasicParams.timeStep;

%% Remember to preallocate these variables in the future when things will be working
interpolatedSteps.LeftFootCoordinates = {};
interpolatedSteps.RightFootCoordinates = {};
time = [];
index = [];

%% First double support needs a special treatment
tStart = 0;
tEnd = tStart + tDS;
for t = tStart:tStep:tEnd
    interpolatedSteps.LeftFootCoordinates{end + 1} = feetCoordinates.LeftFootCoordinates{1};
    interpolatedSteps.RightFootCoordinates{end + 1} = feetCoordinates.RightFootCoordinates{1};
    time(end+1) = t;
end

%% For all the other steps following a DS -> SS pattern
if strcmp(gaitBasicParams.firstFootToMove,'left')
    index = 2:length(feetCoordinates.RightFootCoordinates);
else if strcmp(gaitBasicParams.firstFootToMove,'right')
        index = 2:length(feetCoordinates.LeftFootCoordinates);
    end
end

% WARNING: This assumes that the left foot always initiates the movement.
for idx=index
    % Single support (right foot)
    [time, interpolatedSteps] = partialInterpolateSSRight( interpolatedSteps, feetCoordinates, idx, time, gaitBasicParams );
    % Double Support
    [time, interpolatedSteps] = partialInterpolateDSLeftAhead( interpolatedSteps, feetCoordinates, idx, time, gaitBasicParams );
    % Single Support (left foot)
    [time, interpolatedSteps] = partialInterpolateSSLeft( interpolatedSteps, feetCoordinates, idx, time, gaitBasicParams );
    % Double Support (right ahead)
    [time, interpolatedSteps] = partialInterpolateDSRightAhead( interpolatedSteps, feetCoordinates, idx, time, gaitBasicParams );
end

%% Plot x coordinates evolution
x = [];
if (doPlot)
    figure(1);
    for i=1:length(interpolatedSteps.LeftFootCoordinates)
        if isempty(interpolatedSteps.LeftFootCoordinates{i})
            x(end+1) = -1;
        else
            x(end+1) = interpolatedSteps.LeftFootCoordinates{i}.position(1);
        end
    end
    subplot(121);
    plot(time,x), title('Left Foot X coord evolution'), axis tight;
end

x = [];
if (doPlot)
    for i=1:length(interpolatedSteps.LeftFootCoordinates)
        if isempty(interpolatedSteps.LeftFootCoordinates{i})
            x(end+1) = -1;
        else
            x(end+1) = interpolatedSteps.LeftFootCoordinates{i}.position(2);
        end
    end
    subplot(122);
    plot(time,x), title('Left Foot Y coord evolution'),axis tight;
end


x = [];
if (doPlot)
    figure(2);
    for i=1:length(interpolatedSteps.RightFootCoordinates)
        if isempty(interpolatedSteps.RightFootCoordinates{i})
            x(end+1) = -1;
        else
            x(end+1) = interpolatedSteps.RightFootCoordinates{i}.position(1);
        end
    end
    subplot(121);
    plot(time,x), title('Right Foot X coord evolution'), axis tight;
end

x = [];
if (doPlot)
    for i=1:length(interpolatedSteps.RightFootCoordinates)
        if isempty(interpolatedSteps.RightFootCoordinates{i})
            x(end+1) = -1;
        else
            x(end+1) = interpolatedSteps.RightFootCoordinates{i}.position(2);
        end
    end
    subplot(122);
    plot(time,x), title('Right Foot Y coord evolution'), axis tight;
end
end

