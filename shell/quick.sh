#!/bin/bash
# Function to perform quicksort
quick_sort() {
    local arr=("$@")
    local len=${#arr[@]}
    if [ "$len" -le 1 ]; then
        echo "${arr[@]}"
    else
        local pivot=${arr[0]}
        local left=()
        local right=()

        for ((i=1; i<len; i++)); do
            if [ "${arr[i]}" -lt "$pivot" ]; then
                left+=("${arr[i]}")
            else
                right+=("${arr[i]}")
            fi
        done

        echo "$(quick_sort "${left[@]}") $pivot $(quick_sort "${right[@]}")"
    fi
}

# Main part
echo "Enter the number of elements to be sorted:"
read n
echo "Enter the numbers:"
for ((i = 0; i < n; i++)); do
    read arr[$i]
done

# Call the quick_sort function and display the sorted result
sorted_arr=($(quick_sort "${arr[@]}"))
echo "Sorted list:"
echo "${sorted_arr[@]}"
