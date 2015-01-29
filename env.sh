#!/bin/bash
if [ `env | grep -c "LD_LIBRARY_PATH"` -ge 1 ];
 then
     LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:../easy/dep/protobuf/src/.libs:../easy/dep/mongo-c-driver/src/libbson/.libs:../easy/dep/mongo-c-driver/.libs:../easy/dep/jansson/src/.libs; export LD_LIBRARY_PATH

 else
     LD_LIBRARY_PATH=/usr/local/lib:../easy/dep/protobuf/src/.libs:../easy/dep/mongo-c-driver/src/libbson/.libs:../easy/dep/mongo-c-driver/.libs:../easy/dep/jansson/src/.libs; export LD_LIBRARY_PATH
 fi
