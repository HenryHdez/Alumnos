import React, { useState } from 'react';
import { MapContainer, TileLayer, useMapEvents, Polygon, Circle } from 'react-leaflet';
import 'leaflet/dist/leaflet.css';

const EventMap = () => {
  //Almacenar posición
  const [mapClickPos, setMapClickPos] = useState([4.7110, -74.0721]);
  var polygonPuntos = [
    [4.7110, -74.1721]
  ];
  const MapEvents = () => {
    useMapEvents({
      click(e) {
        polygonPuntos=[...polygonPuntos,[parseFloat(e.latlng.lat.toFixed(2)), parseFloat(e.latlng.lng.toFixed(2))]]
        //setMapClickPos(()=>[...mapClickPos,[e.latlng.lat.toFixed(2), e.latlng.lng.toFixed(2)]]);
        console.log(polygonPuntos);
        //Publicar en una alerta
        //alert('Haz hecho clic en: '+e.latlng.lat.toFixed(2)+','+e.latlng.lng.toFixed(2));

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
        <Circle center={circleCentro} radius={400} color={'red'} />
        <MapEvents />
      </MapContainer>
    </div>
  );
};

export default EventMap;
