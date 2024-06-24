#!/bin/sh
# Print each argument passed to the script
i=1
for arg in "$@"; do
    echo "av[$i]: $arg"
    i=$((i + 1))
done
