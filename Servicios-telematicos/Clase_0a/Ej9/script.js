// Seleccionar el botón del menú y la lista de enlaces
const menuToggle = document.getElementById('menu-toggle');
const navLinks = document.getElementById('nav-links');

// Agregar evento de clic al botón del menú
menuToggle.addEventListener('click', () => {
    navLinks.classList.toggle('active'); // Activa/desactiva el menú
});
