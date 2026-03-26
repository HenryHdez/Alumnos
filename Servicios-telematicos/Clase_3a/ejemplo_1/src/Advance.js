import React, { useMemo, useState } from "react";
import {
  MapContainer,
  TileLayer,
  Marker,
  Popup,
  Polyline,
  useMap,
  useMapEvents,
  CircleMarker,
} from "react-leaflet";
import L from "leaflet";
import "leaflet/dist/leaflet.css";

// Corrige el icono por defecto de Leaflet en muchos proyectos React
delete L.Icon.Default.prototype._getIconUrl;
L.Icon.Default.mergeOptions({
  iconRetinaUrl: "https://unpkg.com/leaflet@1.9.4/dist/images/marker-icon-2x.png",
  iconUrl: "https://unpkg.com/leaflet@1.9.4/dist/images/marker-icon.png",
  shadowUrl: "https://unpkg.com/leaflet@1.9.4/dist/images/marker-shadow.png",
});

// Distancia Haversine en kilómetros
const haversineDistance = (p1, p2) => {
  const toRad = (deg) => (deg * Math.PI) / 180;
  const R = 6371; // km

  const dLat = toRad(p2.lat - p1.lat);
  const dLng = toRad(p2.lng - p1.lng);

  const a =
    Math.sin(dLat / 2) ** 2 +
    Math.cos(toRad(p1.lat)) *
      Math.cos(toRad(p2.lat)) *
      Math.sin(dLng / 2) ** 2;

  const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
  return R * c;
};

// Componente para mover el mapa a un punto seleccionado
const FlyToPoint = ({ selectedPoint }) => {
  const map = useMap();

  React.useEffect(() => {
    if (selectedPoint) {
      map.flyTo([selectedPoint.lat, selectedPoint.lng], 15, {
        duration: 1.2,
      });
    }
  }, [selectedPoint, map]);

  return null;
};

// Captura eventos del mapa
const MapEvents = ({ onAddPoint }) => {
  useMapEvents({
    click(e) {
      onAddPoint(e.latlng);
    },
  });

  return null;
};

const AdvancedLeafletApp = () => {
  const bogota = { lat: 4.711, lng: -74.0721 };

  const [points, setPoints] = useState([]);
  const [selectedPoint, setSelectedPoint] = useState(null);

  // Agregar punto al hacer clic
  const handleAddPoint = (latlng) => {
    const newPoint = {
      id: Date.now(),
      lat: Number(latlng.lat.toFixed(6)),
      lng: Number(latlng.lng.toFixed(6)),
      createdAt: new Date().toLocaleTimeString(),
    };

    setPoints((prev) => [...prev, newPoint]);
  };

  // Eliminar punto por id
  const handleDeletePoint = (id) => {
    setPoints((prev) => prev.filter((p) => p.id !== id));
    setSelectedPoint((prev) => (prev?.id === id ? null : prev));
  };

  // Coordenadas para Polyline
  const polylinePositions = useMemo(
    () => points.map((p) => [p.lat, p.lng]),
    [points]
  );

  // Distancia total recorrida
  const totalDistanceKm = useMemo(() => {
    if (points.length < 2) return 0;

    let total = 0;
    for (let i = 1; i < points.length; i++) {
      total += haversineDistance(points[i - 1], points[i]);
    }
    return total;
  }, [points]);

  return (
    <div
      style={{
        display: "grid",
        gridTemplateColumns: "320px 1fr",
        gap: "16px",
        alignItems: "start",
        fontFamily: "Arial, sans-serif",
      }}
    >
      {/* Panel lateral */}
      <div
        style={{
          padding: "16px",
          border: "1px solid #dcdcdc",
          borderRadius: "12px",
          background: "#f8f9fa",
          height: "600px",
          overflowY: "auto",
        }}
      >
        <h2 style={{ marginTop: 0 }}>Gestión de puntos</h2>

        <p>
          <strong>Puntos registrados:</strong> {points.length}
        </p>
        <p>
          <strong>Distancia total:</strong> {totalDistanceKm.toFixed(3)} km
        </p>

        <div style={{ display: "flex", gap: "8px", marginBottom: "16px" }}>
          <button
            onClick={() => setPoints([])}
            style={{
              padding: "10px 14px",
              borderRadius: "8px",
              border: "none",
              cursor: "pointer",
            }}
          >
            Limpiar ruta
          </button>

          <button
            onClick={() => setSelectedPoint(bogota)}
            style={{
              padding: "10px 14px",
              borderRadius: "8px",
              border: "none",
              cursor: "pointer",
            }}
          >
            Ir al centro
          </button>
        </div>

        <hr />

        {points.length === 0 ? (
          <p>No hay puntos aún. Haga clic sobre el mapa para agregarlos.</p>
        ) : (
          <div>
            {points.map((point, index) => (
              <div
                key={point.id}
                style={{
                  padding: "10px",
                  marginBottom: "10px",
                  border: "1px solid #ccc",
                  borderRadius: "10px",
                  background: "#fff",
                }}
              >
                <p style={{ margin: "0 0 6px 0" }}>
                  <strong>Punto {index + 1}</strong>
                </p>
                <p style={{ margin: "0 0 6px 0" }}>Lat: {point.lat}</p>
                <p style={{ margin: "0 0 6px 0" }}>Lng: {point.lng}</p>
                <p style={{ margin: "0 0 10px 0" }}>Hora: {point.createdAt}</p>

                <div style={{ display: "flex", gap: "8px" }}>
                  <button
                    onClick={() => setSelectedPoint(point)}
                    style={{
                      padding: "8px 12px",
                      borderRadius: "8px",
                      border: "none",
                      cursor: "pointer",
                    }}
                  >
                    Ver en mapa
                  </button>

                  <button
                    onClick={() => handleDeletePoint(point.id)}
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
        )}
      </div>

      {/* Mapa */}
      <div>
        <MapContainer
          center={[bogota.lat, bogota.lng]}
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
            attribution='&copy; OpenStreetMap contributors'
          />

          <MapEvents onAddPoint={handleAddPoint} />
          <FlyToPoint selectedPoint={selectedPoint} />

          {/* Punto base */}
          <CircleMarker
            center={[bogota.lat, bogota.lng]}
            radius={8}
            pathOptions={{ color: "blue" }}
          >
            <Popup>Centro inicial: Bogotá</Popup>
          </CircleMarker>

          {/* Marcadores */}
          {points.map((point, index) => (
            <Marker
              key={point.id}
              position={[point.lat, point.lng]}
              eventHandlers={{
                dblclick: () => handleDeletePoint(point.id),
                click: () => setSelectedPoint(point),
              }}
            >
              <Popup>
                <div>
                  <strong>Punto {index + 1}</strong>
                  <br />
                  Lat: {point.lat}
                  <br />
                  Lng: {point.lng}
                  <br />
                  Hora: {point.createdAt}
                  <br />
                  <br />
                  <em>Doble clic para eliminar</em>
                </div>
              </Popup>
            </Marker>
          ))}

          {/* Ruta */}
          {points.length > 1 && (
            <Polyline positions={polylinePositions} pathOptions={{ color: "red" }} />
          )}
        </MapContainer>
      </div>
    </div>
  );
};

export default AdvancedLeafletApp;