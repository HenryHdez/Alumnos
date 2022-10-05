function graficar(type) {
    //Leer texto de la ecuación de entrada
    var exp = document.getElementById("ecuacion").value;
    var xValues = [];
    var yValues = [];
    // Generar valores de la ecuación
    for (var x = 0; x <= 10; x += 1) {
      xValues.push(x);
      yValues.push(eval(exp));
    }
    // Mostrar usando la librería plotly
    var mode = "lines";
    if (type == 'scatter') {mode = "markers"}
    var data = [{x:xValues, y:yValues, mode:mode, type:"scatter"}];
    var layout = {title: "y = " + exp};
    Plotly.newPlot("presentar_gra", data, layout);
}

