#!/bin/bash
if [ `env | grep -c "LD_LIBRARY_PATH"` -ge 1 ];
 then
     LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./so:../easy/dep/protobuf/src/.libs; export LD_LIBRARY_PATH

 else
     LD_LIBRARY_PATH=./so:../easy/dep/protobuf/src/.libs; export LD_LIBRARY_PATH
 fi
