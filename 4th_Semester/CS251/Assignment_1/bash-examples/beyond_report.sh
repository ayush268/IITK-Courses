#!/bin/bash
indent=0
#used for indentation
pindent(){
            i=0
            while [ $i -lt $indent ];
            do
                  echo -n "   "
                  i=$(($i+1))
            done 
}
recurse(){
     cd "$1"
     for line in *
     do
           if [ -d "$line" ];
           then
                indent=$(($indent + 1))
                recurse "$line"
                 
           fi
     done
     for line in *
     do
           if [ -f "$line" ]
           then
                flines=`wc -l "$line" | cut -d " " -f1`
                flines=$(($flines - $avg_age))
                if [ $flines -ge 0 ]
                then
                   indent=$(($indent + 1))
                   pindent
                   echo "$line"
                   indent=$(($indent - 1))
                fi
           fi
     done
     cd ..   
     indent=$(($indent - 1))
}


if [ $# -ne 2 ];
then
   echo "usage: $0 <csv-file> <dir-path>" 
   exit -1
fi

filename=$1
if [ ! -f $filename ] || [ ! -d $2 ]
then
   echo "usage: $0 <filename>" 
   exit -1
fi

months=`cut -d "," -f3 result.csv`
count=0
sum=0
for i in $months;
do
    sum=$(($sum + $i))
    count=$(($count + 1))
done
avg_age=`echo "$sum/$count" | bc`

#echo "sum=$sum count=$count avg=$avg_age"
recurse $2
