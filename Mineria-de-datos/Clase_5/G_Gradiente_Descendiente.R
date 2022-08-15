#Implemente una función que resulva la ecuación de
#minimos cuadrados.
sum_residuos <- function(x, y, beta_0, beta_1) {
  return(sum((y - (beta_0 + beta_1 * x))^2))
}

#Implemente una función que calcule el gradiente.
calc_gradiente <- function(beta_0, beta_1, x, y) {
  # beta_0: intercepto
  # beta_1: pendiente
  # x: predictor (datos de entrada)
  # y: datos a predecir (datos de salida).
  # Calcule el componente uno del vector de gradiente
  grad_1 <- sum(y - beta_0 - beta_1 * x)
  # Calcule el componente dos del vector de gradiente
  grad_2 <- sum((y - beta_0 - beta_1 * x) * x)
  return(c(grad_1, grad_2))
}

# Implemente el algoritmo del gradiente descendiente.
optimizacion_grad <- function(beta_0, beta_1, x, y, t, max_iter, tolerancia) {
  # tabla para almacenar el valor de las estimaciones en cada iteración
  tabla <- matrix(NA, nrow = max_iter, ncol = 4)
  colnames(tabla) <- c("iteracion", "beta0", "beta1", "residuos")
  #Inicio del proceso iterativo
  for (i in 1:max_iter) { #max_iter es una condición de parada
    gradiente <- calc_gradiente(beta_0 = beta_0, beta_1 = beta_1, x = x, y = y)
    #Si el error cuadratico es menor que el valor esperado el algoritmo para
    if (sqrt(sum(gradiente^2)) < tolerancia) {
      break
    } else {
    #Guarda valores en la tabla
      tabla[i, 1] <- i
      tabla[i, 2] <- beta_0
      tabla[i, 3] <- beta_1
      tabla[i, 4] <- sum_residuos(x, y, beta_0, beta_1)
      beta_0 <- beta_0 + t * gradiente[1] #Actualice beta_0
      beta_1 <- beta_1 + t * gradiente[2] #Actualice beta_1
    }
  }
  print(paste("Mejor beta_0:", beta_0))
  print(paste("Mejor beta_1;", beta_1))
  print(paste("Número de iteraciones:", i))
  print(paste("Suma de residuos cuadrados:", tabla[i - 1, 4]))
  return(list(beta_0 = beta_0,
              beta_1 = beta_1,
              iteraciones = i,
              tabla = as.data.frame(na.omit(tabla))
  )
  )
}

#Ejecute la función asignando valores iniciales al algoritmo
#run if genera numeros racionales aleatoriamente
x <- seq(1, 10)
y <- runif(10, min = 1, max = 2)
resultados <- optimizacion_grad(beta_0 = 10, beta_1 = 10,
                                x, y, t = 0.001, max_iter = 10000,
                                tolerancia = 1e-6)

