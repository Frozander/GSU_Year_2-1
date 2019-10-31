#!/bin/bash

FOLDER="./bck"
if [ ! -d "$FOLDER" ]
then
    `mkdir "$FOLDER"`
fi

if [[ -z "$1" || "$1" == "-h" ]]
then
    echo "Backs up given folder/file in $FOLDER in given intervals"
    echo "Usage: $0 x"
    echo "d: directory or file to be backed up"
    echo "x: time interval between each backup"
    exit 1
fi

if [[ -f "$1" || -d "$1" ]]
then
    if let $2
    then
        echo "backing up $1 for every $2 seconds"
        while :
        do
            `cp -r -f "$1" "$FOLDER"`
            `sleep "$2"`
        done
    else
        echo "$2 is not a number"
        exit 2
    fi
else
    echo "$1 does not exist"
    exit 3
fi
    