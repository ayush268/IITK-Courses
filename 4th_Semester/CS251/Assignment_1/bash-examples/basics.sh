#!/bin/bash

#  read a
#  read b
#  echo $a $b
 
#  read a b < infile
#  echo "a=$a b=$b"
#  echo "a=$a b=$b" > outfile
#  echo "a=$a b=$b" >> outfile
 
#  a=ls
#  echo $a
#  a="ls"
#  echo $a
#  a='ls'
#  echo $a
#  a=$(ls)
#  echo $a
#  a=`ls`
#  echo $a
#
# ls ~/workspace/linux-4.12.3/Documentation/*.txt | grep hw  
# ls ~/workspace/linux-4.12.3/Documentation/*.txt | grep hw | wc -l 
# numfiles_hw=`ls ~/workspace/linux-4.12.3/Documentation/*.txt | grep hw | wc -l`
# numfiles_cpu=`ls ~/workspace/linux-4.12.3/Documentation/*.txt | grep cpu | wc -l`
# total=$(($numfiles_hw+$numfiles_cpu))
# echo "numfiles_hw=$numfiles_hw numfiles_cpu=$numfiles_cpu total=$total"
 
 ls ~/workspace/linux-4.12.3/Documentation/*.txt | grep -E 'hw|cpu' | wc -l  
