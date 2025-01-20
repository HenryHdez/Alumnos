//Manejo de estados nativo de React
//useState
import Contador from './Manejo1'
//useReducer
import ContadorReducer from './Manejo2'
//Context API
import { TemaProveedor } from './Proveedor';
import SelectorTema from './Consumir';
//Aplicación
import './App.css'

function App() {
  return (
    <>
    {/* 
    <Contador></Contador> 
    */}

    {/* 
    <ContadorReducer></ContadorReducer> 
    */}


    <TemaProveedor>
      <SelectorTema />
    </TemaProveedor>
   
    </>
  )
}

export default App
