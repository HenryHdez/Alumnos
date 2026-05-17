syms x f(x)
f(x)=(x^3)+(4*x^2)-10;
df(x)=(3*(x^2))+(8*x);
xn=5;
for i=1:10
    xn1=double(xn-f(xn)/df(xn))
    xn=xn1;
end
