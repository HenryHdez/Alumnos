function Audio_Disp(){
    //Estructura para habilitar el micrófono
    //True=El usuario dio permisos
    let audioIN = { audio: true };
    navigator.mediaDevices.getUserMedia(audioIN).then(function (mediaStreamObj) {
    //Then retorna una promesa, sí
    //El dispositivo esta conectado
    //Seleccione la vía por la cual obtendra el audio
        let audio = document.querySelector('audio');
        //Cree un objeto para almacenar lo que llega del micrófono
        if ("srcObject" in audio) {audio.srcObject = mediaStreamObj;}
        else{audio.src = window.URL.createObjectURL(mediaStreamObj);}
        //Reproducir audio precargado 
        audio.onloadedmetadata = function (ev){audio.play();};
        //Iniciar grabación
        let start = document.getElementById('btnStart');
        //Parar grabación
        let stop = document.getElementById('btnStop');
        //Elemento para reproducir el audio
        let playAudio = document.getElementById('adioPlay');
        //API de reproducción
        let mediaRecorder = new MediaRecorder(mediaStreamObj);
        //Oyente para el botón start
        start.addEventListener('click', function (ev) {
          mediaRecorder.start();
        })
        //Oyente para el botón stop
        stop.addEventListener('click', function (ev) {
          mediaRecorder.stop();
        });
        // Si hay audio disponible reproduzca
        mediaRecorder.ondataavailable = function (ev) {
          dataArray.push(ev.data);
        }
        // Matriz de fragmentos para almacenar audio
        let dataArray = [];
        // Unifique los datos de audio
        // Despues de para la reproducción 
        mediaRecorder.onstop = function (ev) {
          // Guardar mp3
          let audioData = new Blob(dataArray, 
                    { 'type': 'audio/mp3;' });
          // Vaciar arreglo
          dataArray = [];
          // Crear URL para reproducir el audio
          let audioSrc = window.URL.createObjectURL(audioData);
          playAudio.src = audioSrc;
        }
      })
      // Si hay algún error entonces haga esto
      .catch(function (err) {
        console.log(err.name, err.message);
      });
    }

    