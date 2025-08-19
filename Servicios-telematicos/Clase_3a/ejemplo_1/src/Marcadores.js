import React from 'react';
import { MapContainer, TileLayer, Popup, Circle, Polygon } from 'react-leaflet';
import 'leaflet/dist/leaflet.css';

const ShapesMap = () => {
  const centro = [4.7110, -74.0721];
  const circleCentro = [4.7110, -74.1821];
  const polygonPuntos = [
    [4.7110, -74.1721],
    [4.7212, -74.1821],
    [4.7313, -74.1921],
    [4.7313, -74.5921],
  ];

  return (
    <MapContainer center={centro} zoom={10} style={{ height: '400px', width: '600px' }}>
      <TileLayer
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
        attribution='&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
      />
      <Popup position={centro}>Aviso emergente</Popup>
      <Circle center={circleCentro} radius={400} color={'red'} />
      <Polygon positions={polygonPuntos} />
    </MapContainer>
  );
};

export default ShapesMap;

