@echo off

setlocal EnableDelayedExpansion

pushd %~dp0
pushd ..

echo ======= Clang / Debug =======
build.exe --config=automation-c
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\debug\\automation_c_clang.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= Clang / Debug Done =======
echo.

echo ======= Clang / Release =======
build.exe --config=automation-c --release
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\release\\automation_c_clang.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= Clang / Release Done =======
echo.


echo ======= Clang++ / Debug =======
build.exe --config=automation-cpp
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\debug\\automation_cpp_clang.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= Clang++ / Debug Done =======
echo.

echo ======= Clang++ / Release =======
build.exe --config=automation-cpp --release
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\release\\automation_cpp_clang.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= Clang++ / Release Done =======
echo.


echo ======= GCC / Debug =======
build.exe --config=automation-c --gcc
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\debug\\automation_c_gcc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= GCC / Debug Done =======
echo.

echo ======= GCC / Release =======
build.exe --config=automation-c --gcc --release
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\release\\automation_c_gcc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= GCC / Release Done =======
echo.


echo ======= G++ / Debug =======
build.exe --config=automation-cpp --gcc
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\debug\\automation_cpp_gcc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= G++ / Debug Done =======
echo.

echo ======= G++ / Release =======
build.exe --config=automation-cpp --gcc --release
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\release\\automation_cpp_gcc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= G++ / Release Done =======
echo.


echo ======= MSVC (C) / Debug =======
build.exe --config=automation-c --msvc
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\debug\\automation_c_msvc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= MSVC (C) / Debug Done =======
echo.

echo ======= MSVC (C) / Release =======
build.exe --config=automation-c --msvc --release
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\release\\automation_c_msvc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= MSVC (C) / Release Done =======
echo.


echo ======= MSVC (C++) / Debug =======
build.exe --config=automation-cpp --msvc
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\debug\\automation_cpp_msvc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= MSVC (C++) / Debug Done =======
echo.

echo ======= MSVC (C++) / Release =======
build.exe --config=automation-cpp --msvc --release
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\release\\automation_cpp_msvc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= MSVC (C++) / Release Done =======
echo.

goto :ExitSuccess


:ExitSuccess
echo No errors were detected.  Everything looks fine.
popd
popd
goto :EOF

:ExitFailure
echo ERROR: Last operation was not successful.  Stopping...
popd
popd
exit /b %errorlevel%
