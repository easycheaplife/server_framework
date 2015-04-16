#!/bin/bash
./general_proto.sh
LD_LIBRARY_PATH=/usr/local/lib:./dep/protobuf/x64/lib:./dep/jansson/x64/lib; export LD_LIBRARY_PATH
cmake .
make