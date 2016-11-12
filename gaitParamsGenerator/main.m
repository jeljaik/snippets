close all;

addpath(genpath('arrow'));
addpath(genpath('spinCalc'));
addpath(genpath('distance2curve'));

%% Create trajectory
% Number of user-input points. 
nPoints = 6;
% Interpolation type ('linear' is another option)
interpType = 'spline';
% Number of interpolation points between every pair of points
numInterPoints = 100;
% Generate basic trajectory to follow
traj = generateInterpTrajectory(nPoints, interpType, numInterPoints, true);

%% Draw initial two standing feet
% Feet separation. [cm]
gaitBasicParams.feetSeparation = 10;
% Feet dimensions. [cm]
gaitBasicParams.footWidth = 5;
gaitBasicParams.footLength = 10;
% First foot to move.
gaitBasicParams.firstFootToMove = 'left';
% horizon 
horizon = 2;

[leftFootCoordinates, rightFootCoordinates] = drawInitialStandingFeet( traj, horizon, gaitBasicParams );

%% Draw the following nSteps
% Making the step length a 70% larger than the foot length
gaitBasicParams.stepLength = 0.5*gaitBasicParams.footLength; % + 0.2*gaitBasicParams.footLength;

prevLeftFootCoord = leftFootCoordinates;
prevRightFootCoord = rightFootCoordinates;
[feetCoordinates, numSteps] = drawFootstepTrajectory( traj, horizon, gaitBasicParams, prevLeftFootCoord, prevRightFootCoord );

