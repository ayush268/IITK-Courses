#!/usr/bin/awk
{
      if($0 ~ /[[:space:]]*while[[:space:]]*\(/)
           print $0
}
