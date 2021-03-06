function [ alphaCum, betaCum ] = computeRisingAndFallingEdges( aCum, bCum, time, hLow, hUp )
%COMPUTERISINGANDFALLINGEDGES Summary of this function goes here
%   [ alphaCum, betaCum ] = computeRisingAndFallingEdges( aCum, bCum, hLow, hUp )

%% Rising edges of a0 and a1
alphaCum(:,1) = doComputeRisingAndFallingEdges(aCum(:,1));
alphaCum(:,2) = doComputeRisingAndFallingEdges(aCum(:,2));

%% Falling edges of b0 and b1
betaCum(:,1) = doComputeRisingAndFallingEdges(bCum(:,1));
betaCum(:,2) = doComputeRisingAndFallingEdges(bCum(:,2));

figure(hLow);
subplot(412);
plot(time, [alphaCum(:,1), betaCum(:,1)],'-o','MarkerSize',3);
title('Shape Constraints $\alpha$, $\beta$','Interpreter','latex');
h=legend('$\alpha_0$','$\beta_0$');
set(h,'Interpreter','latex');
axis tight;

figure(hUp);
subplot(412);
plot(time, [alphaCum(:,2), betaCum(:,2)], '-o','MarkerSize',3);
title('Shape Constraints $\alpha$, $\beta$','Interpreter','latex');
h = legend('$\alpha_1$','$\beta_1$');
set(h,'Interpreter','latex');
axis tight;
end
