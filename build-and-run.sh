#!/bin/bash
if [ $# -gt 0 ] && [ $1 -eq 1 ]
then
    echo "Clearing build directory..."
    rm -rf build
    mkdir build
fi

echo "Building..."

cd build
cmake ..
make

echo "Running example..."

./src/Program2/Program2 -k "40baaed112a2fdc0934055fd625f906a4a21a07c6aaf45de691b4f6962f10b88" &

sleep 1

./src/Program1/Program1 -k "40baaed112a2fdc0934055fd625f906a4a21a07c6aaf45de691b4f6962f10b88" -m "Message to encrypt"

sleep 1

echo "Done!"

exit 0