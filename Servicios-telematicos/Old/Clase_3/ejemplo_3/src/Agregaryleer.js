import React, { useState } from 'react';

function Agregarseleccion() {
  //Funciones; Agregar nombres, agregar opciones y mostrar selección
  const [nombre, setNombre] = useState(''); 
  const [opciones, setOpciones] = useState([]); 
  const [seleccion, setSeleccion] = useState(''); 

  //Función para agregar opción al select.
  const agregarOpcion = () => {
    //Filtra duplicados o vacíos
    if (nombre && !opciones.includes(nombre)) {
      setOpciones([...opciones, nombre]);
      //Limpiar entrada
      setNombre('');
    }
  };

  //Almacenar opción seleccionada
  const cambiarSeleccion = (e) => {
    setSeleccion(e.target.value);
  };

  //ublicar opción seleccionada
  const publicarSeleccion = () => {
    //Use backticks (`) para incrustar texto
    alert(`Opción seleccionada: ${seleccion}`);
  };

  return (
    <div>
      <input
        type="text"
        value={nombre}
        onChange={(e) => setNombre(e.target.value)}
        placeholder="Introduce un nombre"
      />

      <button onClick={agregarOpcion}>Agregar</button>

      <select onChange={cambiarSeleccion} value={seleccion}>
        <option value="">Selecciona una opción</option>
        {opciones.map((opcion, index) => (
          <option key={index} value={opcion}>{opcion}</option>
        ))}
      </select>

      <button onClick={publicarSeleccion} disabled={!seleccion}>Publicar</button>

    </div>
  );
}

export default Agregarseleccion;