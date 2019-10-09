#!/usr/bin/gawk
BEGIN{
           current_HOUR=-1
           this_HOUR=0
           count=0
           
}
function extract_hour(timeSTR)
{
       split($3, hr, ":");
       return hr[1]          
  
}

{
        
        if ($0 ~ /Invalid response packet/){
             this_HOUR=extract_hour($3);
             if(current_HOUR == -1){
                   current_HOUR=this_HOUR;
             }else if(this_HOUR > current_HOUR || (current_HOUR == 23 && this_HOUR == 0)){
                   print "["current_HOUR"-"this_HOUR"]  "count
                   count=0;  
                   current_HOUR=this_HOUR
             } else{
                   count++;
             }
        }  
}
END{
         if(current_HOUR == 23)
             this_HOUR=0
         else
             this_HOUR=current_HOUR+1
         if(count)
             print "["current_HOUR"-"this_HOUR"]  "count
      
}
