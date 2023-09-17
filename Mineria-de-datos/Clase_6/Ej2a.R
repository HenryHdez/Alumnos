library(plumber)
library(ggplot2)

#* @serializer png
#* @get /histograma
function() {
  data <- rnorm(1000)
  
  plot <- ggplot(data.frame(x=data), aes(x=x)) +
          geom_histogram(binwidth=0.2, fill="blue", color="black", alpha=0.7)
  
  print(plot)
}

