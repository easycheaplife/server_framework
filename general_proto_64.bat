::@echo off
.\dep\protobuf\x64\bin\protoc.exe -I%cd% --cpp_out=%cd% %cd%\proto\transfer.proto
.\dep\protobuf\x64\bin\protoc.exe -I%cd% --cpp_out=%cd% %cd%\proto\login.proto
.\dep\protobuf\x64\bin\protoc.exe -I%cd% --cpp_out=%cd% %cd%\proto\common.proto