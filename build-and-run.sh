#!/bin/bash
if [ $# -gt 0 ] && [ $1 -eq 1 ]
then
    echo "Clearing build directory..."
    rm -rf build
    mkdir build
fi

cd build
cmake ..
make

./Program2/Program2 -k "ABCD1234ABCD1234ABCD1234ABCD1234" &

sleep 1

./Program1/Program1 -k "ABCD1234ABCD1234ABCD1234ABCD1234" -m "Message to encrypt"

sleep 1

exit 0