#!/bin/bash
if [ `env | grep -c "LD_LIBRARY_PATH"` -ge 1 ];
 then
     LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:./dep/protobuf/x64/lib:./dep/jansson/x64/lib; export LD_LIBRARY_PATH

 else
     LD_LIBRARY_PATH=/usr/local/lib:./dep/protobuf/x64/lib:./dep/jansson/x64/lib; export LD_LIBRARY_PATH
 fi
