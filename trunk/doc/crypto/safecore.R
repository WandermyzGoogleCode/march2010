H1 = function(n, m, k)
	return (log2(d)*((n-m)/m-((n-m)/n)^D*(n/m+D-1)+D*((n-m)/n)^D*(1-((n-m)/n)^(k-D)))+((n-m)/n)^k*log2(n-k*m));
H2 = function(n, m, k)
	return (log2(d)*((n-m)/m-((n-m)/n)^D*(n/m+D-1)+D*((n-m)/n)^D*(1-((n-m)/n)^(k-D)))+((n-k*m)/n)*log2(n-k*m));
H3 = function(n, m, k)
	return (log2(d)*((n-m)/m-((n-m)/n)^D*(n/m+D-1)+D*((n-m)/n)^D*(1-((n-m)/n)^(k-D)))+((n-m)/n)^(k-1)*((n-k*m)/n)*log2(n-k*m));

H0 = function(n, m, k)
	return (log2(d)*((n-m)/m-((n-m)/n)^D*(n/m+D-1)+D*((n-m)/n)^D*(1-((n-m)/n)^(k-D)))+
		+(n-k*m)/n*log2(n));

n = 2^30;
m = 2^20;
d = 2;
D = log2(n)/log2(d);
SEG = 10000;
x = (D+1)+c(0:(SEG-1))*(n/m-2-D)/SEG;
y1 = H1(n, m, x);
y2 = H2(n, m, x);
y3 = H3(n, m, x);
y0 = H0(n, m, x);

legendStr = paste("min(y1) =", as.character(min(y1)), "\nmin(y2) =", as.character(min(y2)), "\nmin(y3) =", as.character(min(y3)));
title = paste("H(n = 2^", as.character(log2(n)), ", m = 2^", as.character(log2(m)), ", k = x)", sep="");
xlabStr = "x = k";
ylabStr = "y = H(n, m, k); (entropy)"

plot(x, y2, col="blue", type="l", main=title, xlab=xlabStr, ylab=ylabStr);
lines(x, y3, col="red");
lines(x, y1, col="green");
lines(x, y0, col="black");

lines(x, rep(29, SEG)	, col="grey");
lines(c(D, D), c(D, 0), col="grey");

legend("left", legendStr, bty="n");




