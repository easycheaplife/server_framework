#!/bin/bash
export LD_LIBRARY_PATH=./dep/protobuf/x64/lib
./dep/protobuf/x64/bin/protoc -I./ --cpp_out=./ ./proto/transfer.proto
./dep/protobuf/x64/bin/protoc -I./ --cpp_out=./ ./proto/login.proto
./dep/protobuf/x64/bin/protoc -I./ --cpp_out=./ ./proto/common.proto
