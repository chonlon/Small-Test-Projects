#!/bin/bash

_left=1

if [ -n "$1" ]
then
    _left=$1
fi

_right = 600
if [ -n "$2" ]
then
    _right=$2
fi

for((i=$_left; i <= $_right; i++));
do
    file_name="Ep$i"
    if [ -f $file_name.cpp ];then
        git add $file_name.cpp
        git commit -m "add: (c++ weekly) $file_name"
    fi
done
