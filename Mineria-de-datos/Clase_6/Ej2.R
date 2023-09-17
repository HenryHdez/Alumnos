#* @get /Mensaje de bienvenida
Bienvenida <- function() {
  list(message = "¡Bienvenido!")
}

#* @get /suma
suma <- function(a=0, b=0){
  list(result = as.numeric(a) + as.numeric(b))
}

#* @get /Fecha actual
Fechactual <- function(){
  list(datetime = Sys.time())
}

