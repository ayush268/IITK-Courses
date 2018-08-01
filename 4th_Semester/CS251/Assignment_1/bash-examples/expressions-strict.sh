#!/bin/bash 
if [ $# -ne 2 ];
then
    echo "Usage: $0 <name> <DOB in dd-mm-yyyy>"
    exit -1
fi
regex='^[0-9]{2}-[0-9]{2}-[0-9]{4}$'
#regex='^[0-3][0-9]-[0-1][0-2]-[[19][0-9]{2}|[20][0-9]{2}$'

if ! [[ $2 =~ $regex ]];
then
    echo "This is not a valid date even with a basic check"
    exit -1
fi
name=$1
words=`echo $name | wc -w`
day=`echo $2 | cut -d "-" -f1`
month=`echo $2 | cut -d "-" -f2`
year=`echo $2 | cut -d "-" -f3`

#Year range is between 1900 and 2018
if  [ $year -lt 1900 ] || [ $year -gt 2018 ] 
then
      echo "Invalid year!"
      exit -1
fi 

#Check for month
if  [ $month -eq 0 ] || [ $month -gt 12 ] 
then
      echo "Invalid month!"
      exit -1
fi 

#Check for date
if [ $day -eq 0 ]
then
      echo "Invalid date!"
      exit -1
else
#     set -x
     case "$month" in
     04|06|09|11)
                 if [ $day -gt 30 ]
                 then
                    echo "30. Incompatible month and date!"
                    exit -1
                 fi
                 ;;
     02)
                 year_div_4=$(($year % 4))
                 year_div_400=$(($year % 400))
                 if [ $year_div_4 -eq 0 ] && [ $year_div_400 -ne 0 ]
                 then
                      maxdays=29
                 else 
                      maxdays=28
                 fi 
                 if [ $day -gt $maxdays ];
                 then
                    echo "29. Incompatible month and date!"
                    exit -1
                 fi
                 ;;
    *)
                 if [ $day -gt 31 ]
                 then
                    echo "31. Incompatible month and date!"
                    exit -1
                 fi
                 ;;
     esac
 #    set +x
fi

echo "Mr. $name is a person with a name of $words words was born on $2"
