t=-pi:0.1:pi;
A=sin(t);
B=cos(t);
C=log(t);
MA=[A;B;C];
disp(rref(MA))