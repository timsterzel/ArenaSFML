#!/bin/bash
# Search recursive the given pattern and print out the filename, line and the content
# of the line where the pattern was found
if [ -z "$1" ]
    then
        echo "No pattern specified"
        exit 1
fi
# -r: recusive, -n: line number, -w: match whole world. '.': start in dir of script
pattern=$1
echo "Results for: \"$1\"":
grep -rnw . -e "$pattern"
