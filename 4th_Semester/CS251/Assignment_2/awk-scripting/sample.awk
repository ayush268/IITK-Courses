#!/usr/bin/awk
BEGIN{
 FS="="         
}
{
#   print "LN "NR " --> " $0;
   print "LN "NR sepstr $0;
   for(i=1;i<=NF;i++){
#        print i " --> " $i
        print i sepstr $i
   }
}
END{
}
