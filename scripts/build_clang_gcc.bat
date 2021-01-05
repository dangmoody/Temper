@echo off

setlocal EnableDelayedExpansion

set output_filename=""
set compiler=""
set config=""
set source_files=""

set foundSourceFiles=0

REM store this now because were about to fuck around with all the cmd line args
set cwd=%~dp0

:ParseArgs
if "%1" NEQ "" (
	if /I [%1]==[-h] (
		goto :ShowUsage
	)

	if /I [%1]==[--help] (
		goto :ShowUsage
	)

	if /I [%1]==[--output] (
		set output_filename=%2
	)

	if /I [%1]==[--compiler] (
		set compiler=%2
	)

	if /I [%1]==[--config] (
		set config=%2
	)

	if /I [%1]==[--source] (
		set foundSourceFiles=1
		goto :VerifyArgs
	)

	shift

	goto :ParseArgs
)

:VerifyArgs
if /I [!output_filename!]==[""] (
	echo ERROR: --output argument not specified.
	echo.
	goto :ShowUsage
)

if /I [!compiler!]==[""] (
	echo ERROR: --compiler argument not specified.
	echo.
	goto :ShowUsage
)

if /I [!config!]==[""] (
	echo ERROR: --config argument not specified.
	echo.
	goto :ShowUsage
)

if %foundSourceFiles%==0 (
	echo ERROR: --source argument not specified.
	echo.
	goto :ShowUsage
)

REM get all of the source files specified after the --source arg
shift
set source_files=%1
:GetSourceFilesArgs
shift
if [%1]==[] goto :Build
set source_files=!source_files! %1
goto :GetSourceFilesArgs

REM now we can start to build
:Build
REM echo OUTPUT: !output_filename!
REM echo COMPILER: !compiler!
REM echo CONFIG: !config!
REM echo SOURCE FILES: !source_files!
REM echo.

set std=
if /I [!compiler:~-2!] NEQ [++] (
	set std=-std=c99
)

set symbols=
if /I [!config!]==[debug] (
	set symbols=-g
)

set optimisation=
if /I [!config!]==[release] (
	set optimisation=-O3
)

set defines=-D_CRT_SECURE_NO_WARNINGS

if /I [!config!]==[debug] (
	set defines=!defines! -D_DEBUG
)

if /I [!config!]==[release] (
	set defines=!defines! -DNDEBUG
)

set build_dir=bin\\win64\\!compiler!\\!config!\\demos

if not exist %build_dir% (
	mkdir %build_dir%
)

set warninglevels=""
if [!compiler!]==[clang] (
	set warninglevels=-Werror -Wall -Wextra -Weverything -Wpedantic
) else (
	set warninglevels=-Werror -Wall -Wextra -Wpedantic
)

set ignorewarnings=
if [!compiler!]==[clang] (
	set ignorewarnings=-Wno-newline-eof
)

pushd %cwd%
pushd ..

REM echo !compiler! -std=c99 -o %build_dir%\\!output_filename! !symbols! !optimisation! !defines! %warninglevels% !ignorewarnings! !source_files!
!compiler! !std! -o %build_dir%\\!output_filename! !symbols! !optimisation! !defines! %warninglevels% !ignorewarnings! !source_files!

popd
popd

goto :EOF


:ShowUsage
echo Usage:
echo.
echo %~nx0 --output ^<filename^> --compiler [clang^|clang++^|gcc^|g++] --config [debug^|release] --source ^<source files^>
echo.
echo Arguments:
echo     [-h^|--help] (optional):
echo         Shows this help and then exits.
echo.
echo     --output ^<exe^> (required):
echo         The name of the output binary.
echo.
echo     --compiler [clang^|clang++^|gcc^|g++] (required):
echo         Which compiler you want to use.  MUST be one of the ones in the argument list.
echo.
echo     --config [debug^|release] (required):
echo         MUST be either \"debug\" or \"release\".  If debug is used then compiles with symbols and without optimisations.  If release is used compiles vice-versa.
echo.
echo     --source ^<source files^> (required):
echo         All the source files you want to build.
echo         THIS ARGUMENT MUST COME LAST.
echo.
goto :EOF