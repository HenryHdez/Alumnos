disp('Diga un comando para reconocer ("arriba", "abajo", "hola")');
rec = audiorecorder(fs, 16, 1);
recordblocking(rec, 2);
test = getaudiodata(rec);
audiowrite('test.wav', test, fs);
