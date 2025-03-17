#!/bin/bash

file="$1"
if [ -f "$file" ]; then
	shift
	for pattern in "$@"; do
		echo "Lines containing '$pattern' at last in sorted order:"
		grep -E "$pattern\$" "$file" | sort
	done
else
	echo "Error: File does not exist."
	exit
fi
