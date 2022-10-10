var nodemailer = require('nodemailer');
//Generar agente de transporte
var MTA = nodemailer.createTransport({
  service: 'gmail',
  auth: {
    user: 'hahernandezm@udistrital.edu.co',
    pass: 'Ti88031255206'
  }});
//Configurar el correo electrónico
var Opciones = {
  from: 'hahernandezm@udistrital.edu.co',
  to: 'hahernandezm@udistrital.edu.co',
  subject: 'Correo enviado usando JS',
  text: 'Facil!',
  attachments: [
    { filename: 'Escudo.png',
      path: __dirname + '/Escudo.png',
      cid: 'uniq-mailtrap.png' 
    }]
};

//Envio del correo usando la librería
MTA.sendMail(Opciones, function(error, info){
  if (error) {console.log(error);} 
  else {console.log('Respuesta del app: ' + info.response);}});

