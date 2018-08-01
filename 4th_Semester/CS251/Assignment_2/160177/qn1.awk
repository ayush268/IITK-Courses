#!/usr/bin/awk -f
BEGIN {
  comments=0;strings=0;flagc=0;flags=0; #Basic Declarations
}

# Main
{
  x=1;
  gsub(/\\\"/, "");  #Removing escaped strings
  if (flagc == 1) {   #Comment block going on
    comments++;
  }
  while (x <= NF) {
    if ((flagc == 0) && (flags == 0)) {
      if (($x ~ /\/\//) && (match($x, /\/\//) == match($x, /\/\/|\/\*|\"/))) {         #// Comment
        comments++;
        x++;
        break;
      }
      if (($x ~ /\/\*/) && (match($x, /\/\*/) == match($x, /\/\/|\/\*|\"/))) {        #/* Comment
        comments++;
        flagc = 1;
        $x = substr($x, match($x, /\/\*/)+2);
      }
      else if (($x ~ /\"/) && (match($x, /\"/) == match($x, /\/\/|\/\*|\"/))) {        # " String
        strings++;
        flags = 1;
        $x = substr($x, match($x, /\"/)+1);
      }
    }
    if (($x ~ /\*\//) && (flagc == 1)) {                          # */ Closing comment
      flagc = 0;
      $x = substr($x, match($x, /\*\//)+2);
      continue;
    }
    if ((flags == 1) && ($x ~ /\"/)) {
      flags = 0;
      $x = substr($x, match($x, /\"/)+1);                        # " Closing String
      continue;
    }
    x++;
  }
  flags = 0;
}

END {
  OFS=":"
  print strings, comments;
}
