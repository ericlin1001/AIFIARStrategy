@echo off
set filename=%1

set targetFileName="D:\myDocument\大一下学习\AI-FIAR\projects\A\StrategyA.dll"
IF EXIST %filename% (
IF EXIST %targetFileName% (
del %targetFileName%
IF EXIST %targetFileName% (
echo Can't delete %targetFileName%!
pause>nul
)
)
copy %filename% %targetFileName%
echo success!
) else (
echo Can't find %filename%
echo fail!
pause>nul
)