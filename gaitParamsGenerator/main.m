close all;

addpath(genpath('arrow'));
addpath(genpath('spinCalc'));
addpath(genpath('distance2curve'));

%% Create trajectory
% Number of user-input points. 
nPoints = 2;
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
% Time in Single Support Phase
gaitBasicParams.timeSS = 2;
% Time in Double Support Phase
gaitBasicParams.timeDS = 1;
% Transition time
gaitBasicParams.timeTransition = 2;
% Time step
gaitBasicParams.timeStep = 0.10;
[leftFootCoordinates, rightFootCoordinates] = drawInitialStandingFeet( traj, horizon, gaitBasicParams );

%% Draw the following nSteps
% Making the step length a 70% larger than the foot length
gaitBasicParams.stepLength = 0.5*gaitBasicParams.footLength; % + 0.2*gaitBasicParams.footLength;

prevLeftFootCoord = leftFootCoordinates;
prevRightFootCoord = rightFootCoordinates;
[feetCoordinates, numSteps] = drawFootstepTrajectory( traj, horizon, gaitBasicParams, prevLeftFootCoord, prevRightFootCoord );

%% Interpolate support phases
doPlot = true;
[ interpolatedSteps, time ] = interpolateSupportPhases( feetCoordinates, gaitBasicParams, false );

%% Compute Lower and Upper Bounds a and b
[ aCum, bCum, hLow, hUp ] = ComputeLowerAndUpperBounds( interpolatedSteps, gaitBasicParams, time, doPlot );

%% Compute alpha and beta
[ alphaCum, betaCum ] = computeRisingAndFallingEdges( aCum, bCum, time, hLow, hUp );

%% Compute gamma, Support Phase Change variable
% In theory this should be better obtained from a,b, alpha and beta. For
% simplicity let's do it from interpolatedSteps
[ gammaCum ] = computeGamma( interpolatedSteps, time, hLow, hUp, doPlot );

%% Compute delta
[ deltaCum ] = computeDelta( alphaCum, betaCum, time, hLow, hUp, doPlot); 