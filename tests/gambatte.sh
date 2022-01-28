#!/bin/bash

gbmu="$(pwd)/gbmu"
if [ ! -f "$gbmu" ]; then
    echo "cannot find gbmu" >&2
    exit 1
fi

cd "extras/roms/gambatte/test/hwtests/$1"
if [ $? -ne 0 ]; then
    echo "failed to change dir" >&2
    exit 1
fi

echo "result,file"
for f in $(find . -iname "*dmg*out*.gb*" | LC_ALL=C sort); do
    "$gbmu" -t gambatte "$f"
    ret=$?
    if [ $ret -eq 10 ]; then
        echo "success,\"$f\""
    elif [ $ret -eq 11 ]; then
        echo "failure,\"$f\""
    elif [ $ret -eq 12 ]; then
        echo "timeout,\"$f\""
    elif [ $ret -eq 13 ]; then
        echo "error,\"$f\""
    else
        echo "other $ret,\"$f\""
    fi
done
