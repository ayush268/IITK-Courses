#!/bin/bash
calc_age_months(){
   day_today=`date +%d | bc`     
   mon_today=`date +%m | bc`     
   yr_today=`date +%Y | bc`
   
   day=`echo $1 | cut -d "-" -f1 | bc`
   month=`echo $1 | cut -d "-" -f2 | bc`     
   year=`echo $1 | cut -d "-" -f3 | bc`
   diff_day=$(($day_today - $day))
   diff_mon=$(($mon_today - $month))
   diff_yr=$(($yr_today - $year))
   if [ $diff_day -lt 0 ]
   then 
          diff_mon=$(($diff_mon - 1))     
   fi
   diff_mon=`echo "$diff_mon + 12 * $diff_yr" | bc`
   echo $diff_mon
}

if [ $# -ne 1 ];
then
   echo "usage: $0 <filename>" 
   exit -1
fi

filename=$1
if [ ! -f $filename ]
then
   echo "Invalid file" 
   echo "usage: $0 <filename>" 
   exit -1
fi

echo -n > report.txt
echo -n > result.csv

cat $filename | while read name dob;
do
    op=`./expressions-strict.sh $name $dob`
    if [ $? -eq 0 ]
    then
       echo -n "$op." >> report.txt
       age_months=`calc_age_months $dob`
       echo " Age in months = $age_months." >> report.txt
       echo "$name,$dob,$age_months" >> result.csv
    fi
done
