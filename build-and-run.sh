#!/bin/bash
rm -rf build
mkdir build && cd build
cmake ..
make

./Program2/Program2 -k "ABCD1234ABCD1234ABCD1234ABCD1234"
./Program1/Program1 -k "ABCD1234ABCD1234ABCD1234ABCD1234" -m "Message to encrypt"

exit 0