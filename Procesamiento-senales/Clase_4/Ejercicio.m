[y, Fs]=audioread('bosque.mp3');
figure(1)
plot(y(:,1))
%Transformada de Fourier de la señal obtenida
L=length(y);
NFFT=2^nextpow2(L);
Y=fft(Filtrada,NFFT)/L;
f=(Fs/2)*linspace(0,1,NFFT/2+1);
%Espectro en frecuencia
figure(2)
plot(f,2*abs(Y(1:NFFT/2+1)),'linewidth',2);
grid on; title('Espectro en frecuencia');
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