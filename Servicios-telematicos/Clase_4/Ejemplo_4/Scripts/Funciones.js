function Iniciar(){
    alert("Pagina iniciada");
}

function Crear_Elementos(){
    const div = document.createElement("div");      // Creamos un <div></div>
    const span = document.createElement("span");    // Creamos un <span></span>
    const img = document.createElement("img");      // Creamos un <img>    
    div.innerHTML = "<strong>Texto HTML</strong>";
    span.textContent="Span Saludos";
    //img.src="Bodegon_1.jpg";
    document.body.appendChild(div);
    document.body.appendChild(span);
    //document.body.appendChild(img);
}

function Eliminar(){
    const div = document.querySelector("div");
    div.remove(); 
}

function Reemplazar(){
    /*SetAtributte permite asignar atributos a los elementos creados*/
    var sp1 = document.createElement("span");
    // darle un atributo id llamado 'newSpan'
    sp1.setAttribute("id", "newSpan");
    // crear algún contenido para el nuevo elemento
    var sp1_content = document.createTextNode("Nuevo elemento span para reemplazo.");
    // aplicar dicho contenido al nuevo elemento
    sp1.appendChild(sp1_content);   
    document.body.appendChild(sp1);
    // construir una referencia al nodo existente que va a ser reemplazado
    var sp2 = document.getElementById("childSpan");
    var parentDiv = sp2.parentNode;
    // reemplazar el nodo sp2 existente con el nuevo elemento span sp1
    parentDiv.replaceChild(sp1, sp2);
}

