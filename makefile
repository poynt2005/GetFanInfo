cc = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\cl.exe"
cflags = /I"C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.29.30133\include" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.20348.0\shared" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.20348.0\ucrt" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.20348.0\um" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.20348.0\winrt" 
ldflags =  /LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.29.30133\lib\x64" /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.20348.0\ucrt\x64" /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.20348.0\um\x64"
libs = wbemuuid.lib 	Ole32.lib OleAut32.lib

dll:
	$(cc) /DBUILDFANINFOAPI $(cflags) /c GetFanInfo.cc /Fo:GetFanInfo.obj
	$(cc) /LD GetFanInfo.obj /link $(ldflags) $(libs) /OUT:GetFanInfo.dll /IMPLIB:GetFanInfo.lib
	-del GetFanInfo.obj GetFanInfo.exp