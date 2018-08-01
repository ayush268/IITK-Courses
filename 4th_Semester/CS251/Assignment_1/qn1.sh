#!/bin/bash

# This function is for giving units digit string
function units {
  if [[ $1 -eq 1 ]]; then
    digit="one"
  fi
  if [[ $1 -eq 2 ]]; then
    digit="two"
  fi
  if [[ $1 -eq 3 ]]; then
    digit="three"
  fi
  if [[ $1 -eq 4 ]]; then
    digit="four"
  fi
  if [[ $1 -eq 5 ]]; then
    digit="five"
  fi
  if [[ $1 -eq 6 ]]; then
    digit="six"
  fi
  if [[ $1 -eq 7 ]]; then
    digit="seven"
  fi
  if [[ $1 -eq 8 ]]; then
    digit="eight"
  fi
  if [[ $1 -eq 9 ]]; then
    digit="nine"
  fi
}

# This is for giving tens digit string
function tens {
  if [[ $1 -eq 2 ]]; then
    digit="twenty"
  fi
  if [[ $1 -eq 3 ]]; then
    digit="thirty"
  fi
  if [[ $1 -eq 4 ]]; then
    digit="forty"
  fi
  if [[ $1 -eq 5 ]]; then
    digit="fifty"
  fi
  if [[ $1 -eq 6 ]]; then
    digit="sixty"
  fi
  if [[ $1 -eq 7 ]]; then
    digit="seventy"
  fi
  if [[ $1 -eq 8 ]]; then
    digit="eighty"
  fi
  if [[ $1 -eq 9 ]]; then
    digit="ninety"
  fi
}

# This is for giving the string corresponding to numbers between 10-19.
function one_line {
  if [[ $1 -eq 0 ]]; then
    digit="ten"
  fi
  if [[ $1 -eq 1 ]]; then
    digit="eleven"
  fi
  if [[ $1 -eq 2 ]]; then
    digit="twelve"
  fi
  if [[ $1 -eq 3 ]]; then
    digit="thirteen"
  fi
  if [[ $1 -eq 4 ]]; then
    digit="fourteen"
  fi
  if [[ $1 -eq 5 ]]; then
    digit="fifteen"
  fi
  if [[ $1 -eq 6 ]]; then
    digit="sixteen"
  fi
  if [[ $1 -eq 7 ]]; then
    digit="seventeen"
  fi
  if [[ $1 -eq 8 ]]; then
    digit="eighteen"
  fi
  if [[ $1 -eq 9 ]]; then
    digit="nineteen"
  fi
}

mynum=$1

# Checks if string is invalid (contains anything other than numbers).
echo $mynum | grep -q -E "[^0-9]" ;
if [[ $? -eq 0 ]]; then
  echo "invalid input";
  exit 1;
fi

# Checking if you placed an empty input.
echo $mynum | grep -q -E "[0-9]" ;
if [[ $? -eq 1 ]]; then
  echo "invalid input";
  exit 1;
fi

# Removing initial zeroes.
mynum=$(echo $mynum | sed 's/^0*//')

# Checking if initial string was just zero.
echo $mynum | grep -q -E "[0-9]" ;
if [[ $? -eq 1 ]]; then
  echo "zero";
  exit 0;
fi

# len is number of digits and i is number.
len=0
i=$mynum

# Separating digits of the number and storing them into an array
while [ $i -ne 0 ]; do
  if [[ $len -eq 11 ]]; then
    echo "invalid input"             # Number is greater than 9999,99,99,999
    exit 1;
  fi
  numarr[$len]=$(($i%10))
  i=$(($i/10))
  len=$(($len+1))
done

# Declaring index
index=0
len=$(($len-1))

# Traversing through the number from the highest placed digit and storing corresponding strings in the words array.
while [ $len -ge 0 ]; do
  if [[ $len -eq 10 || $len -eq 9 || $len -eq 7 || $len -eq 5 || $len -eq 3 || $len -eq 2 || $len -eq 0 ]]; then
    if [[ ${numarr[$len]} -ne 0 ]]; then
      units ${numarr[$len]}
      words[$index]=$digit
      index=$(($index+1))
    fi
  else
    if [[ ${numarr[$len]} -ne 0 ]]; then
      if [[ ${numarr[$len]} -ne 1 ]]; then
        tens ${numarr[$len]}
        words[$index]=$digit
        index=$(($index+1))
      else
        len=$(($len-1))
        one_line ${numarr[$len]}
        words[$index]=$digit
        index=$(($index+1))
      fi
    fi
  fi
  if [[ $len -eq 10 ]]; then
    words[$index]="thousand"
    index=$(($index+1))
  fi
  if [[ $len -eq 9 || $len -eq 2 ]]; then
    if [[ ${numarr[$len]} -ne 0 ]]; then
      words[$index]="hundred"
      index=$(($index+1))
    fi
  fi
  if [[ $len -eq 3 ]]; then
    if [[ ${numarr[$len]} -ne 0 || ${numarr[$(($len+1))]} -ne 0 ]]; then
      words[$index]="thousand"
      index=$(($index+1))
    fi
  fi
  if [[ $len -eq 7 ]]; then
      words[$index]="crore"
      index=$(($index+1))
  fi
  if [[ $len -eq 5 ]]; then
    if [[ ${numarr[$len]} -ne 0 || ${numarr[$(($len+1))]} -ne 0 ]]; then
      words[$index]="lakh"
      index=$(($index+1))
    fi
  fi
  len=$(($len-1))
done

# Printing the array in reverse order as storage was done in reverse order.
echo ${words[@]}
