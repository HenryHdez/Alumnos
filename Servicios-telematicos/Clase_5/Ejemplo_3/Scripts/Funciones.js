function draw() {
    //Leer desde el HTML el objeto canvas
    var canvas = document.getElementById('canvas');
    //Si el canvas existe haga
    if (canvas.getContext) {
        //Defina una variable donde dibujar
        var lienzo = canvas.getContext('2d');
        //Defina el color a utilizar
        lienzo.fillStyle = 'rgb(200, 0, 0)';
        //Dibuja un rectángulo
        lienzo.fillRect(10, 10, 50, 50);
        //Dibuja un arco
        //arc(pos x, pos y, radio, ángulo inicio, ángulo fin, sentido horario?);
        var apertura1=Math.PI;
        var apertura2=Math.PI;
        lienzo.fillStyle = 'rgb(0, 0, 0)';
        lienzo.arc(70, 70, 20, 0, apertura1, 0);
        lienzo.stroke();
        lienzo.fillStyle = 'rgb(0, 200, 0)';
        lienzo.arc(100, 100, 40, 0, apertura2, 1);
        lienzo.fill();
        //Dibujar texto (Texto, pos x, pos y)
        lienzo.font = "30px Arial";
        lienzo.fillText("Hola curso", 40, 50); 
        lienzo.strokeText("Curso 2", 30, 70); 
        // Gradiente de color
        var grd = lienzo.createLinearGradient(0, 0, 200, 0);
        grd.addColorStop(0, "red");
        grd.addColorStop(1, "white");
        // Llene algo con el gradiente
        lienzo.fillStyle = grd;
        lienzo.fillRect(10, 10, 150, 80); 
    }
}
