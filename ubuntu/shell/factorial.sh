#!/bin/bash

# Recursive function to calculate factorial
factorial() {
    if [ $1 -eq 0 ] || [ $1 -eq 1 ]; then
        echo 1
    else
        local prev_factorial
        prev_factorial=$(factorial $(( $1 - 1 )))
        echo $(( $1 * $prev_factorial ))
    fi
}

# Take user input for the number
read -p "Enter a non-negative integer: " number

# Validate that the input is a non-negative integer
if ! [[ $number =~ ^[0-9]+$ ]]; then
    echo "Error: Please enter a non-negative integer."
    exit 1
fi

result=$(factorial $number)

echo "Factorial of $number is: $result"