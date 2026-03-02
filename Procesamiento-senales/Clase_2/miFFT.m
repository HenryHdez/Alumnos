function [f,P1,Y] = miFFT(x,Fs)
% miFFT  Calcula y muestra la FFT unilateral de una señal.
%   [f,P1,Y] = miFFT(x)        usa Fs = 1 Hz por defecto.
%   [f,P1,Y] = miFFT(x,Fs)     especifica frecuencia de muestreo Fs (Hz).
%
%   Salidas:
%     f  - vector de frecuencias (Hz) para la amplitud unilateral
%     P1 - amplitud unilateral |X(f)|
%     Y  - FFT completa (complejo)
%
%   El gráfico muestra la señal original y la amplitud unilateral.

if nargin < 2 || isempty(Fs)
    Fs = 1;
end

x = x(:).';                 % asegurar fila
L = length(x);
nfft = 2^nextpow2(L);       % opcional: mejora resolución y eficiencia

Y = fft(x, nfft);
P2 = abs(Y / nfft);
P1 = P2(1:nfft/2+1);
P1(2:end-1) = 2 * P1(2:end-1);

f = Fs * (0:(nfft/2)) / nfft;

% Plots
figure;
subplot(2,1,1)
n = 0:L-1;
stem(n,x,'filled'); grid on;
title('Señal original'); xlabel('n'); ylabel('x[n]')

subplot(2,1,2)
plot(f,P1); grid on;
title('Amplitud unilateral del espectro');
xlabel('Frecuencia (Hz)'); ylabel('|X(f)|');

end
