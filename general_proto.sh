#!/bin/bash
export LD_LIBRARY_PATH=../easy/dep/protobuf/src/.libs
../easy/dep/protobuf/src/.libs/protoc -I./ --cpp_out=./ ./proto/transfer.proto
../easy/dep/protobuf/src/.libs/protoc -I./ --cpp_out=./ ./proto/login.proto
