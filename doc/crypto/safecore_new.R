Pndb = function(D, d, m)
	return (1-m^2/(2^D-2^(d-1)+1));
Pmdb = function(D, d)
	return (1-(d*2^(2*d-2)+d*2^(d-1))/(2^D-1));
d_l = 0;
d_r = 14;
SEG = 1000;
d = c(0:SEG-1)/SEG*(d_r-d_l)+d_l;
D = 32;
Hb = function(D, d, m)
	return (Pndb(D, d, m)*Pmdb(D, d)*d*(1-m^2/(2^D-d*m+1)));
Hlm = function(lm)
	return (Hb(D, d, 2^lm));

y1 = Hlm(12);
y2 = Hlm(13);
y3 = Hlm(14);
y4 = Hlm(15);
	
legendStr = paste("black:\n  max(H | m = 2^12) =", as.character(max(y1)), 
		  "\nblue:\n  max(H | m = 2^13) =", as.character(max(y2)), 
		  "\ngreen:\n  max(H | m = 2^14) =", as.character(max(y3)), 
		  "\nred:\n  max(H | m = 2^15) =", as.character(max(y4)));
xlabStr = "d";
ylabStr = "H(X | Y_d)"	
	
plot(d, y1, type="l", xlab = xlabStr, ylab = ylabStr, col="black");
lines(d, y2, col="blue");
lines(d, y3, col="green");
lines(d, y4, col="red");
legend(-1, y = 14, legendStr, bty="n");
