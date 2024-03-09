import React, { useState } from 'react';

function Agregarnomlista() {
  //Estado de nombre y función para de asignación
  const [nombre, setNombre] = useState('');
  //Estado de los nombres agregados a la lista
  const [nombres, setNombres] = useState([]); 

  // Función para agregar nombre al estado
  const Agregarnomevt = (e) => {
    setNombre(e.target.value);
  };

  // Agrega el nombre actual al select y limpia el campo de entrada
  const agregarNombre = () => {
    if (nombre !== '') {
      //...nombres Crea una copia de nombres y agrega nombre 
      setNombres([...nombres, nombre]);
      // Limpia el campo de entrada
      setNombre('');
  };
  }
  return (
    <div>
      <input
        type="text"
        value={nombre}
        onChange={Agregarnomevt}
        placeholder="Introduce un nombre"
      />
      <button onClick={agregarNombre}>Agregar</button>
      <select>
        {nombres.map((nombre, index) => (
          <option key={index} value={nombre}>{nombre}</option>
        ))}
      </select>
    </div>
  );
}

export default Agregarnomlista;
