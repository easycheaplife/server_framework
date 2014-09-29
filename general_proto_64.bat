::@echo off
..\easy\dep\protobuf\vsprojects\x64\Debug\protoc.exe -I%cd% --cpp_out=%cd% %cd%\proto\transfer.proto