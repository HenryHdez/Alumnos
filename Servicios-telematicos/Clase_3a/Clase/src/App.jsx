import { useState } from 'react'
import './App.css'
import Button from 'react-bootstrap/Button';
import Form from 'react-bootstrap/Form';

function App() {

  return (
    <>
    <div>
      {/* Comentario en Vite */}
      <Button variant="success">Success</Button>
          <Form>
      <Form.Group className="mb-3" controlId="exampleForm.ControlInput1">
        <Form.Label>Email address</Form.Label>
        <Form.Control type="email" placeholder="name@example.com" />
      </Form.Group>
      <Form.Group className="mb-3" controlId="exampleForm.ControlTextarea1">
        <Form.Label>Example textarea</Form.Label>
        <Form.Control as="textarea" rows={3} />
      </Form.Group>
    </Form>
    </div>
    </>
  )
}

export default App
