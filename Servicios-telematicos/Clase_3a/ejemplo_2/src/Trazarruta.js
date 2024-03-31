import React, { useState, useEffect } from 'react';
import { MapContainer, TileLayer, Polyline } from 'react-leaflet';
import 'leaflet/dist/leaflet.css';

const Mapaconruta = () => {
  const [ruta, setRuta] = useState([]);

  const inicio = { lat: 4.7110, lng: -74.0721 }; 
  const destino = { lat: 4.5981, lng: -74.0760 }; 

  useEffect(() => {
    const orsApiKey = '5b3ce3597851110001cf6248ab49b95773b34e8d838a1c6fdbdcf7a5';
    const orsUrl = `https://api.openrouteservice.org/v2/directions/driving-car?api_key=${orsApiKey}&start=${inicio.lng},${inicio.lat}&end=${destino.lng},${destino.lat}`;

    fetch(orsUrl)
      .then(response => response.json())
      .then(data => {
        const ruta = data.features[0].geometry.coordinates.map(coord => [coord[1], coord[0]]);
        setRuta(ruta);
      })
      .catch(error => {
        console.error('Error al obtener la ruta:', error);
      });
  }, []);

  return (
    <MapContainer center={[4.7110, -74.0721]} zoom={9} style={{ height: '400px', width: '600px' }}>
      <TileLayer
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
        attribution='&copy; OpenStreetMap contributors'
      />
      {ruta.length > 0 && <Polyline positions={ruta} color="blue" />}
    </MapContainer>
  );
};

export default Mapaconruta;
