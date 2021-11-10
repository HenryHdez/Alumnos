clc, clear;
x=random('Uniform',0,1,10,5);
media=mean(x);
mejor=min(x);
peor=max(x);
desv=std(x);
errorbar(media,desv,'r')
grid on
hold on
plot(media,'linewidth',2);
plot(mejor,'.-','linewidth',2);
plot(peor,'--','linewidth',2);
grid on
