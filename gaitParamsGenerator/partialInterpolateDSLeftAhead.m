function [ time, interpolatedSteps ] = partialInterpolateDSLeftAhead( interpolatedSteps, feetCoordinates, index, time, gaitParams )
%PARTIALINTERPOLATEDSLEFTAHEAD Summary of this function goes here
%   Assumes time is initialized as an empty array as well as
%   interpolatedSteps.LeftFootCoordinates and
%   interpolatedSteps.RightFootCoordinates

tSS = gaitParams.timeSS;
tDS = gaitParams.timeDS;
tTrans = gaitParams.timeTransition;
tStep = gaitParams.timeStep;

tStart = time(end) + tStep;
tEnd = tStart + tDS;
for t = tStart:tStep:tEnd
    interpolatedSteps.LeftFootCoordinates{end+1} = feetCoordinates.LeftFootCoordinates{index};
    interpolatedSteps.RightFootCoordinates{end+1} = feetCoordinates.RightFootCoordinates{index-1};
    time(end+1) = t;
end

end

