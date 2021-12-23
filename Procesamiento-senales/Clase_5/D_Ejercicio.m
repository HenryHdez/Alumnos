clc, clear
%Defina los arreglos de prueba
x=[4,2,1,3,7];
y=[8,9,2,4,5];
% Grafique los resultados
figure (1)
% haga una auto correlación normalizada
subplot (2,2,1)
x1=x;
y1=y;
[rnxy,m]=xcorr(x1,y1,'normalized');
stem(m,rnxy,'linewidth',2);grid on;


%Haga una correlación cruzada entre los vectores
subplot(2,2,2)
x2=x;
y2=y;
[rnxy,m]=xcorr(x2,y2,'normalized');
stem(m,rnxy,'linewidth',2);grid  on;
xlabel('m');ylabel('Amplitud');title('Diferentes I')
axis([-5,5,0,1]);
%Haga una correlación cruzada frente a un factor
subplot(2,2,3)
x3=x;
y3=x.*rand(1,length(x));
[rnxy,m]=xcorr(x3,y3,'normalized');
stem(m,rnxy,'linewidth',2);grid  on;
xlabel('m');ylabel('Amplitud');title('Diferentres II')
axis([-5,5,0,1]);
%Haga una correlación cruzada frente a un sumando
subplot(2,2,4)
x4=x;
y4=x+random('Normal',0,1,1,length(x));
[rnxy,m]=xcorr(x4,y4,'normalized');
stem(m,rnxy,'linewidth' ,2);grid  on;
xlabel('m');ylabel('Amplitud');title('Diferentres III')
axis([-5,5,0,1]);

