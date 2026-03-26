import React, { useState } from 'react';
import Formulario from './Formulario';
import Visualizacion from './Visualizacion';
import Slider from './Barra'

function App() {
  //Elementos del formulario
  const [datosFormulario, setDatosFormulario] = useState({});
  //Poner Form y vis en la misma pag.
  //<Formulario onSubmit={setDatosFormulario} />
  //<Visualizacion datos={datosFormulario} />
  //<Slider/>
  return (
    <div className="App">
      <Slider />
      <Formulario onSubmit={setDatosFormulario} />
      <Visualizacion datos={datosFormulario} />
    </div>
  );
}

export default App;
