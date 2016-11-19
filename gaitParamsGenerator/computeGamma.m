function [ gammaCum ] = computeGamma( interpolatedSteps, time, hLow, hUp, doPlot )
%COMPUTEGAMMA Summary of this function goes here
%   [ gammaCum ] = computeGamma( interpolatedSteps, time, doPlot )

gammaCum = zeros(length(time),1);
for i=1:length(interpolatedSteps.LeftFootCoordinates)
    if (~isempty(interpolatedSteps.LeftFootCoordinates{i}) && ~isempty(interpolatedSteps.RightFootCoordinates{i}))
        gammaCum(i) = 1;
    end
end

if (doPlot)
    plotGammaCum(hLow, time, gammaCum);
    plotGammaCum(hUp, time, gammaCum);
end

    function [] = plotGammaCum(h,time,gammaCum)
        figure(h);
        subplot(413);
        plot(time, gammaCum,'-o','MarkerSize',3);
        title('Support Phase 1: DS, 0:SS','Interpreter','latex');
        h=legend('$\gamma$');
        set(h,'Interpreter','latex');
        axis tight;
    end

end

