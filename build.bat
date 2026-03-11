@echo off

echo Building MACS...
if not exist "build" mkdir "build"
if not exist "build/obj" mkdir "build/obj"
cl /Fobuild\obj\ /I include daemon.c src\* /link /OUT:build\daemon.exe
doxygen
echo Done.