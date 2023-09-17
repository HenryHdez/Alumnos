#* @apiTitle COVID Colombia API
library(DBI)
library(RMySQL)

#* @get /data
function() {
  conn <- dbConnect(MySQL(), user='root', password='mi_contrasena', 
                    dbname='covid_colombia', host='localhost', port=3307)
  data <- dbReadTable(conn, "covid_data_colombia")
  dbDisconnect(conn)
  return(data)
}

