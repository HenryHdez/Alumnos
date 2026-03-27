import { useState } from 'react'
import './App.css'
//Importar modulos
import { sumar, restar } from './Matematicas.js';

function App() {
  const [name, setName] = useState('');
  console.log(sumar(2, 3));
  console.log(restar(2, 3));
  return (
    <>
    <div>
      {/* Comentario en Vite */}
      <h1>¡Bienvenido a Vite!</h1>
      <input
        type="text"
        placeholder="Escribe tu nombre"
        value={name}
        onChange={(e) => setName(e.target.value)}
      />
      <p>{name && `Hola, ${name}`}</p>
    </div>
    </>
  )
}

export default App
