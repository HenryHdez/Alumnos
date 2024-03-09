import Bob from './Bob.png';
import './App.css';
import Saludo from './Saludo'

function App() {
  return (
    <div>
    <Saludo nombre="Mundo" />
    <div className="App">
      <h1>Mi página</h1>
      <img src={Bob} width="120" height="150"/>
      <p>Este es un parrafo de hola mundo.</p>
    </div>
    </div>

  );
}

export default App;
