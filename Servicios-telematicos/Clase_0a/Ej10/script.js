// Detectar si estamos en la página del formulario
if (document.getElementById('formulario')) {
    document.getElementById('formulario').addEventListener('submit', function(event) {
        event.preventDefault(); // Evita que se recargue la página

        // Obtener valores del formulario
        const nombre = document.getElementById('nombre').value;
        const email = document.getElementById('email').value;

        // Redirigir a la otra página con los valores en la URL
        window.location.href = `resultado.html?nombre=${encodeURIComponent(nombre)}&email=${encodeURIComponent(email)}`;
    });
}
//` (Backticks)	Permiten interpolación de variables, cadenas multilínea y son más flexibles.

// Detectar si estamos en la página de resultados
if (document.getElementById('mostrarNombre')) {
    // Obtener parámetros de la URL
    const params = new URLSearchParams(window.location.search);
    const nombre = params.get('nombre');
    const email = params.get('email');

    // Mostrar los valores en la página
    document.getElementById('mostrarNombre').textContent = nombre ? nombre : "No se recibió nombre";
    document.getElementById('mostrarEmail').textContent = email ? email : "No se recibió correo";
}
