#!/bin/bash

# Read the main string
echo "Enter the main string:"
read main_string

# Read the substring
echo "Enter the substring to check:"
read substring

# Check if the substring exists in the main string
if [[ "$main_string" == *"$substring"* ]]; then
    echo "The substring '$substring' is present in the main string."
else
    echo "The substring '$substring' is NOT present in the main string."
fi
