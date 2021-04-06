#!/bin/bash

cd extras/roms/mooneye-gb_hwtests/
if [ $? -ne 0 ]; then
    exit 1
fi

if [ ! -f ../../../gbmu ]; then
    echo "cannot find gbmu"
    exit 1
fi

for f in $(find acceptance/ -iname "*.gb" | sort); do
    ../../../gbmu -t mooneye "$f"
    ret=$?
    if [ $ret -eq 10 ]; then
        echo "success $f"
    elif [ $ret -eq 11 ]; then
        echo "failure $f"
    elif [ $ret -eq 12 ]; then
        echo "timeout $f"
    else
        echo "other $ret $f"
    fi
done
