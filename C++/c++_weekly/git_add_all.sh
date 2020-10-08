#!/bin/bash

declare -A dict

for file_name in $( find . -maxdepth 1 -regex "\./Ep[0-9]*\.cpp" -type f -size +0 | grep -P "Ep[0-9]*\\.cpp" -o)
do
    dict[$file_name]=1
done

for file_name in $(git ls-files --others --exclude-standard)
do
    [ ${dict[${file_name}]+abc} ] && git add $file_name && git commit -m "add: (c++ weekly) $(echo $file_name | grep -P "Ep[0-9]*" -o)"
    #[ ${dict[${file_name}]+abc} ] && echo "$(echo $file_name | grep -P "Ep[0-9]*" -o)"
done