//Importar la librería navegación
import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';

function Formulario() {
    //Almacenar el nombre del usuario
    const [nombre, setNombre] = useState('');
    const navigate = useNavigate();
    const handleSubmit = (e) => {
        e.preventDefault();
        //Envia la varible a la ruta datos
        navigate('/datos', { state: { nombre } }); 
    };
    return (
        <form onSubmit={handleSubmit}>
        <label>
            Nombre:
            <input
            type="text"
            value={nombre}
            onChange={e => setNombre(e.target.value)}
            />
        </label>
        <button type="submit">Enviar</button>
        </form>
        );
    }

export default Formulario;
