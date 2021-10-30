const {edad,veces}=require('./modulo1');
const tiempo=require('./modulo2');
Usuarios=['Juan','Miguel','Sofia','Viviana'];
Usuario_seleccionado='Viviana';
for(var i=0;i<Usuarios.length;i++){
    if(Usuarios[i]==Usuario_seleccionado){
        console.log('El usuario seleccionado fue: '+Usuarios[i]+
        ', tiene una edad de: '+edad[i]+
        ', sale de su casa: '+veces[i]+' veces al día'+
        ' y el tiempo de actividad fisica es: '+tiempo[i]+' minutos'
        );
    }
}