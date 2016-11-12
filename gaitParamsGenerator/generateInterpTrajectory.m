function [ traj ] = generateInterpTrajectory( nPoints, interpType, numInterpPoints, doPlot )
%GENERATEINTERPTRAJECTORY Given nPoints coordinates selected interactively
%by the user, interpolate the trajectory.
%
%   interpY = GENERATEINTERPTRAJECTORY( nPoints, interpType, numInterPoints, doPlot)
%   will generate a vector of interpolated values given nPoints coordinate
%   selected by the user. The type of interpolation corresponds to those by
%   INTERP1, e.g. 'linear', 'spline'. numInterPoints are the number of 
%   interpolation points to use between every pair of points input by the 
%   user. When the argument doPlot is set to true, a plot will be drawn at 
%   the end of this function. 

if (nargin < 4)
    doPlot = false;
end

% Select nPoints with cursor. By defaut the screen is from 0 to 1. They
% will be scaled. 
scaleFactor = 200;
[X, Y] = ginput(nPoints);
X = scaleFactor * X;
Y = scaleFactor * Y;

% Interpolate trajectory from input points.
xFiner=[];
for idx=1:length(X)-1
    xFiner = [xFiner linspace(X(idx),X(idx+1),numInterpPoints)];
    % Remove the last entry, otherwise it will be repeated in the next
    % cycle
    xFiner(end)=[];
end

% Interpolation
interpY = interp1(X, Y, xFiner, interpType);

% Output
traj.X = xFiner;
traj.Y = interpY;

% Plot coarse linear interpolation
if (doPlot == true)
    plot(X, Y, 'o', 'MarkerSize', 10); hold on;
    plot(xFiner, interpY, ':', 'LineWidth', 3);
end

end

