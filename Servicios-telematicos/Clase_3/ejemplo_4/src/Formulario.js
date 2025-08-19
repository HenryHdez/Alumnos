import React, { useState } from 'react';

function Formulario({ onSubmit }) {
  const [nombre, setNombre] = useState('');

  const handleSubmit = (e) => {
    e.preventDefault();
    onSubmit({ nombre });
    setNombre('');
  };

  return (
    <form onSubmit={handleSubmit}>
      <label>
        Nombre:
        <input
          type="text"
          value={nombre}
          onChange={(e) => setNombre(e.target.value)}
        />
      </label>
      <button type="submit">Enviar</button>
    </form>
  );
}

export default Formulario;
