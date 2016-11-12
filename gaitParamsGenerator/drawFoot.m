function [ footCoordinates ] = drawFoot( whichFoot, startingPosition, gaitBasicParams, interpTraj, horizon )
%DRAWFOOT Draws either the left or right foot around a trajectory.
%   DRAWFOOT( whichFoot, startingPosition, gaitBasicParams, interpTraj, horizon )

% Compute angle at which the foot will be drawn
secondPointTmp = [interpTraj.X(horizon), interpTraj.Y(horizon), 0]';
helperVector = secondPointTmp - startingPosition;
rotationDeg = rad2deg( atan(helperVector(2)/helperVector(1)) );

if (strcmp(whichFoot,'left'))
    %% Draw left foot
    % Normal offset from trajectory
    offset = normalToVectorXY( startingPosition, secondPointTmp, 'left', gaitBasicParams.feetSeparation/2, true );
    position = startingPosition + offset;
    
    drawSingleFootStep( position, ...
                        rotationDeg, ...
                        gaitBasicParams);
else if (strcmp(whichFoot, 'right'))
        %% Draw right foot
        offset = normalToVectorXY( startingPosition, secondPointTmp, 'right', gaitBasicParams.feetSeparation/2 + gaitBasicParams.footWidth, true );
        position = startingPosition + offset;
        
        drawSingleFootStep( position, ...
                            rotationDeg, ...
                            gaitBasicParams);
    end
end

footCoordinates.position = position;
footCoordinates.offset = offset;
footCoordinates.rotationDeg = rotationDeg;

end