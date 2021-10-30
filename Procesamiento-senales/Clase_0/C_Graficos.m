clear, clc
t=-pi/2:0.1:pi/2;
y=cos(t);
%plot(t,y) %Solito
grid on
plot(t,y,'linewidth',2) %Con mayor grosor en la línea
%axis([0,10,0,1])
xlabel('tiempo')
ylabel('Amplitud')
legend('Coseno');
%Estilos
%Línea punteada
plot(t,y,'--','linewidth',2)
%Línea bolita
plot(t,y,'-o','linewidth',2)
%Línea  y punto
plot(t,y,'-.','linewidth',2)
%Línea verde y punto
plot(t,y,'g-.','linewidth',2)
%Línea negra y punto
plot(t,y,'k-.','linewidth',2)