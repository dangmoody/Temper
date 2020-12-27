@echo off

setlocal EnableDelayedExpansion

set demo_name=%1
if /I [%demo_name%]==[] (
	echo ERROR: Demo name was empty.  You need to specify the name of the demo, without the file extension.
	goto :ShowUsage
)

set config=%2
if /I [%config%]==[] (
	echo ERROR: The config must either be debug or release.
	goto :ShowUsage
)

set symbols=""
if /I [%config%]==[debug] (
	set symbols=-g
)

set optimisation=""
if /I [%config%]==[release] (
	set optimisation=-O3
)

set defines=-D_CRT_SECURE_NO_WARNINGS

if /I [%config%]==[debug] (
	set defines=!defines! -D_DEBUG
)

if /I [%config%]==[release] (
	set defines=!defines! -DNDEBUG
)

set warninglevels=-Werror -Wall -Wextra -Weverything -Wpedantic

set ignorewarnings=-Wno-newline-eof

REM set cwd to the folder that the batch file is in
pushd %~dp0
pushd "..\\"

set demo_folder=demos\\%demo_name%
set build_dir=bin\\win64\\%config%\\demos

if not exist %build_dir% (
	mkdir %build_dir%
)

clang -std=c99 -o %build_dir%\\%demo_name%.exe !symbols! !optimisation! !defines! %warninglevels% %ignorewarnings% %demo_folder%\\%demo_name%.c

popd
popd

goto :EOF


:ShowUsage
echo Usage:
echo build.bat ^<demo_name^> ^<config^>
echo.
echo Arguments:
echo     ^<demo_name^> (required):
echo         The name of the demo.  You probably want the name of the source file here (without the file extension).
echo.
echo     ^<config^> (required):
echo         MUST be either debug or release.

goto :EOF