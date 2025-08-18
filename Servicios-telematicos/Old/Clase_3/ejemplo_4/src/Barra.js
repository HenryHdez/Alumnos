import React, { useState } from 'react';

function Slider() {
  //Valor inicial del Slider 50
  const [value, setValue] = useState(50);

  const handleChange = (e) => {
    setValue(e.target.value);
  };

  return (
    <div>
      <input
        type="range"
        min="0"
        max="100"
        value={value}
        onChange={handleChange}
      />
      <p>Valor: {value}</p>
    </div>
  );
}

export default Slider;
