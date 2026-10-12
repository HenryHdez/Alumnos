import logo from './logo.svg';
import Saludo from './Saludo.js'
import Bob from './Bob.png'
import './App.css';

function App() {
  return (
    <div>
      <Saludo nombre="Henry"/>
      <img src={Bob} width="120" height="150"/>
    </div>
  );
}

export default App;
