#!/bin/bash

# Function to generate Fibonacci sequence
fibonacci() {
    local n=$1
    local a=0
    local b=1

    for ((i = 0; i < n; i++)); do
        echo -n "$a "
        local temp=$a
        a=$b
        b=$((temp + b))
    done
    echo
}

# Read input from user
echo "Enter the value of n (number of Fibonacci numbers to generate):"
read n

# Call the fibonacci function and display the sequence
echo "Fibonacci sequence of the first $n numbers:"
fibonacci $n