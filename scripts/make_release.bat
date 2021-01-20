@echo off

setlocal EnableDelayedExpansion

set version=%1

if [%1]==[-h] (
	goto :ShowUsage
)

if [%1]==[--help] (
	goto :ShowUsage
)

REM verify version arg
if /I [!version!]==[] (
	echo ERROR: version number for release not set.
	echo.
	goto :ShowUsage
)

if /I ["!version:~0,1!"] NEQ ["v"] (
	echo ERROR: version number MUST start with a "v".
	echo.
	goto :ShowUsage
)

REM now make release
pushd %~dp0
pushd ..

tools\\7zip\\7za.exe a -tzip releases\\temper_!version!.zip temper.h README.md LICENSE

popd
popd

goto :EOF


:ShowUsage
echo Usage:
echo.
echo %~nx0 ^<version^>:
echo.
echo Arguments:
echo     [-h^|--help] (optional):
echo         Shows this help and exits.
echo.
echo     ^<version^> (required):
echo         The version number of the release.  E.G.: v1.2.0.
echo         MAKE THE RELEASE NUMBER START WITH A 'v'.
goto :EOF