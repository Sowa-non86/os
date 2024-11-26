#!/bin/bash
echo "Enter 10 numbers:"
for ((i=0; i<10; i++)); do
    read arr[$i]
done

IFS=$'\n' sorted=($(sort -n <<<"${arr[*]}"))
second_largest="${sorted[-2]}"
echo "Second largest number is: $second_largest"
