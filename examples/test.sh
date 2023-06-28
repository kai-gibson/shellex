#!/bin/sh

mkdir "abc"
for i in $(seq 1 5000)
do
    touch abc/$i
    echo "$i proc 1" >> abc/$i
done
var=$(cat abc/*)
echo $var | grep 2 &>/dev/null
rm -rf abc
