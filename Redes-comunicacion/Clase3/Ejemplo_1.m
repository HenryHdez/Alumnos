clear, clc, close all
N=1024;         %Total de muestras
Fs=800;         %Frecuencia de muestreo [Hz]
Ts=1/Fs;        %Periodo de muestreo [s]
t=(0:N-1).*Ts;  %Vector de muestras

figure(1)
%% Señal moduladora
m=1;            %indice de modulación
Fmod=10;        %Frecuencia señal moduladora
Amod=5;         %Amplitud señal moduladora
s_mod=Amod*sin(2*pi*Fmod.*t);
subplot(2,2,1)
plot(t,s_mod); title('señal moduladora');
xlabel('tiempo'); ylabel('Amplitud');

%% Señal portadora
Apor=Amod/m; %Amplitud de la señal portadora
Fpor=150; %Frecuencia de la señal portadora
s_por=Apor*cos(2*pi*Fpor.*t);
subplot(2,2,2)
plot(t,s_por); title('Señal portadora');
xlabel('tiempo'); ylabel('Amplitud');

%% Modulación AM (DSB-SC)
s_mod_1=ammod(s_mod,Fpor,Fs,0,Apor);
subplot(2,2,3)
plot(t,s_mod_1); title('Señal modulada');
xlabel('tiempo'); ylabel('Amplitud');

%% Espectro de frecuencias (DSB-SC)
[fx, s_f]=Fourier(s_mod_1,Fs);
subplot(2,2,4)
plot(fx,s_f); grid on; title('Espectro de frecuencias');
xlabel('Frecuencia [Hz]'); ylabel('Amplitud');

figure(2)
%% Modulación AM (SSB-upper)
s_mod_2=ssbmod(s_mod,Fpor,Fs,0,'upper');
subplot(1,2,1), plot(t,s_mod_2); title('banda lateral única')
%% Espectro de frecuencias (SSB-upper)
[fx, s_f]=Fourier(s_mod_2,Fs);
subplot(1,2,2), plot(fx,s_f); title('Espectro de frecuencias (up)')

%% Demodulación
[num, den]=butter(5,Fpor*2/Fs);
[h, w]=freqz(num, den);
figure, plot(w,abs(h));
sdemod=amdemod(s_mod_1,Fpor,Fs,0,Apor,num,den);
figure, plot(t,sdemod); title('Señal demodulada')


