#!/bin/bash

# Function to perform insertion sort
insertion_sort() {
    local arr=("$@")
    local n=${#arr[@]}

    for ((i = 1; i < n; i++)); do
        key=${arr[i]}
        j=$((i - 1))

        # Move elements that are greater than key
        # one position ahead of their current position
        while ((j >= 0 && arr[j] > key)); do
            arr[j + 1]=${arr[j]}
            ((j--))
        done

        arr[j + 1]=$key
    done

    echo "${arr[@]}"
}

# Read array from user input
echo "Enter the elements of the array separated by space:"
read -a array

# Call the function and store the result
sorted_array=($(insertion_sort "${array[@]}"))

# Display the sorted array
echo "Sorted array:"
echo "${sorted_array[@]}"
