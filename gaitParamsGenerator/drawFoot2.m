function [ footCoordinates ] = drawFoot2( whichFoot, startingPosition, gaitBasicParams, interpTraj )
%DRAWFOOT2 Summary of this function goes here
%   drawFoot2( whichFoot, startingPosition, gaitBasicParams, interpTraj )

footCoordinates = [];

% Compute closest point in trajectory
closestXYonTraj = distance2curve([interpTraj.X', interpTraj.Y', zeros(length(interpTraj.Y),1)], startingPosition');
plot(startingPosition(1), startingPosition(2), 'ro');
% pause;
plot(closestXYonTraj(1), closestXYonTraj(2), 'ro');
% pause;

% Find (approx) those coordinates in interpolated trajectory
a = find(interpTraj.X > closestXYonTraj(1));
if ( length(a) < 2 )
    display('REACHED END OF TRAJECTORY');
    return;
end
xTmp = interpTraj.X(a(1));

% aY = find(interpTraj.Y > closestXYonTraj(2));
% if ( length(aY) < 2 )
%     display('REACHED END OF TRAJECTORY');
%     return;
% end
yTmp = interpTraj.Y(a(1));

plot(xTmp, yTmp, 'go')
% pause;
firstPointTmp = [xTmp, yTmp, 0]';
secondPointTmp = [interpTraj.X(a(2)), interpTraj.Y(a(2)), 0]';
% angle
helperVec = secondPointTmp - firstPointTmp;
rotationDeg = rad2deg(atan(helperVec(2)/helperVec(1)));

if (strcmp(whichFoot,'left'))
    %% Draw left foot
    % Normal offset from trajectory
    offset = normalToVectorXY( firstPointTmp, secondPointTmp, 'left', gaitBasicParams.feetSeparation/2, true );
    position = firstPointTmp + offset;
    drawSingleFootStep( position, ...
        rotationDeg, ...
        gaitBasicParams);
else if (strcmp(whichFoot, 'right'))
        %% Draw right foot
        % Normal offset from trajectory
        offset = normalToVectorXY( firstPointTmp, secondPointTmp, 'right', gaitBasicParams.feetSeparation/2 + gaitBasicParams.footWidth, true );
        position = firstPointTmp + offset;
        drawSingleFootStep( position, ...
            rotationDeg, ...
            gaitBasicParams);
    end
end

footCoordinates.position = position;
footCoordinates.offset = offset;
footCoordinates.rotationDeg = rotationDeg;

end