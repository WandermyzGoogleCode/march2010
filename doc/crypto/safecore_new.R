Pndb = function(D, d, m)
	return (1-(2^(d-1)*m*d)/(2^D-m+1));
Pmdb = function(D, d)
	return (1-(d*2^(2*d-2)+d*2^(d-1))/(2^D-1));
d_l = 0;
d_r = 14;
SEG = 14;
d = c(0:(SEG-1))/SEG*(d_r-d_l)+d_l;
D = 32;
Hb = function(D, d, m)
	return (Pndb(D, d, m)*Pmdb(D, d)*d*(1-d*m^2/(2^D-m+1)));
Hlm = function(lm)
	return (Hb(D, d, 2^lm));

y1 = Hlm(11);
y2 = Hlm(12);
y3 = Hlm(13);
y4 = Hlm(14);
	
legendStr = c(paste("max(H | m = 2^11) =", as.character(max(y1))), 
		  paste("max(H | m = 2^12) =", as.character(max(y2))), 
		  paste("max(H | m = 2^13) =", as.character(max(y3))), 
		  paste("max(H | m = 2^14) =", as.character(max(y4)))
)

xlabStr = "d";
ylabStr = "H(X | Y_d)"	
	
plot(d, y1, type="b", xlab = xlabStr, ylab = ylabStr, pch=1);
lines(d, y2, type="b", pch=24);
lines(d, y3, type="b", pch=20);
lines(d, y4, type="b", pch=0);
legend(-0.5, 12, legendStr, bty="n", pch=c(1, 24, 20, 0), cex=1.2);
