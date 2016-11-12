function [ leftFootCoordinates, rightFootCoordinates ] = drawInitialStandingFeet( interpTraj, horizon, gaitBasicParams )
%DRAWINITIALSTANDINGFEET Summary of this function goes here
%   drawInitialStandingFeet( interpTraj, horizon, gaitBasicParams )

startingPosition = [interpTraj.X(1), interpTraj.Y(1), 0]';

%% Draw left foot
leftFootCoordinates = drawFoot( 'left', startingPosition, gaitBasicParams, interpTraj, horizon );

%% Draw right foot
rightFootCoordinates = drawFoot( 'right', startingPosition, gaitBasicParams, interpTraj, horizon );

end