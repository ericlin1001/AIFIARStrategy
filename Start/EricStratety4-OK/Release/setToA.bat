@echo off
Rem Usage: XXX sourceFileName
Rem 用法:用命令行运行 XXX sourceFileName
Rem XXX 为本文件名


echo ******************%~nx0******************
set targetA="D:\myDocument\大一下学习\AI-FIAR\projects\A\StrategyA.dll"
set targetB="D:\myDocument\大一下学习\AI-FIAR\projects\B\StrategyB.dll"
Rem here to change
set targetFile=%targetA%

set sourceFile=
set sourceFile=%1

if "%sourceFile%"=="" (
echo Usage: %~nx0 sourceFileName
echo.
)

Rem getting the sourceFileName
:getsourceFile
if "%sourceFile%"=="" (
echo The dll files in current directory:
dir *.dll /B
set /p sourceFile=Source File:
)
if "%sourceFile%"=="" (
echo Pleae input the sourceFile! 
echo.
goto getsourceFile
)

Rem copy the sourceFile to the target
IF EXIST %sourceFile% (
IF EXIST %targetFile% (
del %targetFile%
IF EXIST %targetFile% (
echo Can't delete %targetFile%!
pause>nul
)
)
copy %sourceFile% %targetFile%
echo success!
) else (
echo Can't find %sourceFile%
echo fail!
pause>nul
)