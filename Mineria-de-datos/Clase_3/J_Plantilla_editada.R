#Importe la librería
library(shiny)
#>>>>Definición de la forma de la ventana y contenido<<<<
#En este caso la variable ui almacena el objeto "ventana"
ui <- fluidPage(
    # Titulo de la aplicación
    titlePanel("Old Faithful Geyser Data"),
    # Definición del Slider
    sidebarLayout(
        sidebarPanel(
            sliderInput("bins",
                        "Number of bins:",
                        min = 1,
                        max = 50,
                        value = 30)
        ),
    # Definición del histograma
        mainPanel(
           plotOutput("distPlot")
        )
    )
)

# Definición del servidor o parte lógica de la aplicación
server <- function(input, output) {
    output$distPlot <- renderPlot({
        # Generar la distribución
        x    <- faithful[, 2]
        bins <- seq(min(x), max(x), length.out = input$bins + 1)
        # Presentación del histograma
        hist(x, breaks = bins, col = "darkgray", border = "white",
             xlab = "Waiting time to next eruption (in mins)",
             main = "Histogram of waiting times")
    })
}

# Ejecución de la aplicación
shinyApp(ui = ui, server = server)

