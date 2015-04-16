server_framework
================

a c++ server framework for mobile game which uses tinynet,google protobuf,mongodb and so on. 



build:
---
download or git from github:<br>
$git clone git@github.com:yuyunliuhen/easy.git<br>
$git clone git@github.com:yuyunliuhen/tinynet.git<br>
$git clone git@github.com:yuyunliuhen/server_framework.git<br>

#####windwos
(1) compiler or install boost<br>
download from boost binaries: http://sourceforge.net/projects/boost/files/boost-binaries/, recommend 1.53 if you use vs2012.

(2) install scons<br>
download from http://www.scons.org/download.php, the latest version is 2.3.3<br>

(3) compiler mongodb c++ driver<br>
git clone https://github.com/mongodb/mongo-cxx-driver.git (current latest stable version is 26compat) .<br>
$cd easy/dep/mongo-cxx-driver, excute command at cmd:<br>
scons --cpppath="C:\local\boost_1_53_0" --libpath="C:\local\boost_1_53_0\lib64-msvc-11.0" --64 --sharedclient --dynamic-windows --dbg=on<br>
more detail:<br>
[mongodb windows ](http://blog.chinaunix.net/uid-8625039-id-4446874.html)<br>

(4) compiler jansson<br>
open easy/dep/jansson/win32/vs2012/jansson.sln and compiler it <br>

(4) compiler protobuf<br>
open easy/dep/protobufvsprojects/protobuf.sln and compiler it <br>

(6) compile server framework<br>
general proto files first, if not call this file, error will be happend when compiler later<br>
general_proto_64.bat<br>
use windwos command tools:VS2012 x64 Cross Tools Command Prompt <br>
cmake -G "Visual Studio 11 Win64" . <br>
msbuild.exe ALL_BUILD.vcxproj

#####linux
(1) compile boost
download from boost:http://www.boost.org/<br>
$tar zxvf boost_1_49_0.tar.gz<br>
$cd boost_1_49_0<br>
$./bootstrap.sh<br>
$./b2 install<br>

(2) compiler scons for mongodb cxx driver<br>
download from scons:http://www.scons.org/<br>
$tar zxvf scons-2.3.3.tar.gz<br>
$cd scons-2.3.3 & python setup.py install <br>

(3) compiler protobuf<br>
$cd easy/dep/protobuf<br>
$./configure & make<br>
more detail:<br>
[google protobuf](http://blog.chinaunix.net/uid-8625039-id-4430741.html)<br>

(4)	compiler jansson<br>
$cd easy/dep/jansson<br>
$./configure & make<br>

(5)	compiler mongodb<br>
$cd .. & cd mongo-cxx-driver<br>
$scons all (if you install boost is not default,you can use like this:scons --cpppath="/home/lee/install/include" --libpath="/home/lee/install/lib")<br>
more detail:<br>
[mongodb linux ](http://blog.chinaunix.net/uid-8625039-id-4444101.html) <br>

(6) compile server framework<br>
$cd server_framework <br>
$cmake . ( if you want to debug ,you should do cmake -DCMAKE_BUILD_TYPE=Debug .<br>
$make<br>

######or
excute build_x64/x86.bat at windows(visual studio 2012 or later ) or build.sh at linux(gcc 4.8.1 or later ). all dependency static/dynamic library and exe are build and place at dep directory, you can use it directly.

configure:
---
you can find file at config directory. it looks like that:<br>
![](http://img.blog.csdn.net/20150416160100480)
add or remove core/proxy server if you want.<br>

run:
---
#####linux
set environment:<br>
![](http://img.blog.csdn.net/20150416160501831)
 and then <br>
 $./bin/core 192.168.20.135 8881<br>
 $./bin/core 192.168.20.135 8882<br>
 $./bin/proxy 192.168.20.135 8871<br>
 $./bin/proxy 192.168.20.135 8872<br>
 $./bin/login 192.168.20.135 8861<br>
 
 test:<br>
 $./bin/test_client 192.168.20.135 8861<br>
 
press test:
---
[server framework performance test](http://blog.chinaunix.net/uid-8625039-id-4911018.html)<br>


