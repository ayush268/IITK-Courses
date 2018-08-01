#!/usr/bin/gawk
BEGIN{
           
}

{
        
   if ($0 ~ /Invalid response packet/ && $NF ~ /[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.$/){
              split($NF, b, /\.$/)     
              arr[b[1]]++
        }
        
        if ($0 ~ /Invalid response packet/ && $0 ~ /message repeated [0-9]+ times/ && $NF ~ /[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.\]$/){
              split($NF, b, /\.\]$/)     
              arr[b[1]]=arr[b[1]] + $8
        }
          
}
END{
      
       for(i in arr){
               print i "   " arr[i]
       }
}
