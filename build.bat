@echo off

echo Building MACS...
if not exist "build" mkdir "build"
if not exist "build/obj" mkdir "build/obj"
if not exist "build/docs" mkdir "build/docs"
cl /Fobuild\obj\ /I include src\*.c /link /OUT:build\daemon.exe
doxygen
echo Done.