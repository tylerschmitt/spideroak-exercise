#!/bin/bash
rm -rf build
mkdir build && cd build
cmake ..
make

# ./Program2/Program2 -k "KEYKEYKEY"
# ./Program1/Program1 -k "KEYKEYKEY" -m "Message to encrypt"