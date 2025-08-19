//Estados complejos con lógica
import React, { useReducer } from 'react';

// Reducer y estado inicial
const estadoInicial = { contador: 0 };

function Acciones(estado, accion) {
  switch (accion.tipo) {
    case 'incrementar':
      return { contador: estado.contador + 1 };
    case 'decrementar':
      return { contador: estado.contador - 1 };
    default:
      throw new Error('Acción desconocida');
  }
}

function ContadorReducer() {
  const [estado, despachar] = useReducer(Acciones, estadoInicial);

  return (
    <div>
      <h1>Contador: {estado.contador}</h1>
      <button onClick={() => despachar({ tipo: 'incrementar' })}>Incrementar</button>
      <button onClick={() => despachar({ tipo: 'decrementar' })}>Decrementar</button>
    </div>
  );
}

export default ContadorReducer;
