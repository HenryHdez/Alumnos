function animacionSeno()
    % Crear una figura para la animación
    figure;
    x = linspace(0, 2*pi, 100);
    y = sin(x);
    
    % Bucle para animar el gráfico
    for k = 1:100
        % Actualizar los datos y para la animación
        y = sin(x + k * 0.1);
        
        % Graficar los datos actualizados
        plot(x, y);
        axis([0 2*pi -1 1]); % Establecer límites de los ejes
        title('Onda Senoidal Animada');
        xlabel('x');
        ylabel('sin(x + k * 0.1)');
        
        % Actualizar la figura
        drawnow;
        
        % Pausar por una corta duración para visualizar la animación
        pause(0.1);
    end
end

clc;
clear;
close all;
animacionSeno();


