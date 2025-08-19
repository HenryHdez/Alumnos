import React, { useState, useEffect } from 'react';

function BarraProgreso() {
  const [progreso, setProgreso] = useState(0);
  
  //Temporizador para incrementar el valor de la barra
  useEffect(() => {
    const intervalo = setInterval(() => {
      setProgreso(progresoActual => {
        const nuevoProgreso = progresoActual + 10;
        if (nuevoProgreso >= 100) {
          clearInterval(intervalo);
          return 100;
        }
        return nuevoProgreso;
      });
    }, 1000);
    return () => clearInterval(intervalo);
  }, []);

  //style={{ width: `${progreso}%` }} define la barra en terminos de porcentaje
  //{progreso}% se usa para mostrar el valor
  return (
    <div className="progress">
      <div
        className="progress-bar"
        role="progressbar"
        style={{ width: `${progreso}%` }}
        aria-valuenow={progreso}
        aria-valuemin="0"
        aria-valuemax="100"
      >
        {progreso}%
      </div>
    </div>
  );
}

export default BarraProgreso;
