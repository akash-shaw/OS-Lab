#!/bin/bash

read -p "Enter the file name: " filename

if [ -d "$filename" ]; then
    echo "$filename is a directory."
elif [ -f "$filename" ]; then
    echo "$filename is a regular file."
else
    echo "$filename does not exist."
fi
