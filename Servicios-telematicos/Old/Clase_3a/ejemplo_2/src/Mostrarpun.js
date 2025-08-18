import React, { useState } from 'react';
import { MapContainer, TileLayer, useMapEvents, Circle } from 'react-leaflet';
import 'leaflet/dist/leaflet.css';

const MostrarPunto = () => {
    //Guardar puntos
    const [puntos, setPuntos] = useState([]);

    const agregarPunto = (latlng) => {
        setPuntos([...puntos, latlng]);
    };

    const MapEvents = () => {
        useMapEvents({
            click(e) {
            agregarPunto(e.latlng);
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
      {puntos.map((position, idx) => (
        <Circle key={idx} center={position} radius={200} color="red" fillColor="blue" fillOpacity={0.5} />
      ))}
    </MapContainer>
  );
};

export default MostrarPunto;
