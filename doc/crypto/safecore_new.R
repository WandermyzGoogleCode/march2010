Pndb = function(D, d, m)
	return (1-m^2/(2^D-2^(d-1)+1));
Pmdb = function(D, d)
	return (1-(d*2^(2*d-2)+d*2^(d-1))/(2^D-1));
d_l = 0;
d_r = 16;
SEG = 1000;
d = c(0:SEG-1)/SEG*(d_r-d_l)+d_l;
D = 36;
Hb = function(D, d, m)
	return (Pndb(D, d, m)*Pmdb(D, d)*d*(1-m^2/(2^D-d*m+1)));
Hlm = function(lm)
	return (Hb(D, d, 2^lm));

y14 = Hlm(14);
y15 = Hlm(15);
y16 = Hlm(16);
y17 = Hlm(17);
	
legendStr = paste("max(m = 2^14) =", as.character(max(y14)), 
		  "\nmax(m = 2^15) =", as.character(max(y15)), 
		  "\nmax(m = 2^16) =", as.character(max(y16)), 
		  "\nmax(m = 2^17) =", as.character(max(y17)));
xlabStr = "x = d";
ylabStr = "y = H"	
	
plot(d, y14, type="l", xlab = xlabStr, ylab = ylabStr);
lines(d, y15);
lines(d, y16);
lines(d, y17);
legend("topleft", legendStr, bty="n");
