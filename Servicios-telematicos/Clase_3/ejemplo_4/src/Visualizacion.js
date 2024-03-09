import React from 'react';

function Visualizacion({ datos }) {
  return (
    <div>
      <h2>Datos del Formulario</h2>
      <p>Nombre: {datos.nombre}</p>
    </div>
  );
}

export default Visualizacion;