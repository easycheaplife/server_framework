::@echo off
..\easy\dep\protobuf\vsprojects\Debug\protoc.exe -I%cd% --cpp_out=%cd% %cd%\proto\transfer.proto