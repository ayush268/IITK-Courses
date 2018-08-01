#user defined function

check_and_sum <- function(ydata, year)
{
     total <- 0.0
     for(i in 1 : length(ydata)){
           total <- total + ydata[i]
     }
     if(year <= 1950){
           total = total * 1.8
     }
     return (total)
}

expenses <- data.frame(USPersonalExpenditure)
expenses

cols <- colnames(expenses)

for(i in 1: length(cols)){
   val <- cols[i]
    
   ydata <- expenses[[val]]
 
   year <- gsub("X","",val)

   totalexp <- check_and_sum(ydata, year)

   print(totalexp)  
}

