import React, { useState, useEffect } from 'react';

function TemporizadorConBotones() {
  const [segundos, setSegundos] = useState(0);
  const [activo, setActivo] = useState(false);
  //SetSegundos o setActivo son funciones
  useEffect(() => {
    let intervalo = null;
    if (activo) {
      intervalo = setInterval(() => {
        setSegundos((segundos) => segundos + 1);
      }, 1000);
    } else if (!activo && segundos !== 0) {
      clearInterval(intervalo);
    }
    return () => clearInterval(intervalo);
  }, [activo, segundos]);

  const iniciarTemporizador = () => {
    setActivo(true);
  };

  const detenerTemporizador = () => {
    setActivo(false);
  };

  return (
    <div>
      <h2>Temporizador</h2>
      <p>{segundos} segundos</p>
      <button onClick={iniciarTemporizador} disabled={activo}>Iniciar</button>
      <button onClick={detenerTemporizador} disabled={!activo}>Detener</button>
    </div>
  );
}

export default TemporizadorConBotones;
