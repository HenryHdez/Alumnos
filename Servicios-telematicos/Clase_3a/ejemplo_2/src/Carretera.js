import React, { useState } from 'react';
import { MapContainer, TileLayer, useMapEvents, Circle } from 'react-leaflet';
import 'leaflet/dist/leaflet.css';

const Rutarecta = () => {
  const [markers, setMarkers] = useState([]);

  const agregarmarker = (latlng) => {
    setMarkers([...markers, latlng]);
    if (markers.length === 1) {
      // Una vez que tenemos dos puntos, calcular la ruta
      calcularRuta(markers[0], latlng);
    }
  };

  const calcularRuta = (start, end) => {
    const orsApiKey = '5b3ce3597851110001cf62487140c01fee1143f9a3aef575c7645a07';
    const orsUrl = `https://api.openrouteservice.org/v2/directions/driving-car?api_key=${orsApiKey}&start=${start.lng},${start.lat}&end=${end.lng},${end.lat}`;
    //Fetch lee el archivo resultado
    fetch(orsUrl)
      .then(response => response.json())
      .then(data => {
        const distance = data.features[0].properties.summary.distance; // Distancia en metros
        alert(`Distancia en linea recta: ${(distance / 1000).toFixed(2)} km`);
      })
      .catch(error => {
        console.error('Error al calcular la ruta:', error);
      });
  };

  const MapEvents = () => {
    useMapEvents({
      click(e) {
        if (markers.length < 2) {
          agregarmarker(e.latlng);
        }
      }
    });
    return null;
  };

  return (
    <MapContainer center={[4.7110, -74.0721]} zoom={13} style={{ height: '400px', width: '600px' }}>
      <TileLayer
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
        attribution='&copy; OpenStreetMap contributors'
      />
      <MapEvents />
      {markers.map((position, idx) => (
        <Circle center={position} radius={200} color="red" fillColor="blue" fillOpacity={0.5}/>
      ))}
    </MapContainer>
  );
};

export default Rutarecta;
