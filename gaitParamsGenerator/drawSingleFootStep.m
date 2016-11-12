function [ verticesCCW ] = drawSingleFootStep( startingPosition, rotation, gaitBasicParams )
%DRAWSINGLEFOOTSTEP Draws a single footstep.
%
%   verticesCCW = DRAWSINGLEFOOTSTEP( startingPosition, rotation, gaitBasicParams )
%   draws a single footstep from a lower-left-corner initial vertex. The
%   parameter rotation will rotate the rectangle provided the angle is in
%   degrees. Type 1 Rotations (123) are assumed and to happen only around
%   the z frame (point out of the screen).
%   
%   verticesCCW is a structure with the following elements:
%   v1: Equals startingPosition
%   v2: Second vertex of the step rectangle in a CCW direction.
%   v3: Third vertex of the step rectangle in a CCW direction.
%   v4: Fourth vertex of the step rectangle in a CCW direction.
%       
%         -----------------
%        |                 |
%        |                 |
%        |                 |
%        X-----------------
% 
% "X" in the previous drawing corresponds to the input startingPoint.
%

footLength = gaitBasicParams.footLength;
footWidth = gaitBasicParams.footWidth;
% There is a "minus" before the rotation angle in order to rotation as if
% the z axis was pointing out of the screen.
rotMatrix = SpinCalc('EA123toDCM',[0,0,-rotation],[],1);
v1  = startingPosition;
v2r = v1 + rotMatrix * [footLength 0 0]';
v3r = v1 + rotMatrix * [footLength footWidth 0]';
v4r = v1 + rotMatrix * [0 footWidth 0]';

X = [v1(1); v2r(1); v3r(1); v4r(1)];
Y = [v1(2); v2r(2); v3r(2); v4r(2)];

verticesCCW.v1 = v1;
verticesCCW.v2 = v2r;
verticesCCW.v3 = v3r;
verticesCCW.v4 = v4r;

patch(X,Y,zeros(length(Y),1), 'FaceColor','blue','FaceAlpha',.5);
axis equal;
end

