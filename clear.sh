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

rm -rf lib/
echo 'end clear'
