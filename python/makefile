cc = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\cl.exe"
cflags = /I"C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.29.30133\include" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.20348.0\shared" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.20348.0\ucrt" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.20348.0\um" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.20348.0\winrt" /I"C:\Users\SteveChung\AppData\Local\Programs\Python\Python310\include"
ldflags =  /LIBPATH:../ /LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.29.30133\lib\x64" /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.20348.0\ucrt\x64" /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.20348.0\um\x64" /LIBPATH:"C:\Users\SteveChung\AppData\Local\Programs\Python\Python310\libs"
libs = python310.lib GetFanInfo.lib

pyd:
	$(cc) $(cflags) /c pythonBinding.cc /Fo:pythonBinding.obj
	$(cc) /LD pythonBinding.obj /link $(ldflags) $(libs) /OUT:GetFanInfo.pyd
	-del pythonBinding.obj pythonBinding.exp pythonBinding.lib