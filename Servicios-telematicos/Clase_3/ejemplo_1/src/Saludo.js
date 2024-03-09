// En src/Saludo.js
import React from 'react';

function Saludo(props) {
    return (
      <div>
        <h1>Hola, {props.nombre}</h1>
        <p>Este texto corresponde a un parrafo</p>
      </div>
    );
  }

export default Saludo;