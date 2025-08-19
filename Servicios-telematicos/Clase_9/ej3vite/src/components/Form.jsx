import React, { useState } from 'react';
import { Form, Button, Container, Row, Col } from 'react-bootstrap';

export default function MyForm() {
  const [formData, setFormData] = useState({
    name: '',
    email: '',
    message: '',
  });

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData((prevData) => ({
      ...prevData,
      [name]: value,
    }));
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    alert(`Datos enviados:\nNombre: ${formData.name}\nEmail: ${formData.email}\nMensaje: ${formData.message}`);
  };

  return (
    <Container className="my-4">
      <h2>Contáctanos</h2>
      <Form onSubmit={handleSubmit}>
        <Form.Group as={Row} className="mb-3" controlId="formName">
          <Form.Label column sm={2}>Nombre</Form.Label>
          <Col sm={10}>
            <Form.Control
              type="text"
              name="name"
              placeholder="Ingresa tu nombre"
              value={formData.name}
              onChange={handleChange}
            />
          </Col>
        </Form.Group>
        <Form.Group as={Row} className="mb-3" controlId="formEmail">
          <Form.Label column sm={2}>Correo</Form.Label>
          <Col sm={10}>
            <Form.Control
              type="email"
              name="email"
              placeholder="Ingresa tu correo"
              value={formData.email}
              onChange={handleChange}
            />
          </Col>
        </Form.Group>
        <Form.Group as={Row} className="mb-3" controlId="formMessage">
          <Form.Label column sm={2}>Mensaje</Form.Label>
          <Col sm={10}>
            <Form.Control
              as="textarea"
              name="message"
              placeholder="Escribe tu mensaje"
              rows={4}
              value={formData.message}
              onChange={handleChange}
            />
          </Col>
        </Form.Group>
        <Button variant="primary" type="submit">Enviar</Button>
      </Form>
    </Container>
  );
}
