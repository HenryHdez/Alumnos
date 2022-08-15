library(shiny)
ui <- fluidPage(
    titlePanel("Ejemplo 2"),
    sidebarLayout(
        #Aquí van los elementos que componen la interfaz
        sidebarPanel(
            #Texto de ayuda
            helpText("Esta es una aplicación de prueba"),
            #Campo de selección
            selectInput("Grupo_1", #ID
                        label = "Escoja una variable",
                        choices = c("Opcion 1", "Opcion 2", "Opcion 3"),
                        selected = "Opcion 2"),
            #Slider (ID, Etiqueta, Rango)
            sliderInput("Nombre_1",
                        "Rango de valores: ", min = 1, max = 30, value = 10)
        ),
        #Aquí van las funciones de salida
        mainPanel(
           textOutput("Nombre_funcion_1"),
           textOutput("Nombre_funcion_2")
        )
    )
)
#>>>>Funciones del usuario<<<<
server <- function(input, output) {
    output$Nombre_funcion_1 <- renderText({
        paste("Entrada seleccionada: ", input$Grupo_1)
    })
    output$Nombre_funcion_2 <- renderText({
        paste("Entrada seleccionada: ", input$Nombre_1)
    })
}
#>>>>Ejecutar el servidor
shinyApp(ui = ui, server = server)

