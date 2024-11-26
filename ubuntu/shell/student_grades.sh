#!/bin/bash
echo "Enter student's score: "
read score

if [ $score -ge 90 ]; then
    echo "Grade: O"
elif [ $score -ge 80 ]; then
    echo "Grade: E"
elif [ $score -ge 70 ]; then
    echo "Grade: A"
elif [ $score -ge 60 ]; then
    echo "Grade: B"
elif [ $score -ge 50 ]; then
    echo "Grade: P"
else
    echo "Grade: F"
fi
