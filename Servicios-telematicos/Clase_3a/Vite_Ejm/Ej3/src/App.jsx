import { useState } from 'react';
import {
  Container,
  Card,
  Form,
  Button,
  Modal
} from 'react-bootstrap';

function App() {
  // Estado para guardar el texto escrito en la caja
  const [texto, setTexto] = useState('');

  // Estado para controlar si el modal está abierto o cerrado
  const [mostrarModal, setMostrarModal] = useState(false);

  // Oyente de la caja de texto
  const manejarCambio = (e) => {
    setTexto(e.target.value);
  };

  // Abre el modal
  const abrirModal = () => {
    setMostrarModal(true);
  };

  // Cierra el modal
  const cerrarModal = () => {
    setMostrarModal(false);
  };

  return (
    // Contenedor principal ocupando toda la altura de la pantalla
    <Container
      fluid
      className="min-vh-100 d-flex justify-content-center align-items-center bg-light"
    >
      {/* Tarjeta principal con sombra y bordes redondeados */}
      <Card
        className="shadow-lg border-0 rounded-4 p-4"
        style={{ width: '100%', maxWidth: '500px' }}
      >
        <Card.Body>
          {/* Título */}
          <h2 className="text-center mb-3">Formulario básico</h2>

          {/* Texto descriptivo */}
          <p className="text-muted text-center mb-4">
            Ejemplo de uso de react.
          </p>

          {/* Grupo del formulario */}
          <Form>
            <Form.Group className="mb-4">
              <Form.Label className="fw-semibold">
                Escribe un mensaje
              </Form.Label>

              {/* Caja de texto */}
              <Form.Control
                type="text"
                placeholder="Escribe algo aquí..."
                value={texto}
                onChange={manejarCambio}
                className="rounded-3 py-2"
              />
            </Form.Group>

            {/* Botón ancho completo */}
            <div className="d-grid">
              <Button
                variant="primary"
                size="lg"
                className="rounded-3"
                onClick={abrirModal}
              >
                Ver mensaje
              </Button>
            </div>
          </Form>
        </Card.Body>
      </Card>

      {/* Modal */}
      <Modal
        show={mostrarModal}
        onHide={cerrarModal}
        centered
      >
        <Modal.Header closeButton className="border-0 pb-0">
          <Modal.Title>Mensaje ingresado</Modal.Title>
        </Modal.Header>

        <Modal.Body className="pt-2">
          <div className="p-3 bg-light rounded-3 border">
            {texto ? texto : 'No se escribió ningún mensaje.'}
          </div>
        </Modal.Body>

        <Modal.Footer className="border-0">
          <Button variant="secondary" onClick={cerrarModal}>
            Cerrar
          </Button>
        </Modal.Footer>
      </Modal>
    </Container>
  );
}

export default App;