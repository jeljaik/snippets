function [ feetCoordinates, numSteps ] = drawFootstepTrajectory( traj, horizon, gaitBasicParams, prevLeftFootCoord, prevRightFootCoord )
%DRAWFOOTSTEPTRAJECTORY Summary of this function goes here
%   drawFootstepTrajectory( traj, horizon, gaitBasicParams, prevLeftFootCoord, prevRightFootCoord )

% Feet coordinates will be stored in an array of structures!
LeftFootCoordinates{1} = prevLeftFootCoord;
RightFootCoordinates{1} = prevRightFootCoord;

%% Draw first half step
if (strcmp(gaitBasicParams.firstFootToMove, 'left'))
    start = prevLeftFootCoord.position;
    prevNormal = prevLeftFootCoord.offset;
    newStartingPosition = newStartingPositionAfterStep( start, prevNormal, 'left', gaitBasicParams, true );
    [ LeftFootCoordinates{end+1} ] = drawFoot2(gaitBasicParams.firstFootToMove, newStartingPosition, gaitBasicParams, traj);
else if (strcmp(gaitBasicParams.firstFootToMove, 'right'))
        start = prevRightFootCoord.position;
        prevNormal = prevRightFootCoord.offset;
        newStartingPosition = newStartingPositionAfterStep( start, prevNormal, 'right', gaitBasicParams, true );
        [ RightFootCoordinates{end+1} ] = drawFoot2(gaitBasicParams.firstFootToMove, newStartingPosition, gaitBasicParams, traj);
    end
end

%% Draw the rest of the steps

numSteps = 1;
stop = false;
while(~stop)
    prevRightFootCoord = RightFootCoordinates{end};
    prevLeftFootCoord = LeftFootCoordinates{end};
    % If numStep is odd draw right foot (right foot starts first full step)
    % This method must be improved because it assumes that the left foot
    % is always the first to start moving. 
    if ( mod(numSteps,2) == 1)
        start = prevRightFootCoord.position;
        prevNormal = prevRightFootCoord.offset;
        newStartingPosition = newStartingPositionAfterStep( start, prevNormal, 'right', gaitBasicParams, false );
        % Does this stopping method even work? Double check.
        stop = evaluateStopCondition(newStartingPosition, traj);
        if (stop == true)
            disp('Stopping because new step will be beyond the trajectory');
            break;
        end
        newRightFootCoordinates = drawFoot2('right', newStartingPosition, gaitBasicParams, traj);
        if (isempty(newRightFootCoordinates))
            break;
        end
        [ RightFootCoordinates{end+1} ] = newRightFootCoordinates;
    else
        start = prevLeftFootCoord.position;
        prevNormal = prevLeftFootCoord.offset;
        newStartingPosition = newStartingPositionAfterStep( start, prevNormal, 'left', gaitBasicParams, false );
        stop = evaluateStopCondition(newStartingPosition, traj);
        if (stop == true)
            disp('Stopping because new step will be beyond the trajectory');
            break;
        end
        newLeftFootCoordinates = drawFoot2('left', newStartingPosition, gaitBasicParams, traj);
        if (isempty(newLeftFootCoordinates))
            break;
        end
        [ LeftFootCoordinates{end+1} ] = newLeftFootCoordinates;
    end
    numSteps = numSteps + 1;
end

feetCoordinates.LeftFootCoordinates = LeftFootCoordinates;
feetCoordinates.RightFootCoordinates = RightFootCoordinates;

end

