import React, { useState } from 'react';
import Formulario from './Formulario';
import Visualizacion from './Visualizacion';
//import Slider from './Barra'

function App() {
  //Elementos del formulario
  const [datosFormulario, setDatosFormulario] = useState({});
  //<Formulario onSubmit={setDatosFormulario} />
  //<Visualizacion datos={datosFormulario} />
  //<Slider/>
  return (
    <div className="App">
      <Formulario onSubmit={setDatosFormulario} />
      <Visualizacion datos={datosFormulario} />
    </div>
  );
}

export default App;
