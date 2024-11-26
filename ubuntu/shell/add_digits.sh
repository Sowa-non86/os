#!/bin/bash

# Prompt the user to enter a three-digit number
echo "Enter a three-digit number:"
read number

# Extract individual digits
digit1=$((number / 100))
digit2=$(((number / 10) % 10))
digit3=$((number % 10))

# Calculate the sum of every pair of digits
sum1=$((digit1 + digit2))
sum2=$((digit2 + digit3))
sum3=$((digit1 + digit3))


# Display the results
echo "Sum of every pair of digits: $sum1 $sum2 $sum3"
