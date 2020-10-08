#!/bin/bash

for file_name in $(ls . | grep "Ep[0-9]*\.cpp")
do
    git add $file_name
    git commit -m "add: (c++ weekly) $file_name"
done