
#--- CONFIGURATION ---#
clang = "C:\msys64\clang64\bin\clang.exe"
files = build.c
flags = /nologo /wd4996 /wd5050 /wd4838 /wd4100 /Zi /Ob0 /Od /MDd /EHsc /std:c11 /W3 /Fo: "temp\site.obj" /Fd"temp\site.pdb"
paths = /I "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\include" /I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\um" /I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\ucrt\"
libs = kernel32.lib user32.lib shlwapi.lib

build_exe = build.exe

#--- RULES ---#
main: $(build_exe)
	./$(build_exe)

$(build_exe): $(files) generator/generator.h
	cl $(files) $(libs) /Fe:"$(build_exe)" $(flags) $(paths)
