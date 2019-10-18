#!/bin/bash
if let $1
then
    printf "%d is an integer\n" "$1"
else
    printf "%d is not an integer\n" "$1"
fi