@echo off
echo ----------------------------------------------------
echo Press any key to delete all files with ending:
echo  *.aps *.idb *.ncp *.obj *.pch *.tmp *.sbr
echo Visual c++/.Net junk 
echo delete file folder use    rd  /S /Q .svn 
echo delete hide file use    del /F /Q /S /A:H-S
echo ----------------------------------------------------

del /F /Q /S *.aps *.idb *.ncp *.obj *.pch *.sbr *.tmp *.pdb *.bsc *.ilk *.res *.ncb *.opt *.suo *.manifest *.dep *.user *.sdf *.sln *.vcxproj *.filters *.cmake *.opensdf *.sdf 
del /F /Q /S /A:H-S server_framework.v11.suo 
rd  /S /Q CMakeFiles Debug Win32 proto.dir tinynet.dir  easy.dir x64 wrpcrt4.pdb lib bin
del /F /Q /S CMakeCache.txt

cd login
clear.bat
cd ..
cd test_client
clear.bat
pause