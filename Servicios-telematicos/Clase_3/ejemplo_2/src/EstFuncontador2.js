import React, { useState } from 'react';

//UseState preserva el valor de una variable
//Imlementen {{}} cuando sea nesesario

function Contador2() {
  const [contador, setContador] = useState(0);
  if (contador < 10) {
    return (
      <div>
        <p style={{ color: 'blue' }}>He hecho click {contador} veces</p>
        <button onClick={() => setContador(contador + 1)}>
          Click
        </button>
      </div>
    );
  } else {
    return (
      <div>
        <p style={{ color: 'red' }}>He hecho click {contador} veces</p>
        <button onClick={() => setContador(contador + 1)}>
          Click
        </button>
      </div>
    );
  }
}

export default Contador2;
