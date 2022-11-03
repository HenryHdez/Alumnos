%Definición del vector de entrada y salida
%Combinaciones de la entrada
x = [0 0 1 1; 0 1 0 1];
%Combinaciones de la salida
t = [0 0 0 1];
%Definición de la red
red = perceptron;
%Parámetros de entrenamiento
red.trainParam.epochs = 20;  %Iteraciones
red.trainParam.goal = 0.001; %Parada
%Entrenamiento
red = train(red,x,t);
%Simulación de la red
%Todas las combinaciones
y = red(x);
disp(y)
%Predecir una sola combinación
y = red([1;0]);
disp(y)

URL='https://cad.onshape.com/documents/e10d659a8f9e4103eb49aa50/w/15d5b228a48037828996c863/e/6b42e2cef0994c3c832af116'
RUTA='C:\Users\usuario\Desktop\www\'
XML=smexportonshape(URL, 'FolderPath', RUTA);

nom=strcat(RUTA,'\',XML)
smimport(nom)