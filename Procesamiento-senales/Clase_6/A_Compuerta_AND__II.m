clc,
clear,
close all
X = [ -0.5 -0.5 +0.3 -0.1;  ...
      -0.5 +0.5 -0.5 +1.0];
T = [1 1 0 0];
figure
plot(X,T);

net = perceptron;
net = configure(net,X,T);

figure
plot(X,T);
figure
plot(net.IW{1},net.b{1});

XX = repmat(con2seq(X),1,3);
TT = repmat(con2seq(T),1,3);
net = adapt(net,XX,TT);
figure
plot(net.IW{1},net.b{1});

x = [0.7; 1.2];
y = net(x);
plotpv(x,y);
point = findobj(gca,'type','line');
point.Color = 'red';

hold on;
figure
plot(X,T);
figure
plot(net.IW{1},net.b{1});
hold off;