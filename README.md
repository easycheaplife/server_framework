server_framework
================

a c++ server framework for mobile game which uses tinynet,google protobuf,mongodb and so on. 

ready:
---
[mongodb linux ](http://blog.chinaunix.net/uid-8625039-id-4444101.html) <br>
[mongodb windows ](http://blog.chinaunix.net/uid-8625039-id-4446874.html)<br>
[google protobuf](http://blog.chinaunix.net/uid-8625039-id-4430741.html)<br>
[easy](https://github.com/yuyunliuhen/easy)<br>
[tinynet](https://github.com/yuyunliuhen/tinynet)

build:
---
#####windwos
use windwos command tools:VS2012 x64 Cross Tools Command Prompt
cmake -G "Visual Studio 11 Win64" .
msbuild.exe ALL_BUILD.vcxproj

#####linux
$cmake . & make

######or
excute build_x64/x86.bat at windows(visual studio 2012 or later ) or build.sh at linux(gcc 4.8.1 or later ).




