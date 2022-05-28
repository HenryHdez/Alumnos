function [f,P1,Y]=Fourier(s,Fs)
    L=2^nextpow2(Fs+1);
    Y=fft(s);
    J=Y/sqrt(L);
    P2=abs(Y/L);
    P1=P2(1:(length(P2)/2));
    P1(2:end-1)=2*P1(2:end-1);
    f=Fs*(0:(length(P2)/2)-1)/L;
end

