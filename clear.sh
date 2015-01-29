#!/bin/bash
echo 'start clear'
rm -rf CMakeFiles
rm -f cmake_install.cmake
rm -f CMakeCache.txt
rm -f Makefile

rm -rf login/CMakeFiles
rm -f login/cmake_install.cmake
rm -f login/CMakeCache.txt
rm -f login/Makefile

rm -rf proxy/CMakeFiles
rm -f proxy/cmake_install.cmake
rm -f proxy/CMakeCache.txt
rm -f proxy/Makefile

rm -rf core/CMakeFiles
rm -f core/cmake_install.cmake
rm -f core/CMakeCache.txt
rm -f core/Makefile

rm -rf test_client/CMakeFiles
rm -f test_client/cmake_install.cmake
rm -f test_client/CMakeCache.txt
rm -f test_client/Makefile

rm -rf bin
rm -rf lib

echo 'end clear'
