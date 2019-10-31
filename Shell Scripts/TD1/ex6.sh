#!/bin/bash

if [[ -z $1 ]]; then
    echo "Usage: $0 num"
    exit 1
fi

if ! let $1; then
    echo "$1 is not a number"
fi

tries=0
limit=$2
rand=`expr "$RANDOM" % $1`
guess=-1

echo $rand

while [ $guess != $rand -a $tries -lt $limit ]
do
    echo "Enter a number:"
    read guess
    if [ "$guess" -lt "$rand" ]
    then
        echo "Go higher!"
    fi
    if [ "$guess" -gt "$rand" ]
    then
        echo "Go lower!"
    fi
    tries=`expr $tries + 1`
done

if [[ "$tries" -eq "$limit" ]]
then
    echo "Too many tries"
    exit 2
fi
echo "Congratulation! You have found the correct number $rand, in $tries tries"

