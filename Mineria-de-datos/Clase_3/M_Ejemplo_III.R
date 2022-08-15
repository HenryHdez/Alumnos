library(shiny)
library(datos)
library(tidyverse)
#>>>>Aplicación de usuario<<<<
ui <- fluidPage(
    titlePanel("Ejemplo 3"),
    sidebarLayout(
        sidebarPanel(helpText("Gráfica aleatoria")),
        mainPanel(plotOutput("Nombre_funcion_1"))
    )
)
#>>>>Funciones del usuario<<<<
server <- function(input, output) {
    output$Nombre_funcion_1 <- renderPlot({
        autos <- datos::millas
        ggplot(data <- autos) +
                    geom_point(mapping = aes(x = cilindrada, y = autopista))
    })
}
#>>>>Ejecutar el servidor
shinyApp(ui = ui, server = server)

