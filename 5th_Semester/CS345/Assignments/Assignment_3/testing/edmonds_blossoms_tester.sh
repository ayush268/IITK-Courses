#!/usr/bin/zsh
temp_file="./ebtest.txt"

myeb_out="/tmp/myeb.out"
eb_out="/tmp/eb.out"
g++ "./matching.cpp" -o $myeb_out
g++ "./edmonds_blossoms_codeforces.cpp" -o $eb_out

for it in $(seq 1 1000)
do
    n=$((1 + RANDOM % 100))
    m=$((1 + RANDOM % 4000))
    echo "$n $m" > $temp_file

    for edge in $(seq 1 $m)
    do
        i=$((1 + RANDOM % n))
        j=$((1 + RANDOM % n))
        echo "$i $j" >> $temp_file
    done

    myeb_ans=$(cat $temp_file | $myeb_out | head -1)
    eb_ans=$(cat $temp_file | $eb_out | head -1)
    if (( $myeb_ans != $eb_ans ))
    then
        echo "Mismatch found                "
        cp $temp_file "./mismatch.txt"
        exit -1
    else
        echo -ne "\rSuccess: Iteration $it"
    fi
done

echo ""
rm $temp_file $myeb_out $eb_out
