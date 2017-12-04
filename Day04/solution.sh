#!/bin/bash

sed -re "/\<(\w+)\>.*\<\1\>/d" input.txt | wc -l
exit 0

# Original solution (absolutely disgusting and extremely slow)
cat input.txt | while read line
do
    for word in $line
    do
        echo $word | grep -o . | sort | tr -d "\n"
        echo " "
    done | tr -d "\n"
    echo " "
done | sed -re "/\<(\w+)\>.*\<\1\>/d" | wc -l
