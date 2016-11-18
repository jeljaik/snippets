function [ aCum, bCum, hLow, hUp ] = ComputeLowerAndUpperBounds( interpolatedSteps, gaitBasicParams, time, doPlot )
%COMPUTELOWERANDUPPERBOUNDS Summary of this function goes here
%   [ aCum, bCum ] = ComputeLowerAndUpperBounds( interpolatedSteps, gaitBasicParams, time, doPlot )


% a_0 = [a0_0, a1_0];
% ...
% a_k = [a0_k, a1_k];
%
% b_0 = [b0_0, b1_0];
% ...
% b_k = [b0_k, b1_k];

%%
aCum = [];
bCum = [];
feetCenters.RightFoot = {};
feetCenters.LeftFoot = {};
footLength = gaitBasicParams.footLength;
footWidth = gaitBasicParams.footWidth;
beta = atan(footWidth/footLength);

%% Compute feet centers for each time
for i=1:length(interpolatedSteps.LeftFootCoordinates)
    if (~isempty(interpolatedSteps.LeftFootCoordinates{i}))
        positionLeft = interpolatedSteps.LeftFootCoordinates{i}.position;
        alphaLeft = deg2rad(interpolatedSteps.LeftFootCoordinates{i}.rotationDeg);
    else
        positionLeft = [];
        alphaLeft = [];
    end
    if (~isempty(interpolatedSteps.RightFootCoordinates{i}))
        positionRight = interpolatedSteps.RightFootCoordinates{i}.position;
        alphaRight = deg2rad(interpolatedSteps.RightFootCoordinates{i}.rotationDeg);
    else
        positionRight = [];
        alphaRight = [];
    end
    if ( ~isempty(interpolatedSteps.LeftFootCoordinates{i}) && ~isempty(interpolatedSteps.RightFootCoordinates{i}) )
        % if standing in double support
        feetCenters.LeftFoot{end+1} = computeCenterVector(positionLeft, alphaLeft, beta, footWidth, footLength);
        feetCenters.RightFoot{end+1} = computeCenterVector(positionRight, alphaRight, beta, footWidth, footLength);
        [a, b] = doComputeLowerAndUpperBounds(feetCenters.LeftFoot{end}, feetCenters.RightFoot{end});
    else if ( isempty(interpolatedSteps.LeftFootCoordinates{i}) )
            % else if ... standing on right foot
            feetCenters.LeftFoot{end+1} = [];
            feetCenters.RightFoot{end+1} = computeCenterVector(positionRight, alphaRight, beta, footWidth, footLength);
            [a, b] = doComputeLowerAndUpperBounds([], feetCenters.RightFoot{end});
        else if ( isempty(interpolatedSteps.RightFootCoordinates{i}) )
                %else if ... standing on left foot
                feetCenters.LeftFoot{end+1} = computeCenterVector(positionLeft, alphaLeft, beta, footWidth, footLength);
                feetCenters.RightFoot{end+1} = [];
                [a, b] = doComputeLowerAndUpperBounds(feetCenters.LeftFoot{end}, []);
            end
        end
    end
    
    aCum(i,:) = a;
    bCum(i,:) = b;
    
end

figure;
subplot(211);
if (doPlot)
    plot(time, aCum(:,1), '-o', 'MarkerSize', 3); hold on;
    plot(time, bCum(:,1), '-o', 'MarkerSize', 3);
end
title('Lower bounds $a_0$, $b_0$', 'Interpreter', 'latex'); axis tight;
h = legend('$a_0$', '$b_0$');
set(h,'Interpreter', 'latex');
hLow = gcf;

figure;
subplot(211);
if (doPlot)
    plot(time, aCum(:,2), '-o', 'MarkerSize', 3); hold on;
    plot(time, bCum(:,2), '-o', 'MarkerSize', 3);
end
title('Upper bounds $a_1$, $b_1$','Interpreter','latex'); axis tight;
h=legend('$a_1$','$b_1$');
set(h,'Interpreter','latex');
hUp = gcf;

end

function centerVector = computeCenterVector(position, alpha, beta, w, l)
% COMPUTECENTERVECTOR(position, alpha, beta, w, l)
% Computes the center vector (in world reference frame) for a single
% footstep.
centerVector = position + sqrt(w^2 + l^2)*[cos(alpha + beta); sin(alpha+beta); 0];
end

function [a, b] = doComputeLowerAndUpperBounds( leftFootCenter, rightFootCenter)
% DOCOMPUTELOWERANDUPPERBOUNDS(leftFootCenter, rightFootCenter)

if (isempty(leftFootCenter))
    a(1) = rightFootCenter(1);
    b(1) = a(1);
    a(2) = rightFootCenter(2);
    b(2) = a(2);
else if (isempty(rightFootCenter))
        a(1) = leftFootCenter(1);
        b(1) = a(1);
        a(2) = leftFootCenter(2);
        b(2) = a(2);
    end
end

if (~isempty(leftFootCenter) && ~isempty(rightFootCenter))
    if (leftFootCenter(1) > rightFootCenter(1))
        a(1) = leftFootCenter(1);
        b(1) = rightFootCenter(1);
    else
        a(1) = rightFootCenter(1);
        b(1) = leftFootCenter(1);
    end
    
    if (leftFootCenter(2) > rightFootCenter(2))
        a(2) = leftFootCenter(2);
        b(2) = rightFootCenter(2);
    else
        a(2) = rightFootCenter(2);
        b(2) = leftFootCenter(2);
    end
end

end

