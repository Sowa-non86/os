#!/bin/bash

# Function to search for an element in an array
search_element() {
    local arr=("$@")
    local n=${#arr[@]}
    
    read -p "Enter the element to search: " target

    found=false

    for ((i = 0; i < n; i++)); do
        if [ "${arr[i]}" == "$target" ]; then
            found=true
            index=$((i))
            break
        fi
    done

    if [ "$found" == true ]; then
        echo "Element '$target' found at index $index."
    else
        echo "Element '$target' not found in the array."
    fi
}

# Input the number of elements
read -p "Enter the number of elements in the array: " n

# Input the array elements
echo "Enter the elements of the array:"
for ((i = 0; i < n; i++)); do
    read element
    arr[i]=$element
done

echo "Array: ${arr[@]}"

# Call the search_element function to search for an element
search_element "${arr[@]}"
