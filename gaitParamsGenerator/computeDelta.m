function [ deltaCum ] = computeDelta( alphaCum, betaCum, time, hLow, hUp, doPlot)
%COMPUTEDELTA Summary of this function goes here
%   Detailed explanation goes here

deltaCum = zeros(length(alphaCum),1);

for idx = 1:length(alphaCum)
    if ( (alphaCum(idx,1) == 1 &&  (alphaCum(idx,1) == alphaCum(idx,2))) || (betaCum(idx,1) == 1 && (betaCum(idx,1) == betaCum(idx,2))))
        deltaCum(idx:end) = 1;
    else if ((betaCum(idx,2) == 1 && (betaCum(idx,2) == alphaCum(idx,1))) || (alphaCum(idx,2) ==1 && (alphaCum(idx,2) == betaCum(idx,1))))
            deltaCum(idx:end) = 0;
        end
    end
end
    
if doPlot
    plotDeltaCum(hLow,time,deltaCum);
    plotDeltaCum(hUp,time,deltaCum);
end

    function [] = plotDeltaCum(h,time,deltaCum)
        figure(h);
        subplot(414);
        plot(time, deltaCum,'-o','MarkerSize',3);
        title('Potential change from DS to SS','Interpreter','latex');
        h=legend('$\delta$');
        set(h,'Interpreter','latex');
        xlabel('time (s)');
        axis tight;
    end


end

