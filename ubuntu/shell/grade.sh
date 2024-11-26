#!/bin/bash

# Function to calculate grade based on marks
get_grade() {
    if [ $1 -lt 30 ]; then
        echo "Fail"
    elif [ $1 -lt 40 ]; then
        echo "D"
    elif [ $1 -lt 50 ]; then
        echo "C"
    elif [ $1 -lt 60 ]; then
        echo "B"
    elif [ $1 -lt 70 ]; then
        echo "B+"
    elif [ $1 -lt 80 ]; then
        echo "A"
    elif [ $1 -lt 90 ]; then
        echo "A+"
    else
        echo "O"
    fi
}

# Take input for 5 subjects
echo "Enter marks for 5 subjects (out of 100):"

for i in {1..5}
do
    read -p "Enter marks for Subject $i: " marks
    if [ $marks -lt 30 ]; then
        fail=true
    fi
    grades[$i]=$(get_grade $marks)
    total_marks=$((total_marks + marks))
done

# Check if any subject is failed
if [ "$fail" = true ]; then
    echo "ATKT/Fail"
else
    # Calculate percentage
    percentage=$((total_marks / 5))
    echo "Percentage: $percentage%"

    # Display grades
    for i in {1..5}
    do
        echo "Grade for Subject $i: ${grades[$i]}"
    done
fi
