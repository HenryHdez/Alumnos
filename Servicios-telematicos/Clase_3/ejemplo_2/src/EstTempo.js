import React, { useState, useEffect } from 'react';

//Useeffect se invoca dentro del cuerpo del componente. Puede ejecutarse después de cada renderizado completado 

function Temporizador() {
  const [segundos, setSegundos] = useState(0);

  useEffect(() => {
    //Fijar intervalo de temporización
    const intervalo = setInterval(() => {
      setSegundos(segundosPrevios => segundosPrevios + 1);
    }, 1000);

    // Eliminar componente cuando se desmonta
    return () => clearInterval(intervalo);
  }, []); // No hay variables dependientes

  return (
    <div>
      <h2>Temporizador</h2>
      <p>{segundos} Segundos.</p>
    </div>
  );
}

export default Temporizador;
