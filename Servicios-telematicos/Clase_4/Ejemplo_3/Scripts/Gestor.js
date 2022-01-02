var i = 0;
function Rotar_Imagenes(){
    var Lista=['imagenes/Bodegon_1.jpg',
               'imagenes/Bodegon_2.jpg',
               'imagenes/Bodegon_3.jpg',
               'imagenes/Bodegon_4.jpg']
//forEach les permite recorrer una lista elemento por elemento
/*    Lista.forEach(function(v,i,l){
        //v es el valor actual de la lista
        //i es el indice del valor
        //l es el arreglo
        console.log(v);
    });*/
    document.getElementById("imagen").src = Lista[i];
    i++;
    if(i>=Lista.length){i=0;}
}

