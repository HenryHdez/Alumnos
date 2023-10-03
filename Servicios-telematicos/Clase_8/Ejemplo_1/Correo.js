var nodemailer = require('nodemailer');
//Generar agente de transporte
var MTA = nodemailer.createTransport({
  service: 'gmail',
  auth: {
    user: 'usuario@udistrital.edu.co',
    pass: '*****'
  }});
//Configurar el correo electrónico
var Opciones = {
  from: 'usuario@udistrital.edu.co',
  to: 'destino@udistrital.edu.co',
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

