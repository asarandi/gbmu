#!/bin/sh

DEST="extras/roms/gbmicrotest/bin"
GBMU="$(pwd)/gbmu"

if [ ! -f "$GBMU" ]; then
	echo "cannot find gbmu" 1>&2
	exit 1
fi

if ! cd "$DEST"; then
	echo "failed to change directory" 1>&2
	exit 1
fi

echo "result,file"
for f in $(find . -iname "*.gb" | LC_ALL=C sort); do
	"$GBMU" -t gbmicrotest "$f"
	RET=$?

	if [ $RET -eq 10 ]; then
		echo "success,\"$f\""
	elif [ $RET -eq 11 ]; then
		echo "failure,\"$f\""
	elif [ $RET -eq 12 ]; then
		echo "timeout,\"$f\""
	elif [ $RET -eq 13 ]; then
		echo "error,\"$f\""
	else
		echo "other $RET,\"$f\""
	fi

	rm -f "${f%.gb}.sav"
done
