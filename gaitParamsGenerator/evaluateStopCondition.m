function [ stop ] = evaluateStopCondition( newStartingPoint, traj )
%EVALUATESTOPCONDITION Summary of this function goes here
%   EVALUATESTOPCONDITION( newStartingPoint, traj )

lastPointInTraj = [traj.X(end), traj.Y(end), 0]';
distVectorToEnd = newStartingPoint - lastPointInTraj ;
distVectorToEndLogical = [distVectorToEnd(1)/abs(distVectorToEnd(1)), distVectorToEnd(2)/abs(distVectorToEnd(2))]';
if ( distVectorToEndLogical(1) > 0 && distVectorToEndLogical(2) > 0 )
    stop = true; 
else
    stop = false;
end

end

