#!/bin/bash

if [ -n "$1" ]
then
    git add Ep$1.cpp
    git commit -m "add: (c++ weekly) Ep$1"
else
    echo "usage: ./git_add_one.sh [num]"
fi