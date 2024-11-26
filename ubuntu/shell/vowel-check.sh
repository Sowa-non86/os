#!/bin/bash
echo "Enter a character: "
read char

case $char in
    [aeiouAEIOU])
        echo "$char is a vowel."
        ;;
    *)
        echo "$char is not a vowel."
        ;;
esac
