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

