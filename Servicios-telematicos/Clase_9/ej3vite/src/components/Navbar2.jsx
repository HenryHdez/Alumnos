import React from 'react';
import { Navbar, Nav, Container } from 'react-bootstrap';

export default function NavigationBar() {
  return (
    <Navbar bg="dark" variant="dark" expand="lg" fixed="top">
      <Container>
        <Navbar.Brand href="#">Mi App</Navbar.Brand>
        <Navbar.Toggle aria-controls="navbarResponsive" />
        <Navbar.Collapse id="navbarResponsive">
          <Nav className="me-auto">
            <Nav.Link href="#home">Inicio</Nav.Link>
            <Nav.Link href="#about">Acerca</Nav.Link>
            <Nav.Link href="#contact">Contacto</Nav.Link>
          </Nav>
          <Nav>
            <Nav.Link href="#login">Iniciar Sesión</Nav.Link>
          </Nav>
        </Navbar.Collapse>
      </Container>
    </Navbar>
  );
}
