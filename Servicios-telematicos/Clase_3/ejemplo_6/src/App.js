import React from 'react';
//Importar buscador de rutas
import { BrowserRouter, Routes, Route } from 'react-router-dom';
//Importar componentes
import Formulario from './Formulario'; 
import Datos from './Datos'; 

function App() {
  return (
    //Configuración de las rutas
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Formulario />} /> // Inicio
        <Route path="/datos" element={<Datos />} /> // Otras rutas
      </Routes>
    </BrowserRouter>
  );
}

export default App;
