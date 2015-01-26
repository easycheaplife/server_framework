::@echo off
..\easy\dep\protobuf\vsprojects\Debug\protoc.exe -I%cd% --cpp_out=%cd% %cd%\proto\transfer.proto
..\easy\dep\protobuf\vsprojects\Debug\protoc.exe -I%cd% --cpp_out=%cd% %cd%\proto\login.proto
..\easy\dep\protobuf\vsprojects\Debug\protoc.exe -I%cd% --cpp_out=%cd% %cd%\proto\common.proto