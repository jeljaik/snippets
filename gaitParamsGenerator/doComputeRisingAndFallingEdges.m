function [ output ] = doComputeRisingAndFallingEdges( a )
%DOCOMPUTERISINGANDFALLINGEDGES Summary of this function goes here
%   Detailed explanation goes here

output = zeros(length(a),1);

% Identify where there's a rising or falling edge and set output to one
    
for idx = 2:length(a)
    if a(idx-1) < a(idx) || a(idx-1) > a(idx)
        output(idx) = 1;
    end
end

end

