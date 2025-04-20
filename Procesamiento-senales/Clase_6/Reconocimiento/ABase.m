%Grabar comandos base "Repetir intensamente"
comandos = {'arriba', 'abajo', 'hola'};
fs = 16000;

for i = 1:length(comandos)
    disp(['Diga la palabra: ', comandos{i}]);
    rec = audiorecorder(fs, 16, 1);
    recordblocking(rec, 2);
    audio = getaudiodata(rec);
    audiowrite([comandos{i}, '.wav'], audio, fs);
end
