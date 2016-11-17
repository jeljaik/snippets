function [ time, interpolatedSteps ] = partialInterpolateSSRight( interpolatedSteps, feetCoordinates, index, time, gaitParams )
%PARTIALINTERPOLATESSRIGHT Summary of this function goes here
%   Detailed explanation goes here

tSS = gaitParams.timeSS;
tDS = gaitParams.timeDS;
tTrans = gaitParams.timeTransition;
tStep = gaitParams.timeStep;

tStart = time(end) + tStep;
tEnd = tStart + tSS;
for t = tStart:tStep:tEnd
    interpolatedSteps.LeftFootCoordinates{end+1} = [];
    interpolatedSteps.RightFootCoordinates{end+1} = feetCoordinates.RightFootCoordinates{index-1};
    time(end+1) = t;
end


end

