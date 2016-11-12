function [ newStartingPosition ] = newStartingPositionAfterStep( vr, prevNormal, whichFoot, gaitBasicParams, isFirstStep )
%NEWSTARTINGPOSITIONAFTERSTEP Summary of this function goes here
%   newStartingPositionAfterStep( v1, prevNormal, gaitBasicParams, isFirstStep )

%% Assuming the trajectory will be a straight line!
if (isFirstStep == true)
    gaitBasicParams.stepLength = gaitBasicParams.stepLength/2;
end

if (strcmp(whichFoot,'left'))
    newStartingPosition = vr + gaitBasicParams.stepLength * cross(1/norm(prevNormal)*prevNormal, [0 0 1]');
else if (strcmp(whichFoot, 'right'))
        newStartingPosition = vr + gaitBasicParams.stepLength * cross([0 0 1]', 1/norm(prevNormal)*prevNormal);
    end
end

end
