import React from 'react';

function MiComponente() {
  const plantillaHTML = `
    <div>
      <h1>¡Hola, mundo desde una plantilla!</h1>
      <p>Este es un párrafo dentro de una plantilla HTML.</p>
      <div>
        <h2>Sección dentro del div</h2>
        <p>Otro párrafo.</p>
      </div>
    </div>
  `;

  return (
    <div dangerouslySetInnerHTML={{ __html: plantillaHTML }} />
  );
}

export default MiComponente;
