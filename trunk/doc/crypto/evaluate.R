Pndb = function(D, d, m)
	return (1-(2^(d-1)*m*d)/(2^D-m+1));
Pmdb = function(D, d)
	return (1-(d*2^(2*d-2)+d*2^(d-1))/(2^D-1));
D = 32;
x = c(1:14);
pb = function(D, d, m)
	return (Pndb(D, d, m)*Pmdb(D, d)*(1-d*m^2/(2^D-m+1)));
plm = function(lm)
	return (pb(D, x, 2^lm));

d11 = read.csv("11.csv");
d13 = read.csv("13.csv");
d14 = read.csv("14.csv");
p11 = plm(11);
p13 = plm(13);
p14 = plm(14);

GO13 = function(){
	plot(x, p13, type="b", xlab="number of lucky updates: d", 
		ylab="possibility: p1*p2*p3", pch=0, cex.lab=1.2);
	lines(d13, type="b", pch=3);
	legend(1, 0.8, c("experimental result", "simple lower bound"), 
		bty="n", pch=c(3, 0), cex=1.2);
	dev.copy2eps();
}

GO14 = function(){
	plot(x, p14, type="b", ylim=c(0,1), xlab="number of lucky updates: d", 
		ylab="possibility: p1*p2*p3", cex.lab=1.2, pch=0);
	lines(d14, type="b", pch=3);
	legend(2, 0.3, c("experimental result", "simple lower bound"), 
		bty="n", pch=c(3, 0), cex=1.2);
	dev.copy2eps();
}

GO11 = function(){
	plot(x, p11, type="b", xlab="number of lucky updates: d", 
		ylab="possibility: p1*p2*p3", cex.lab=1.2, pch=0);
	lines(d11, type="b", pch=3);
	legend(1, 0.9, c("experimental result", "simple lower bound"), 
		bty="n", pch=c(3, 0), cex=1.2);
	dev.copy2eps();
}
