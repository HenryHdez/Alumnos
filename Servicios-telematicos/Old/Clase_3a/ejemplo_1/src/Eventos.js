import React, { useState } from 'react';
import { MapContainer, TileLayer, useMapEvents } from 'react-leaflet';
import 'leaflet/dist/leaflet.css';

const EventMap = () => {
  //Almacenar posición
  //const [mapClickPos, setMapClickPos] = useState(null);

  const MapEvents = () => {
    useMapEvents({
      click(e) {
        
        //setMapClickPos(e.latlng.lat.toFixed(2), e.latlng.lng.toFixed(2));
        //console.log(mapClickPos);
        //Publicar en una alerta
        alert('Haz hecho clic en: '+e.latlng.lat.toFixed(2)+','+e.latlng.lng.toFixed(2));
      }
    });
    return null; 
  };

  return (
    <div>
      <MapContainer center={[4.7110, -74.0721]} zoom={13} style={{ height: '400px', width: '600px' }}>
        <TileLayer
          url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
          attribution='&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
        />
        <MapEvents />
      </MapContainer>
    </div>
  );
};

export default EventMap;
