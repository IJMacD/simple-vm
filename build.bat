@echo off
if not exist obj mkdir obj
if not exist bin mkdir bin
cd obj
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:../bin/vm.exe
cl.exe %compilerflags% ../src/*.c ../src/windows/*.c /link %linkerflags%
