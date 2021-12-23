clc, clear all
%>>>Diseñe una señal con frecuencia variable<<<<<
Fs=4000;                         %Frecuencia de muestreo
figure(1)                        %(Número de la figura)
t=0:1/Fs:4;                      %Intervalo definido por Fs
y=[sin(200*pi*t(1:end/2)),...    %...Indica que continua
   sin(800*pi*t(end/2:end))];      %Continua
%Grafico
plot(t,y,'linewidth',2);
grid on;title('Señal original');
ylabel('Amplitud');xlabel('Tiempo (s)');
%Definicion de la transformada 
%Tome la longitud del vector 
L=length(y);
%nextpow devuelve la potencia más pequeña de dos, que es mayor o 
%igual que el valor absoluto de L, ya que, el algoritmo de FFT 
%calcula la transformada en potencias de 2.
NFFT=2^nextpow2(L);
%Algoritmo de  transformada rápida de Fourier
Y=fft(y,NFFT)/L;
%Generación del vector de frecuancias disponibles
%Fs/2, es vaido porque el espectro de frecuencia de una señal 
%tiene simetria hermitiana (loque significa que el espectro de 
%valores por encima de Fs/2 se puede obtener del conjugado 
%comlejode los valores por debajo de Fs/2).
%Esta definicion comprende a los valores de NFFT/2+1
%(con el NFFT/2+1 correspondiente a Fs/2).
%Entonces .en lugar de mostrar la información redundante por encima 
%de Fs/2, solo muestra el espectro hasta Fs/2
f=(Fs/2)*linspace(0,1,NFFT/2+1);
%Espectro en frecuencia 
figure(2)
%Imprime la magnitud en un rango de frecuencias
plot(f,2*abs(Y(1:NFFT/2+1)),'linewidth',2);
grid on;title('Espectro de frecuencia');
ylabel('Magnitud |Y(f)|');xlabel('Frecuencia(Hz)');
%Diseño del filtro 
Rp=5;
Rs=20;
Wp=[2*300 2*500]/Fs;
Ws=[2*200 2*600]/Fs;
[N,Wn]=buttord(Wp,Ws,Rp,Rs);
[b,a]=butter(N,Wn);
%Barrido en frecuencia del filtro
f0=0;
f_paso=1;
ff=1000;
f=f0:f_paso:ff;
H=freqz(b,a,f,Fs);
figure(3)
plot(f,abs(H),'linewidth',2);
grid on; title('Filtro pasabanda');
xlabel('Frecuencia (Hz)');ylabel('Amplitud');
%>>>>>Filtrado de una señal<<<<<<
Filtrada=filter(b,a,y);
%Transformada de Fourier de la señal obtenida
L=length(Filtrada);
NFFT=2^nextpow2(L);
Y=fft(Filtrada,NFFT)/L;
f=(Fs/2)*linspace(0,1,NFFT/2+1);
%Espectro en frecuencia
figure(4)
plot(f,2*abs(Y(1:NFFT/2+1)),'linewidth',2);
grid on; title('Espectro en frecuencia');
ylabel('Magnitud |Y(f)|');xlabel('Frecuencia(Hz)');
%Señal filtrada en el dominio del tiempo
figure(5)
plot(t,Filtrada,'linewidth',2);
grid on;
ylabel('Amplitud');xlabel('Frecuencia(Hz)');