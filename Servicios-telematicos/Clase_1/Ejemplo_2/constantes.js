//Lista del archivo principal
Mi_lista=['uno', 'dos', 'alegre', 'gato'];
Cantidad_veces=2500
//Instrucción utilizada para exportar de un modulo a otro.
//Modo 1= Nombre atributo:Nombre variable
module.exports={Lista_exportar:Mi_lista,
//Modo 2= Nombre variable
                Cantidad_veces};

//Algunas funciones de interes
module.exports={atributo_1:Nombre_variable, atributo_2}
const{atributo_1, atributo_2}=require('./ruta+Nombre archivo')
var Nombre_lista=['ele 1', 'ele 2', '...'];
if(condicion){console.log('tal cosa');}
for(var i=0; i<Nombre_lista.length; i++){console.log('tal cosa ...');}

