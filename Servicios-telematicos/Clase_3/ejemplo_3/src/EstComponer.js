import React from 'react';

//Funcion componente usuario
function Usuario(props) {
  return <div>Usuario: {props.nombre}</div>;
}

//Crear lista a partir de la función contigua
function Listausuarios() {
  return (
    <div>
      <Usuario nombre="Hugo" />
      <Usuario nombre="Juan" />
      <Usuario nombre="Helena" />
    </div>
  );
}

export default Listausuarios;