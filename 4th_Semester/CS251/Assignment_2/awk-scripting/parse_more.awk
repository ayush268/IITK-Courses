#!/usr/bin/gawk
BEGIN{
           
}

{
        
  if ($0 ~ /Invalid response packet/ && $NF ~ /[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}/){
              arr[$NF]++
        }  
}
END{
      
       for(i in arr){
               print i "   " arr[i]
       }
}
