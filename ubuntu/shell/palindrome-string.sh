#!/bin/bash

# Function to check if a string is a palindrome
is_palindrome() {
    local input="$1"
    local reversed=""
    local len=${#input}

    for ((i = len - 1; i >= 0; i--)); do
        reversed="${reversed}${input:$i:1}"
    done

    if [ "$input" == "$reversed" ]; then
        echo "The string '$input' is a palindrome."
    else
        echo "The string '$input' is not a palindrome."
    fi
}

# Input the string
read -p "Enter a string: " input_string

# Remove spaces and convert to lowercase (optional, for case-insensitive checks)
input_string=$(echo "$input_string" | tr -d ' ' | tr '[:upper:]' '[:lower:]')

# Call the is_palindrome function to check if it's a palindrome
is_palindrome "$input_string"
