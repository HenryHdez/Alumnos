import logo from './logo.svg';
import './App.css';
import Mapabasico from'./MapaBasico'
import Marcarmapa from'./Marcadores'
import CrearEvent from'./Eventos'
import SavesMapas from'./Guardar'
import AdvancedLeafletApp from './Advance';
import GeoFenceMap from './ejII'
function App() {
  //<Mapabasico></Mapabasico>
  //<Marcarmapa></Marcarmapa>
  //<CrearEvent></CrearEvent>
  //<SavesMapas></SavesMapas>
  //<AdvancedLeafletApp></AdvancedLeafletApp>
  return (
    <div className="App">
      <GeoFenceMap></GeoFenceMap>
    </div>
  );
}

export default App;
