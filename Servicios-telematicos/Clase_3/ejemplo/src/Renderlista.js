import React from 'react';

function ListaNombres(props) {
  const nombres = ['Ana', 'Paco', 'Helena', 'Luis'];
  return (
    //Uso particular de la función map
    <ul>
      {nombres.map((nombre, index) => (
        <li key={index}>{nombre}</li>
      ))}
    </ul>
  );
}

export default ListaNombres;