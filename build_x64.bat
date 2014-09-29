@echo off
::	for comment
cmake -G "Visual Studio 11 Win64" .
msbuild.exe ALL_BUILD.vcxproj
xcopy  /e /y  %cd%\dep\mongoc\x64\bin %cd%\bin\Debug
