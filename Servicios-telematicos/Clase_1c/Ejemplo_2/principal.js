//Use la función require para importar de otro módulo
//Mi_lista_importada=require('./constantes')
//Multiples atributos
const {Lista_exportar, Cantidad_veces} = require('./constantes')

//Publique el contenido de la lista usando la consola
for(var i=0;i<Lista_exportar.length;i++){
    console.log(Lista_exportar[i]);
}
console.log(Cantidad_veces)

