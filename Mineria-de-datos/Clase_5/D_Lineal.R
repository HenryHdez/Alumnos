#cree un modelo con los datos de temperatura de atm 
#Recuerde importar la libreria library (modelr) 
#lm es un comando para estimar modelos lineales a partir de regresiones. 
#En este caso lm toma como predictor la temp_superficie y se predice el año 
atm=datos :: atmosfera 
mod <- lm(atm$temp_superficie ~ atm$anio, data = atm) 
#Una nueva variable almacena la diferencia entre los datos estimados 
#y los de entrenamiento estimados con el comando add_residuals 
atm2 <- atm %>%add_residuals (mod) 
#La diferencia o residuo se presenta en un gráfico de dispersión 
ggplot (data = atm2) +
  geom_point (mapping = aes (x = temp_superficie, y = resid)) 
#La cual tambien se podria apreciar en un diagrama de cajas 
ggplot (data = atm2) +
  geom_boxplot (mapping = aes (x = temp_superficie, y = resid))