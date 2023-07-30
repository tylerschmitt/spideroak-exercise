#!/bin/bash
if [ $# -gt 0 ] && [ $1 -eq 1 ]
then
    echo "\nClearing build directory..."
    rm -rf build
fi

if [ ! -d "/path/to/dir" ]
then 
    mkdir build
fi


echo "\nBuilding..."
cd build
cmake ..
make

echo "\nRunning tests..."
./spideroak_test crypto_test

echo "\nRunning good example..."
./Program2 -k "40baaed112a2fdc0934055fd625f906a" &
sleep 1
./Program1 -k "40baaed112a2fdc0934055fd625f906a" -m "Message to encrypt"
sleep 1

echo "\nRunning bad example..."
./Program2 -k "40baaed112a2fdc0934055fd625f906a" &
sleep 1
./Program1 -k "40baaed112a2fdc0934055fd625f906b" -m "Message to encrypt"
sleep 1

echo "\nDone!"

exit 0