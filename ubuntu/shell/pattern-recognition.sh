#!/bin/bash

# Check if the correct number of arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filename> <pattern>"
    exit 1
fi

filename="$1"
pattern="$2"

# Check if the file exists
if [ -f "$filename" ]; then
    # Use grep to search for the pattern in the file
    if grep -q "$pattern" "$filename"; then
        echo "Pattern found in $filename."
        grep "$pattern" "$filename"
    else
        echo "Pattern not found in $filename."
    fi
else
    echo "File '$filename' does not exist."
fi