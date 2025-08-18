# Server Framework

A C++ server framework for mobile game development, integrating tinynet, Google Protobuf, MongoDB, and other components.

## Quick Start

### Clone Repositories
```bash
git clone git@github.com:yuyunliuhen/server_framework.git
git clone git@github.com:yuyunliuhen/tinynet.git
git clone git@github.com:yuyunliuhen/easy.git
```

## Build Instructions

### Windows
1. Install Boost
   - Download from [Boost binaries](http://sourceforge.net/projects/boost/files/boost-binaries/)
   - Recommended version: 1.53 for VS2012

2. Install SCons
   - Download from [SCons website](http://www.scons.org/download.php)
   - Latest version: 2.3.3

3. Build MongoDB C++ Driver
   ```bash
   git clone https://github.com/mongodb/mongo-cxx-driver.git
   cd easy/dep/mongo-cxx-driver
   scons --cpppath="C:\local\boost_1_53_0" --libpath="C:\local\boost_1_53_0\lib64-msvc-11.0" --64 --sharedclient --dynamic-windows --dbg=on
   ```
   See [MongoDB Windows Guide](http://blog.chinaunix.net/uid-8625039-id-4446874.html) for details.

4. Build Jansson
   ```
   Open easy/dep/jansson/win32/vs2012/jansson.sln and build
   ```

5. Build Protobuf
   ```
   Open easy/dep/protobufvsprojects/protobuf.sln and build
   ```

6. Build Server Framework
   ```bash
   # Generate protocol files
   general_proto_64.bat
   
   # Using VS2012 x64 Cross Tools Command Prompt
   cmake -G "Visual Studio 11 Win64" .
   msbuild.exe ALL_BUILD.vcxproj
   ```

### Linux/macOS
1. Build Boost
   ```bash
   # Download from http://www.boost.org/
   tar zxvf boost_1_49_0.tar.gz
   cd boost_1_49_0
   ./bootstrap.sh
   ./b2 install
   ```

2. Install SCons
   ```bash
   # Download from http://www.scons.org/
   tar zxvf scons-2.3.3.tar.gz
   cd scons-2.3.3
   python setup.py install
   ```

3. Build Dependencies
   ```bash
   # Protobuf
   cd easy/dep/protobuf
   ./configure && make
   
   # Jansson
   cd easy/dep/jansson
   ./configure && make
   
   # MongoDB
   cd mongo-cxx-driver
   scons all
   # For custom boost path:
   # scons --cpppath="/home/lee/install/include" --libpath="/home/lee/install/lib"
   ```
   
   See [Google Protobuf Guide](http://blog.chinaunix.net/uid-8625039-id-4430741.html) and [MongoDB Linux Guide](http://blog.chinaunix.net/uid-8625039-id-4444101.html) for details.

4. Build Server Framework
   ```bash
   cd server_framework
   cmake . # For debug: cmake -DCMAKE_BUILD_TYPE=Debug .
   make
   ```

Alternative: Use build scripts
- Windows: `build_x64.bat` or `build_x86.bat` (Visual Studio 2012+)
- Linux: `build.sh` (GCC 4.8.1+)

Note: All dependency libraries are pre-built in the `dep` directory.

## Configuration

The configuration file is located at `config/servers_template.json`. You can add or remove core/proxy servers as needed.

## Running

### Linux Environment Setup
Set environment variables using `env.sh`, then:

```bash
./bin/core 192.168.20.135 8881
./bin/core 192.168.20.135 8882
./bin/proxy 192.168.20.135 8871
./bin/proxy 192.168.20.135 8872
./bin/login 192.168.20.135 8861

# Test client
./bin/test_client 192.168.20.135 8861
```

## Additional Resources

- [Performance Test Report](http://blog.chinaunix.net/uid-8625039-id-4911018.html)
- [NoSQL Integration Guide](http://blog.chinaunix.net/uid-8625039-id-4766151.html)
