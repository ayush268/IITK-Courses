#!/bin/python3

import re  # A guy needs Regular expressions
import sys

# Just declaring, actually has no use
number = '0'
base = '2'

# Have to use this stupid dictionary because we can't use int() function.
num_dict = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15, 'G': 16, 'H': 17, 'I': 18, 'J': 19, 'K': 20, 'L': 21, 'M': 22, 'N': 23, 'O': 24, 'P': 25, 'Q': 26, 'R': 27, 'S': 28, 'T': 29, 'U': 30, 'V': 31, 'W': 32, 'X': 33, 'Y': 34, 'Z': 35}

rev_num_dict = {num_dict[i]:i for i in num_dict}

#while True:

# Taking inputs and quitting
if(len(sys.argv) != 3):
    print ("Usage: ./q1.py NUMBER BASE")
    #break
    sys.exit()
number = sys.argv[1]
base = sys.argv[2]
neg_flag = 0;
point_flag = 0;

# If you enter empty input you are done.
#if (number == '' or base == ''):
#    sys.exit()
    #break

# Allowing amsall alphabets
number = number.strip()
base = base.strip()

if (len(re.findall("[0-9a-zA-Z]", number)) == 0):
    print ("Invalid Input.")
    sys.exit()

number_1 = number.upper()

# Checking if you entered a negative
if (re.findall("^-",number_1)):
    neg_flag = 1;
    number_1 = number_1[1:len(number_1)]

# Checking for decimal point
div_list = re.split("\.",number_1)
if (len(div_list) > 2):
    print ("Invalid Input.")
    #continue
    sys.exit()
elif (len(div_list) == 2):
    point_flag = 1
    number_1 = div_list[0]
    number_2 = div_list[1]

# Removing initial zeroes from ahead.
pattern = re.compile("^0+")
if(pattern.findall(number_1)):
    m = pattern.match(number_1)
    number_1 = number_1[m.end():len(number_1)]
if(pattern.findall(base)):
    m = pattern.match(base)
    base = base[m.end():len(base)]

# Removing trailing zeroes from behind.
if(point_flag):
    number_2 = number_2[::-1]
    if(pattern.findall(number_2)):
        m = pattern.match(number_2)
        number_2 = number_2[m.end():len(number_2)]
    number_2 = number_2[::-1]

# Checking validity of base
if(len(base)<1 or len(base)>2):
    print ("Invalid Input.")
    #continue
    sys.exit()
else:
    if(len(base)==1 and base>='0' and base<='9'):
        base = num_dict[base]
        if(base < 2):
            print("Invalid Input.")
            #continue
            sys.exit()
    elif(len(base)==2 and base[0]>='0' and base[1]>='0' and base[0]<='9' and base[1]<='9'):
        base = 10*num_dict[base[0]] + num_dict[base[1]]
        if(base > 36):
            print("Invalid Input.")
            #continue
            sys.exit()
    else:
        print("Invalid Input.")
        #continue
        sys.exit()

# If number was just zeroes then upper code will give empty string
if(number_1 == '' and number_2 == ''):
    print ("0")
    #continue
    sys.exit()

# Finding out the range of characters for current base
base_dict = {rev_num_dict[i]:i for i in range(0,base)}

# Converting number now
dec_number = 0
valid_no = 1

# If number has decimal point
# Converting decimal part first
if(point_flag):
    factor = 1 / base
    for i in number_2:
        if i in base_dict.keys():
            dec_number = factor*base_dict[i] + dec_number
            factor = factor / base
        else:
            valid_no = 0
            break

factor = 1
if(valid_no):
    for i in number_1[::-1]:
        if i in base_dict.keys():
            dec_number = factor*base_dict[i] + dec_number
            factor = factor*base
        else:
            valid_no = 0
            break

if(neg_flag):
    dec_number = -1*dec_number

if(valid_no):
    if(dec_number<-999999999 or dec_number>999999999):
        print("Result Out Of Bounds")
        #continue
        sys.exit()
    print (dec_number)
else:
    print ("Invalid Input.")
