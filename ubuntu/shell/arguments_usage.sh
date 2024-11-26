#!/bin/bash
if [ $# -ne 2 ]; then
    echo "Usage: $0 arg1 arg2"
    exit 1
fi
echo "First argument: $1"
echo "Second argument: $2"