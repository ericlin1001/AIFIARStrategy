@echo off
title setRunStrategy.bat
set updateCount=0
set srcA="Z:\projects\A\StrategyA.dll"
set srcB="Z:\projects\B\StrategyB.dll"
set destA="C:\AIRobot\Strategy\runningA.dll"
set destB="C:\AIRobot\Strategy\runningB.dll"


if exist %srcA% (
if exist %destA% (
del %destA%
)
if not exist %destA% (
copy %srcA% %destA%>nul
del %srcA%
echo Update runningA.dll successfully!
set /a updateCount=%updateCount%+1
)
)

if exist %srcB% (
if exist %destB% (
del %destB%
)
if not exist %destB% (
copy %srcB% %destB%>nul
del %srcB%
echo Update runningB.dll successfully!
set /a updateCount=%updateCount%+1
) else (
echo can't del %destB%
)
) else (
echo not exit %srcB%
)
echo.
echo In all,Update %updateCount% files!
pause