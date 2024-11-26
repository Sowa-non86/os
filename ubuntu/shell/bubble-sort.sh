#!/bin/bash

# Function to perform Bubble Sort
bubble_sort() {
    local arr=("$@")
    local n=${#arr[@]}

    for ((i = 0; i < n-1; i++)); do
        for ((j = 0; j < n-i-1; j++)); do
            if [ ${arr[j]} -gt ${arr[j+1]} ]; then
                # Swap arr[j] and arr[j+1]
                temp=${arr[j]}
                arr[j]=${arr[j+1]}
                arr[j+1]=$temp
            fi
        done
    done

    echo "Sorted Array: ${arr[@]}"
}

# Input the number of elements
read -p "Enter the number of elements: " n

# Input the array elements
echo "Enter the elements of the array:"
for ((i = 0; i < n; i++)); do
    read element
    arr[i]=$element
done

echo "Original Array: ${arr[@]}"

# Call the bubble_sort function to sort the array
bubble_sort "${arr[@]}"
