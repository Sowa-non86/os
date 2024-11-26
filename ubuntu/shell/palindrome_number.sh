#!/bin/bash
echo "Enter a number: "
read num
reverse=0
temp=$num
while [ $num -gt 0 ]; do
    digit=$((num % 10))
    reverse=$((reverse * 10 + digit))
    num=$((num / 10))
done
if [ $temp -eq $reverse ]; then
    echo "$temp is a palindrome."
else
    echo "$temp is not a palindrome."
fi
