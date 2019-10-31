#!/bin/bash

TRASH="./trash"
if [ ! -d "$TRASH" ]
then
    `mkdir "$TRASH"`
fi

for (( i = 1; i <= $#; i+=2)); do
    # echo "${!i}"
    case "${!i}" in

        "-d")
            j=$((i+1))
            `mv "${!j}" ./trash/"${!j}"`
        ;;
        
        "-c")
            `rm -r -f ./trash/*`
        ;;
        
        "-h")
            echo "$0 script help"
            echo "Usage:"
            echo "-d arg    moves file to /trash folder"
            echo "-c        empties /trash folder"
            echo "-h        help command"
        ;;
        
        *)
            echo "Use -h to see available commands"
        ;;
    esac
done