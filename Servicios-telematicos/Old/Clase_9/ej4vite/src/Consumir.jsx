import React, { useContext } from 'react';
import { TemaContexto } from './Proveedor';
function SelectorTema() {
  const { tema, setTema } = useContext(TemaContexto);

  return (
    <div>
      <h1>Tema actual: {tema}</h1>
      <button onClick={() => setTema(tema === 'claro' ? 'oscuro' : 'claro')}>
        Cambiar Tema
      </button>
    </div>
  );
}

export default SelectorTema;