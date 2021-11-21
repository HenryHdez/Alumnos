%TRANSFORMADA RAPIDA DE FOURIER
%Generacion de la señal de prueba 
L=1500;              %Cantidad de muestras
n=(0:L-1);           %Etiqueta de las muestras
x=sin(8*pi*n)*rand;  %Amplitud de las muestras
subplot(2,1,1)
stem(n,x);grid on;title('Original');
xlabel('n');ylabel('x[n]')
%Calculo de la transformada rapida de Fourier
Y=fft(x);
%Caldulo de la amplitud del espectro (bilateral +/-)
P2=abs(Y/L);
%Hay que extraer la mitad del vector de amplitudes
%,ya que, los datos se duplican al ser bilateral
P1=P2(1:L/2+1);
P1(2:end-1)=2*P1(2:end-1);
f=(0:(L/2));
subplot(2,1,2)
plot(f,P1);grid on;title('Amplitud unilateral del espectro');
xlabel('Frecuencia (Hz)');ylabel('|X(k)|');
 