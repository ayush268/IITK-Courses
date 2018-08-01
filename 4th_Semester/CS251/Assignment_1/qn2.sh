#!/bin/bash

# This function calculates number of integers and returns result as exit code
function cal_int {
  a=$(cat "$1" | grep -oP "\d*\.*\d+" | grep -Pv "\d\." | grep -coP "\d+")
  return $a
}

# This function calculates number of sentences and returns result as exit code
function cal_sent {
  b=$(cat "$1" | sed "s/[0-9]\.[0-9]//g" | tr '\n' " " | tr '.' "\n" | tr '?' "\n" | tr '!' "\n" | grep -P "\S" | grep -v "^$" | wc -l)
  return $b
}

# This function takes path and depth as arguments and prints the result in a recursive pattern
function traverse {
  local num_int=0
  local num_sent=0

  if test -f "$1"; then
    cal_int "$1"
    num_int=$?
    cal_sent "$1"
    num_sent=$?
  fi
  
  # For a directory it makes a recursive call to itself with the subpaths and depth+1
  if test -d "$1"; then
   temp_int[$2]=0
   temp_sent[$2]=0
   cd "$1"
    # tr command is used here to handle files which have spaces in their names
    # I am using "@" assuming is not in filename, use other character if you have used this in filename
    for i in $(ls -a | tr ' ' '@'); do 
      if [[ "$i" == "." || "$i" == ".." ]]; then
        continue;
      fi
      traverse "$(echo $i | tr '@' ' ')" $(($2+1))    # tr is for filenames with spaces
    done
    num_int=${temp_int[$2]}
    num_sent=${temp_sent[$2]}
    cd ..
  fi

  # Keeping track of num_int and num_sent for directories by adding one's of contents
  if [[ $2 -ne 0 ]]; then
    temp_int[$(($2-1))]=$((${temp_int[$(($2-1))]}+$num_int))
    temp_sent[$(($2-1))]=$((${temp_sent[$(($2-1))]}+$num_sent))
  fi

  # Printing relevant amount of tab-spaces
  local k=$2
  while [ $k -gt 0 ]; do
    echo -e -n "\t"
    k=$(($k-1))
  done

  #Printing the corresponding result
  if test -d "$1"; then
    echo "(D) $(basename "$1")-$num_sent-$num_int"
  fi
  if test -f "$1"; then
    echo "(F) $(basename "$1")-$num_sent-$num_int"
  fi
}

# Checking if path provided is valid or not.
if test ! -d "$1" -a ! -f "$1"; then
  echo "Please input a valid directory or file path!"
  exit 1
fi

# Setting depth to 0 initially and passing path to traverse
depth=0
traverse "$1" $depth
