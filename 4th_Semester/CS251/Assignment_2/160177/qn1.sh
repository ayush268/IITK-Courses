#!/bin/bash

function traverse {
  if test -f "$1"; then
    echo "$1" | grep -q -E "\.c$"
    if [[ $? -eq 0 ]]; then
      local result=$("$main"qn1.awk "$1")             # Calling awk script on C files.
      local temp=$(echo $result | cut -d ":" -f 1)
      strings=$(($strings+$temp))
      temp=$(echo $result | cut -d ":" -f 2)
      comments=$(($comments+$temp))
    fi
  fi
  # For a directory it makes a recursive call to itself with the subpaths
  if test -d "$1"; then
   cd "$1"
    for i in $(ls -a | tr ' ' '@'); do
      if [[ "$i" == "." || "$i" == ".." ]]; then
        continue;
      fi
      traverse "$(echo $i | tr '@' ' ')"
    done
    cd ..
  fi
}

for j in $(cat "$1"); do

  # Checking if path provided is valid or not.
  if test ! -d "$j" -a ! -f "$j"; then
    echo "Please input a valid directory or file path!"
    exit 1
  fi

  strings=0
  comments=0
  main="$(pwd)/"
  traverse "$j"
  echo -e "$j\n"
  echo "Number of STRINGS: $strings"
  echo -e "Number of COMMENTS: $comments\n"
done
