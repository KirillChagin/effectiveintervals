function rejeegplot = effints2eegplot( rej, rejE, pnts, color)
	rej  = find(rej>0);
	rejE = rejE(:, rej)';
   	rejeegplot = zeros(length(rej), size(rejE,2)+5);
   	rejeegplot(:, 6:end) = rejE;
   	rejeegplot(:, 1) = (rej(:)-1)*pnts;
   	rejeegplot(:, 2) = rej(:)*(pnts-1)-1;
   	rejeegplot(:, 3:5) = ones(size(rejeegplot,1),1)*color;
return