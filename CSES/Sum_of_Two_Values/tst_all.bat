cls
g++ -std=c++11 -O2 -Wall  main.cpp
@echo off
FOR /L %%i IN (0,1,%1) DO (
	echo %%i
	start  cmd.exe /c tst.bat %%i
)

