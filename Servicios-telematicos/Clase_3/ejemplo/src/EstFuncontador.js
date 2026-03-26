import React, { useState } from 'react';

//UseState presevar el valor de una variable

function Contador() {
  const [contador, setContador] = useState(0);
  
  return (
    <div>
      <p>He hecho click {contador} veces</p>
      <button onClick={() => setContador(contador + 1)}>
        Click
      </button>
    </div>
  );
}

export default Contador;