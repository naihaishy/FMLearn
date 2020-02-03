@echo off
REM # build from source code in vs
mkdir build_win && cd build_win && ^
cmake -G "Visual Studio 15 2017 Win64" ../ && ^
FMLearn.sln
@pause