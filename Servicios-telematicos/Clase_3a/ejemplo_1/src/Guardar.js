import React, { useRef } from 'react';
import { MapContainer, TileLayer } from 'react-leaflet';
import 'leaflet/dist/leaflet.css';
import domToImage from 'dom-to-image';
import { saveAs } from 'file-saver';

const GuardarMapa = () => {
  //Mpara de referencia
  const Maparefe = useRef(null);
  //Guardar mapa función
  const Guardar = () => {
    if (Maparefe.current) {
      Maparefe.current.whenReady(() => {
        const mapElement = Maparefe.current.getContainer();
        domToImage.toBlob(mapElement)
          .then(blob => {
            saveAs(blob, 'mapa.png');
          })
          .catch(error => {
            console.error('Error al convertir el mapa en imagen:', error);
          });
      });
    }
  };

  return (
    <div>
      <MapContainer
        center={[4.7110, -74.0721]} // Coordenadas de Bogotá
        zoom={12}
        style={{ height: '400px', width: '600px' }}
        ref={Maparefe}
      >
        <TileLayer
          url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
          attribution="&copy; OpenStreetMap contributors"
        />
      </MapContainer>
      <button onClick={Guardar}>Guardar Mapa</button>
    </div>
  );
};

export default GuardarMapa;
