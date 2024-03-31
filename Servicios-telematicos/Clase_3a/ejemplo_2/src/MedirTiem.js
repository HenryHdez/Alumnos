import React, { useState } from 'react';
import { MapContainer, TileLayer, Circle} from 'react-leaflet';
import 'leaflet/dist/leaflet.css';

const Estimaciontdeviaje = () => {
  // Coordenadas iniciales para Bogotá
  const [inicio, setInicio] = useState({ lat: 4.7110, lng: -74.0721 });
  const [destino, setDestino] = useState({ lat: 4.7510, lng: -74.0721 });
  const [distancia, setDistancia] = useState(null);
  const [tiempo, setTiempo] = useState(null);

  const calcularRuta = (start, end) => {
    const orsApiKey = '5b3ce3597851110001cf6248ab49b95773b34e8d838a1c6fdbdcf7a5';
    const orsUrl = `https://api.openrouteservice.org/v2/directions/driving-car?api_key=${orsApiKey}&start=${start.lng},${start.lat}&end=${end.lng},${end.lat}`;

    fetch(orsUrl)
      .then(response => response.json())
      .then(data => {
        const distancia = data.features[0].properties.summary.distance; //Distancia en metros
        const tiempoEstimado = distancia / 1000 / 60; 
        setDistancia((distancia / 1000).toFixed(2)); 
        setTiempo(tiempoEstimado.toFixed(2)); 
      })
      .catch(error => {
        console.error('Error al calcular la ruta:', error);
      });
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    calcularRuta(inicio, destino);
  };

  return (
    <div>
      <form onSubmit={handleSubmit}>
        <label>
          Inicio (lat, lng):
          <input type="text" value={`${inicio.lat}, ${inicio.lng}`} onChange={e => setInicio({ lat: parseFloat(e.target.value.split(',')[0]), lng: parseFloat(e.target.value.split(',')[1]) })} />
        </label>
        <label>
          Destino (lat, lng):
          <input type="text" value={`${destino.lat}, ${destino.lng}`} onChange={e => setDestino({ lat: parseFloat(e.target.value.split(',')[0]), lng: parseFloat(e.target.value.split(',')[1]) })} />
        </label>
        <button type="submit">Calcular ruta</button>
      </form>
      {//Estructuras de javascript dentro del codigo
      distancia && (
        <div>
          <p>Distancia: {distancia} km</p>
          <p>Tiempo estimado de viaje (a 60 km/h): {tiempo} horas</p>
        </div>
      )}

      <MapContainer center={[4.7110, -74.0721]} zoom={13} style={{ height: '400px', width: '600px' }}>
        <TileLayer
          url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
          attribution='&copy; OpenStreetMap contributors'
        />
        {inicio.lat && <Circle center={[inicio.lat, inicio.lng]} radius={200} color="red" fillColor="blue" fillOpacity={0.5} />}
        {destino.lat && <Circle center={[destino.lat, destino.lng]} radius={200} color="red" fillColor="green" fillOpacity={0.5} />}
      </MapContainer>
    </div>
  );
};

export default Estimaciontdeviaje;
