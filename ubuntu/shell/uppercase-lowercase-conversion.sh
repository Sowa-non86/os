#!/bin/bash

echo "Enter a string:"
read input_string

echo "Select operation:"
echo "1. Convert to lower case"
echo "2. Convert to upper case"
read choice

case $choice in
    1)
        converted_string=$(echo "$input_string" | tr '[:upper:]' '[:lower:]')
        echo "Converted string to lower case: $converted_string"
        ;;
    2)
        converted_string=$(echo "$input_string" | tr '[:lower:]' '[:upper:]')
        echo "Converted string to upper case: $converted_string"
        ;;
    *)
        echo "Invalid choice"
        ;;
esac

read -p "Press any key..." x