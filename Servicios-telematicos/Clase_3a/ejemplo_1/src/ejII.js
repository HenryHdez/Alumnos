import React, { useState } from "react";
import {
  MapContainer,
  TileLayer,
  Marker,
  Popup,
  Circle,
  useMapEvents,
  useMap,
} from "react-leaflet";
import L from "leaflet";
import "leaflet/dist/leaflet.css";

// Corrección del icono por defecto en React + Leaflet
delete L.Icon.Default.prototype._getIconUrl;
L.Icon.Default.mergeOptions({
  iconRetinaUrl: "https://unpkg.com/leaflet@1.9.4/dist/images/marker-icon-2x.png",
  iconUrl: "https://unpkg.com/leaflet@1.9.4/dist/images/marker-icon.png",
  shadowUrl: "https://unpkg.com/leaflet@1.9.4/dist/images/marker-shadow.png",
});

// Componente para mover el mapa a un punto
const FlyToLocation = ({ point }) => {
  const map = useMap();

  React.useEffect(() => {
    if (point) {
      map.flyTo([point.lat, point.lng], 15, { duration: 1.2 });
    }
  }, [point, map]);

  return null;
};

// Captura clics en el mapa
const MapClickHandler = ({ onAddMarker }) => {
  useMapEvents({
    click(e) {
      onAddMarker(e.latlng);
    },
  });

  return null;
};

const GeoFenceMap = () => {
  const initialCenter = [4.711, -74.0721];

  const [markers, setMarkers] = useState([
    {
      id: 1,
      name: "Nodo 1",
      lat: 4.711,
      lng: -74.0721,
      radius: 300,
    },
    {
      id: 2,
      name: "Nodo 2",
      lat: 4.715,
      lng: -74.065,
      radius: 450,
    },
  ]);

  const [selectedMarker, setSelectedMarker] = useState(null);
  const [radiusValue, setRadiusValue] = useState(300);

  const addMarker = (latlng) => {
    const newMarker = {
      id: Date.now(),
      name: `Nodo ${markers.length + 1}`,
      lat: Number(latlng.lat.toFixed(6)),
      lng: Number(latlng.lng.toFixed(6)),
      radius: radiusValue,
    };

    setMarkers((prev) => [...prev, newMarker]);
    setSelectedMarker(newMarker);
  };

  const deleteMarker = (id) => {
    setMarkers((prev) => prev.filter((m) => m.id !== id));
    if (selectedMarker?.id === id) {
      setSelectedMarker(null);
    }
  };

  const updateRadius = (id, newRadius) => {
    setMarkers((prev) =>
      prev.map((m) =>
        m.id === id ? { ...m, radius: Number(newRadius) } : m
      )
    );

    if (selectedMarker?.id === id) {
      setSelectedMarker((prev) => ({ ...prev, radius: Number(newRadius) }));
    }
  };

  return (
    <div
      style={{
        display: "grid",
        gridTemplateColumns: "340px 1fr",
        gap: "16px",
        fontFamily: "Arial, sans-serif",
      }}
    >
      <div
        style={{
          border: "1px solid #ccc",
          borderRadius: "12px",
          padding: "16px",
          background: "#f7f7f7",
          height: "600px",
          overflowY: "auto",
        }}
      >
        <h2 style={{ marginTop: 0 }}>Panel de geocercas</h2>

        <div style={{ marginBottom: "16px" }}>
          <label>
            <strong>Radio para nuevos nodos (m): </strong>
          </label>
          <input
            type="number"
            value={radiusValue}
            onChange={(e) => setRadiusValue(e.target.value)}
            style={{
              width: "100%",
              marginTop: "8px",
              padding: "8px",
              borderRadius: "8px",
              border: "1px solid #bbb",
            }}
          />
        </div>

        <p>
          <strong>Total de nodos:</strong> {markers.length}
        </p>

        <hr />

        {markers.map((marker) => (
          <div
            key={marker.id}
            style={{
              border: "1px solid #ddd",
              borderRadius: "10px",
              padding: "12px",
              marginBottom: "12px",
              background:
                selectedMarker?.id === marker.id ? "#eaf4ff" : "#ffffff",
            }}
          >
            <p style={{ margin: "0 0 6px 0" }}>
              <strong>{marker.name}</strong>
            </p>
            <p style={{ margin: "0 0 6px 0" }}>Lat: {marker.lat}</p>
            <p style={{ margin: "0 0 6px 0" }}>Lng: {marker.lng}</p>
            <p style={{ margin: "0 0 6px 0" }}>Radio: {marker.radius} m</p>

            <label>
              <strong>Ajustar radio:</strong>
            </label>
            <input
              type="range"
              min="100"
              max="2000"
              step="50"
              value={marker.radius}
              onChange={(e) => updateRadius(marker.id, e.target.value)}
              style={{ width: "100%", marginTop: "8px", marginBottom: "10px" }}
            />

            <div style={{ display: "flex", gap: "8px" }}>
              <button
                onClick={() => setSelectedMarker(marker)}
                style={{
                  padding: "8px 12px",
                  borderRadius: "8px",
                  border: "none",
                  cursor: "pointer",
                }}
              >
                Seleccionar
              </button>

              <button
                onClick={() => deleteMarker(marker.id)}
                style={{
                  padding: "8px 12px",
                  borderRadius: "8px",
                  border: "none",
                  cursor: "pointer",
                }}
              >
                Eliminar
              </button>
            </div>
          </div>
        ))}
      </div>

      <MapContainer
        center={initialCenter}
        zoom={13}
        style={{
          height: "600px",
          width: "100%",
          borderRadius: "12px",
          overflow: "hidden",
        }}
      >
        <TileLayer
          url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
          attribution="&copy; OpenStreetMap contributors"
        />

        <MapClickHandler onAddMarker={addMarker} />
        <FlyToLocation point={selectedMarker} />

        {markers.map((marker) => (
          <React.Fragment key={marker.id}>
            <Marker
              position={[marker.lat, marker.lng]}
              eventHandlers={{
                click: () => setSelectedMarker(marker),
              }}
            >
              <Popup>
                <div>
                  <strong>{marker.name}</strong>
                  <br />
                  Lat: {marker.lat}
                  <br />
                  Lng: {marker.lng}
                  <br />
                  Radio: {marker.radius} m
                </div>
              </Popup>
            </Marker>

            <Circle
              center={[marker.lat, marker.lng]}
              radius={marker.radius}
              pathOptions={{
                color: selectedMarker?.id === marker.id ? "red" : "blue",
                fillOpacity: 0.2,
              }}
            />
          </React.Fragment>
        ))}
      </MapContainer>
    </div>
  );
};

export default GeoFenceMap;