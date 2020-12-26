@echo off

setlocal EnableDelayedExpansion

set cpp=%1
if [%cpp%]==[] (
	echo ERROR: Language not set.
	goto :bail
)

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

pushd %~dp0

set examplesdir="..\\examples"

pushd %examplesdir%

if not exist build mkdir build
if not exist build\\intermediate mkdir build\\intermediate

if /I [%cpp%]==[cpp] (
	echo.
	echo Building C++ samples:
	cl.exe /Fo"build/intermediate/" /EHsc example_cpp.cpp sample_suite_cpp.cpp /D_CRT_SECURE_NO_WARNINGS /link /OUT:build/example_cpp_msvc.exe /PDB:build/

	echo.
	echo Running C++ samples:
	echo.
	echo Example CPP MSVC:
	build\\example_cpp_msvc.exe
	echo.
) else (
	echo.
	echo building C samples:
	cl.exe /Fo"build/intermediate/" /EHsc ../examples/example_basic.c /D_CRT_SECURE_NO_WARNINGS /link /OUT:build/example_basic_msvc.exe /PDB:build/
	cl.exe /Fo"build/intermediate/" /EHsc ../examples/example_suite.c ../examples/sample_suite.c /D_CRT_SECURE_NO_WARNINGS /link /OUT:build/example_suite_msvc.exe /PDB:build/

	echo.
	echo Running C samples:
	echo.
	echo Example basic MSVC:
	build\\example_basic_msvc.exe
	echo.

	echo Example suite MSVC:
	build\\example_suite_msvc.exe
)

popd
popd

goto :EOF


:bail
echo Usage:
echo     build_msvc.bat ^<language^>
echo.
echo Arguments:
echo     ^<language^> (required):
echo         Which language you want to build the tests in.  Must be either "c" or "cpp" (without speechmarks).

goto :EOF