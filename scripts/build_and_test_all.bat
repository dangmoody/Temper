@echo off

setlocal EnableDelayedExpansion

pushd %~dp0
pushd ..

echo ======= Clang / Debug =======
builder build.cpp --config=automation-c
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\debug\\clang\\automation_c_clang.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= Clang / Debug Done =======
echo.

echo ======= Clang / Release =======
builder build.cpp --config=automation-c --release
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\release\\clang\\automation_c_clang.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= Clang / Release Done =======
echo.


echo ======= Clang++ / Debug =======
builder build.cpp --config=automation-cpp
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\debug\\clang\\automation_cpp_clang.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= Clang++ / Debug Done =======
echo.

echo ======= Clang++ / Release =======
builder build.cpp --config=automation-cpp --release
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\release\\clang\\automation_cpp_clang.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= Clang++ / Release Done =======
echo.


echo ======= GCC / Debug =======
builder build.cpp --config=automation-c
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\debug\\gcc\\automation_c_gcc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= GCC / Debug Done =======
echo.

echo ======= GCC / Release =======
builder build.cpp --config=automation-c --release
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\release\\gcc\\automation_c_gcc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= GCC / Release Done =======
echo.


echo ======= G++ / Debug =======
builder build.cpp --config=automation-cpp
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\debug\\gcc\\automation_cpp_gcc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= G++ / Debug Done =======
echo.

echo ======= G++ / Release =======
builder build.cpp --config=automation-cpp --release
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\release\\gcc\\automation_cpp_gcc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= G++ / Release Done =======
echo.


echo ======= MSVC (C) / Debug =======
builder build.cpp --config=automation-c
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\debug\\msvc\\automation_c_msvc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= MSVC (C) / Debug Done =======
echo.

echo ======= MSVC (C) / Release =======
builder build.cpp --config=automation-c --release
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\release\\msvc\\automation_c_msvc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= MSVC (C) / Release Done =======
echo.


echo ======= MSVC (C++) / Debug =======
builder build.cpp --config=automation-cpp
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\debug\\msvc\\automation_cpp_msvc.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= MSVC (C++) / Debug Done =======
echo.

echo ======= MSVC (C++) / Release =======
builder build.cpp --config=automation-cpp --release
if %errorlevel% neq 0 goto :ExitFailure

.\\bin\\release\\msvc\\automation_cpp_msvc.exe
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
