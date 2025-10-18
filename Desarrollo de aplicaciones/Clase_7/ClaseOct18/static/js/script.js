        //Variables globales
        var variable=0;
        var i=0;
        var text="texto de prueba";
        //funciones
        function funcion1(){
            alert("Hola desde la funcion 1");
            //Estrucuras de control
            if (variable==0){}
            else{}
            for (i=0;i<10;i++){
                console.log(i); //Mostrar en consola
            }
            while (variable<10){
                variable++;
            }
            switch (variable){
                case 0:
                    console.log("Caso 0");
                    break;
                case 1:
                    console.log("Caso 1");
                    break;
                default:
                    console.log("Caso por defecto");
            }
        }
        function funcion2(numero){
            document.getElementById("prueba").innerHTML="el numero es:" + numero;
        }
        function mostrar(){
            document.getElementById("spinwin").style.display="block";
            //var texto2=document.getElementById("Nombre").value;
            //document.getElementById("Nombre").value = texto2+"Cargando...";
        }
        function ocultar(){
            setTimeout(
                document.getElementById("spinwin").style.display="none", 
                5000);
            //document.getElementById("spinwin").style.display="none";
            //document.getElementById("Nombre").value = "Finalizado";
        }