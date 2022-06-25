#!/bin/bash

sh ~/.fehbg
wmname compiz

arr=("copyq" "fcitx" "dunst" "clipmenud" "cfw" "nutstore")

for value in ${arr[@]}; do
    if [[ ! $(pgrep ${value}) ]]; then
        exec "$value" &
    fi
done

if [[ ! $(pgrep "xob") ]]; then
    exec sxob
fi
