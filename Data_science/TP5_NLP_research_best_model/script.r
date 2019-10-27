;; This buffer is for text that is not saved, and for Lisp evaluation.
;; To create a file, visit it with C-x C-f and enter text in its buffer.

prediction_finale <- function(x_ultime, 
                              y_ultime,
                              file_path = "checchio_model_keras.hdf5"){
  #Remplacer "my_login" par votre propre login ensimag. 
  
  require(magrittr) 
  
  #tests 
  if (nrow(x_ultime) != 5000 | ncol(x_ultime) != 2000) 
    stop("Dimensions de x incorrectes.")

  if (nrow(y_ultime) != 5000 | ncol(y_ultime) != 2) 
    stop("Dimensions de y incorrectes.")
    
  #if keras
    require(keras) 

    model <- load_model_hdf5(filepath = "checchio_model_keras.hdf5")
    model %>% evaluate(x_ultime, y_ultime)
}