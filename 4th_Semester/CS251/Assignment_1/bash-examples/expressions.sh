#!/bin/bash
if [ $# -ne 2 ];
then
    echo "Usage: $0 <name> <DOB in dd-mm-yyyy>"
    exit -1
fi
regex='^[0-9]{2}-[0-9]{2}-[0-9]{4}$'
if ! [[ $2 =~ $regex ]];
then
    echo "DUsage: $0 <name> <DOB in dd-mm-yyyy>"
    exit -1
fi
name=$1
words=`echo $name | wc -w`
echo "Mr. $name is a person with a name of $words words was born on $2"
