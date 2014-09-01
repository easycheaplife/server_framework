#!/bin/bash
echo "start compile protobuf"
cd .. && cd easy/dep/protobuf
./configure 
make
echo "protobuf compile end"

echo "start compile server framework"
cd ..
cd ..
cd ..
cd server_framework
cmake .
make
echo "server framework compile end"

