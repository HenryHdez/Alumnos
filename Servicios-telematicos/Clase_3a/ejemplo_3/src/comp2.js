import React, { useState, useEffect } from 'react'; 

/*fetch
fetch() es una función integrada en JavaScript que permite hacer peticiones HTTP 
(como GET, POST, etc.) a servidores, archivos u otras APIs.
Devuelve una promesa que se resuelve con la respuesta de la red.
fetch(url)
  .then(response => response.text())  // o response.json()
  .then(data => {
    // trabajar con los datos
  })
  .catch(error => {
    // manejar errores
  });
*/

// Definir un componente funcional llamado MiComponente2
function MiComponente2() {
  // Declarar un estado para almacenar el contenido HTML que cargaremos desde un archivo externo
  const [contenidoHTML, setContenidoHTML] = useState('');

  // useEffect se ejecuta automáticamente una vez después de que el componente se monta
  useEffect(() => {
    // Usar fetch para cargar un archivo HTML desde la carpeta "public" del proyecto
    fetch(`${process.env.PUBLIC_URL}/plantilla.html`)
      .then(response => response.text())      // Convertir la respuesta del servidor a texto
      .then(data => setContenidoHTML(data));  // Guardar el contenido del archivo en el estado
  }, []); 
  // El arreglo vacío [] asegura que esto solo se ejecute una vez al montar el componente

  return (
    <div dangerouslySetInnerHTML={{ __html: contenidoHTML }} />
  );
}

export default MiComponente2;
