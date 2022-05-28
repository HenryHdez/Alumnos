clear, clc, close all
N=1024;         %Total de muestras
Fs=1000;        %Frecuencia de muestreo [Hz]      
Ts=1/Fs;        %Periodo de muestreo [s]
t=(0:N-1).*Ts;  %Vector de muestras 

figure(1)
%% Señal moduladora
Fmod=60;       
Amod=1;        
s_mod=Amod*sin(2*pi*Fmod.*t);
subplot(2,2,1)
plot(t,s_mod); title('señal moduladora');
xlabel('tiempo'); ylabel('Amplitud');

%% Modulación FM
Fc=200;     %Frecuencia portadora
Fdev=50;    %Desviación de la frecuencia de la señal modulada
s_mod_1=fmmod(s_mod,Fc,Fs,50);
subplot(2,2,2)
plot(t,s_mod_1); title('Señal modulada');
xlabel('tiempo'); ylabel('Amplitud');

%% Espectro de frecuencias
[fx, s_f]=Fourier(s_mod_1,Fs);
subplot(2,2,3)
plot(fx,s_f); grid on; title('Espectro de frecuencias');
xlabel('Frecuencia [Hz]'); ylabel('Amplitud');

%% Demodulación
sdemod=fmdemod(s_mod_1,Fc,Fs,50);
subplot(2,2,4)
plot(t,sdemod); title('Señal demodulada')


