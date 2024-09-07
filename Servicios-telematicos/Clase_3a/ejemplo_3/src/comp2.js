import React, { useEffect, useState } from 'react';

function MiComponente2() {
  const [contenidoHTML, setContenidoHTML] = useState('');

  useEffect(() => {
    // Cargar el archivo HTML externo
    fetch(`${process.env.PUBLIC_URL}/plantilla.html`)
      .then(response => response.text())
      .then(data => setContenidoHTML(data));
  }, []);

  return (
    <div dangerouslySetInnerHTML={{ __html: contenidoHTML }} />
  );
}

export default MiComponente2;
