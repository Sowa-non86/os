#!/bin/bash

# Function to merge two subarrays
merge() {
    local arr=("$@")
    local n=${#arr[@]}
    local mid=$((n / 2))
    local left=("${arr[@]:0:mid}")
    local right=("${arr[@]:mid}")

    local i=0 j=0 k=0
    local result=()

    # Merge the two subarrays
    while ((i < ${#left[@]} && j < ${#right[@]})); do
        if ((left[i] <= right[j])); then
            result[k]=${left[i]}
            ((i++, k++))
        else
            result[k]=${right[j]}
            ((j++, k++))
        fi
    done

    # Copy remaining elements of left, if any
    while ((i < ${#left[@]})); do
        result[k]=${left[i]}
        ((i++, k++))
    done

    # Copy remaining elements of right, if any
    while ((j < ${#right[@]})); do
        result[k]=${right[j]}
        ((j++, k++))
    done

    echo "${result[@]}"
}

# Function to perform merge sort
merge_sort() {
    local arr=("$@")
    local n=${#arr[@]}

    # Base case: if array has one or no elements, it's already sorted
    if ((n <= 1)); then
        echo "${arr[@]}"
        return
    fi

    # Split array into two halves
    local mid=$((n / 2))
    local left=("${arr[@]:0:mid}")
    local right=("${arr[@]:mid}")

    # Recursively sort both halves
    left_sorted=($(merge_sort "${left[@]}"))
    right_sorted=($(merge_sort "${right[@]}"))

    # Merge the sorted halves
    merge "${left_sorted[@]}" "${right_sorted[@]}"
}

# Read array from user input
echo "Enter the elements of the array separated by space:"
read -a array

# Call the function and store the result
sorted_array=($(merge_sort "${array[@]}"))

# Display the sorted array
echo "Sorted array:"
echo "${sorted_array[@]}"
