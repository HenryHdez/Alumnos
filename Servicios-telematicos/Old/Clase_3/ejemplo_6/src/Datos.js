import React from 'react';
import { useLocation } from 'react-router-dom';

function Datos() {
  const location = useLocation();
  //? Es un operador de encadenamiento y permite leer una propiedad contenida 
  //en un objeto
  //?? Similar a un if devuelve el lado derecho en caso de que no sea nulo
  const nombre = location.state?.nombre ?? 'Nombre no proporcionado';

  return (
    <div>
      <h2>Datos del Formulario</h2>
        <p>Nombre: {nombre}</p>
    </div>
  );
}

export default Datos;
