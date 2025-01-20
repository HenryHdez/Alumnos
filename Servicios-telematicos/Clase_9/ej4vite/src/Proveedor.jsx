//Proveedor del contexto
import React, { createContext, useState } from 'react';
// Crear el contexto
export const TemaContexto = createContext();
// Proveedor del contexto
export function TemaProveedor({ children }) {
  const [tema, setTema] = useState('claro');

  return (
    <TemaContexto.Provider value={{ tema, setTema }}>
      {children}
    </TemaContexto.Provider>
  );
}
