@echo off
::	for comment
cmake -G "Visual Studio 11 Win64" .
msbuild.exe ALL_BUILD.vcxproj
xcopy  /e /y  %cd%\dep\mongoc\x64\bin %cd%\bin\Debug
xcopy  /e /y  %cd%\dep\mongocxx\x64\lib\mongoclient-gd.dll %cd%\bin\Debug
xcopy  /e /y  %cd%\dep\jansson\x64\bin\jansson.dll %cd%\bin\Debug
xcopy  /e /y  c:\local\boost_1_53_0\lib64-msvc-11.0\boost_date_time-vc110-mt-gd-1_53.dll %cd%\bin\Debug
xcopy  /e /y  c:\local\boost_1_53_0\lib64-msvc-11.0\boost_thread-vc110-mt-gd-1_53.dll %cd%\bin\Debug
xcopy  /e /y  c:\local\boost_1_53_0\lib64-msvc-11.0\boost_system-vc110-mt-gd-1_53.dll %cd%\bin\Debug
xcopy  /e /y  c:\local\boost_1_53_0\lib64-msvc-11.0\boost_regex-vc110-mt-gd-1_53.dll %cd%\bin\Debug
md 	 		  %cd%\bin\Debug\config
copy 		  %cd%\config\servers_template.json %cd%\bin\Debug\config\servers.json
