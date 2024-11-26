#!/bin/bash

# Function to count lines, words, and characters in a file
count_file_stats() {
    local file="$1"
    
    if [ -f "$file" ]; then
        lines=$(wc -l < "$file")
        words=$(wc -w < "$file")
        characters=$(wc -m < "$file")
        
        echo "Number of lines in '$file': $lines"
        echo "Number of words in '$file': $words"
        echo "Number of characters in '$file': $characters"
    else
        echo "File '$file' does not exist."
    fi
}

# Input the filename
read -p "Enter the filename: " filename

# Create the file and allow user input
echo "Enter text into the file. Press Ctrl+D when done."
cat > "$filename"

# Call the count_file_stats function to count lines, words, and characters
count_file_stats "$filename"
