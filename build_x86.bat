@echo off
::	for comment
cmake -G "Visual Studio 11" .
msbuild.exe ALL_BUILD.vcxproj
xcopy  /e /y  %cd%\dep\mongoc\x86\bin %cd%\bin\Debug