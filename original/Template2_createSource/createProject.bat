@echo off
set /p projectName=projectName:
set src=.
set dest=..\%projectName%

md %dest%\Release
md %dest%\%projectName%

copy %src%\Template2.sln %dest%\%projectName%.sln
copy %src%\Release\setToA.bat %dest%\Release\setToA.bat
copy %src%\Release\setToB.bat %dest%\Release\setToB.bat
copy %src%\Template2\Template2.vcxproj %dest%\%projectName%\%projectName%.vcxproj
copy %src%\Template2\Template2.vcxproj.user %dest%\%projectName%\%projectName%.vcxproj.user
copy %src%\Template2\Template2.vcxproj.filters %dest%\%projectName%\%projectName%.vcxproj.filters
copy %src%\Template2\source\* %dest%\%projectName%\

echo please change the %projectName%.sln
echo and trun the project configuration to Release
pause>nul


