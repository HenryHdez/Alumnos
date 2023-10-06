const express = require('express');
const bodyParser = require('body-parser');
const nodemailer = require('nodemailer');
const path = require('path');
//Puerto y servidor express
const app = express();
const PORT = 5000;

// Middlewares:
//Aplicación que se ejecuta en el momento que el cliente
//hace una solicitud y la respuesta del servidor
//Expresa la solicitud x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: true }));
//Analiza el cuerpo de las solicitudes entrantes en formato JSON 
//y los convierte en un objeto JavaScript accedido mediante req.body.
app.use(bodyParser.json());
//Crear agente de transporte
const MTA = nodemailer.createTransport({
    service: 'gmail',
    auth: {
        user: 'heahernandezma@unal.edu.co',
        pass: 'xrye gcok mlnt kvyu'
    }
});
//Ver archivo html
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'views', 'index.html'));
});
//Enviar correo
app.post('/enviar-email', (req, res) => {
    const { para, asunto, mensaje } = req.body;
    const mailOptions = {
        from: 'heahernandezma@unal.edu.co',
        to: para,
        subject: asunto,
        text: mensaje
    };

    MTA.sendMail(mailOptions, (error, info) => {
        if (error) {
            console.log(error);
            res.status(500).send('Hubo un error al enviar el correo.');
        } else {
            res.status(200).send('Correo enviado exitosamente.');
        }
    });
});
//Oyente
app.listen(PORT, () => {
    console.log('Servidor en ejecución');
});
