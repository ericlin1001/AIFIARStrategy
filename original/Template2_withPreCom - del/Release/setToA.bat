@echo off
Rem Usage: XXX sourceFileName
Rem �÷�:������������ XXX sourceFileName
Rem XXX Ϊ���ļ���


echo ******************%~nx0******************
set targetA="D:\myDocument\��һ��ѧϰ\AI-FIAR\projects\A\StrategyA.dll"
set targetB="D:\myDocument\��һ��ѧϰ\AI-FIAR\projects\B\StrategyB.dll"
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