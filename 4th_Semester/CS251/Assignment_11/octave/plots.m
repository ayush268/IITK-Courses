X=[1:10]
Y=X.^3


hold on;
plot(X, Y);

xlabel ("X");
ylabel ("cube(X)");
title ("Graph for f(x) = x^3");

print -dpdf "fig1.pdf";
close

ndist = randn(5000, 1);
hold on;
hist(ndist, 50);
print -dpdf "fig2.pdf";
close;


v=[1:8];
v1=[1,0, 1, 0 , 1, 0, 1, 0];
hold on;

pie(v, v1)
print -dpdf "fig3.pdf";
close;

