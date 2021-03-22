@echo off

setlocal EnableDelayedExpansion

pushd %~dp0

echo ======= Clang / Debug =======
call build_clang_gcc.bat --output automation_c.exe --compiler clang --config debug --source demos\\automation_c\\automation_c.c
if %errorlevel% neq 0 goto :ExitFailure

..\\bin\\win64\\clang\\debug\\demos\\automation_c.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= Clang / Debug Done =======
echo.

echo ======= Clang / Release =======
call build_clang_gcc.bat --output automation_c.exe --compiler clang --config release --source demos\\automation_c\\automation_c.c
if %errorlevel% neq 0 goto :ExitFailure

..\\bin\\win64\\clang\\release\\demos\\automation_c.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= Clang / Release Done =======
echo.


echo ======= Clang++ / Debug =======
call build_clang_gcc.bat --output automation_cpp.exe --compiler clang++ --config debug --source demos\\automation_cpp\\automation_cpp.cpp
if %errorlevel% neq 0 goto :ExitFailure

..\\bin\\win64\\clang++\\debug\\demos\\automation_cpp.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= Clang++ / Debug Done =======
echo.

echo ======= Clang++ / Release =======
call build_clang_gcc.bat --output automation_cpp.exe --compiler clang++ --config release --source demos\\automation_cpp\\automation_cpp.cpp
if %errorlevel% neq 0 goto :ExitFailure

..\\bin\\win64\\clang++\\release\\demos\\automation_cpp.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= Clang++ / Release Done =======
echo.


echo ======= GCC / Debug =======
call build_clang_gcc.bat --output automation_c.exe --compiler gcc --config debug --source demos\\automation_c\\automation_c.c
if %errorlevel% neq 0 goto :ExitFailure

..\\bin\\win64\\gcc\\debug\\demos\\automation_c.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= GCC / Debug Done =======
echo.

echo ======= GCC / Release =======
call build_clang_gcc.bat --output automation_c.exe --compiler gcc --config release --source demos\\automation_c\\automation_c.c
if %errorlevel% neq 0 goto :ExitFailure

..\\bin\\win64\\gcc\\release\\demos\\automation_c.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= GCC / Release Done =======
echo.


echo ======= G++ / Debug =======
call build_clang_gcc.bat --output automation_cpp.exe --compiler g++ --config debug --source demos\\automation_cpp\\automation_cpp.cpp
if %errorlevel% neq 0 goto :ExitFailure

..\\bin\\win64\\g++\\debug\\demos\\automation_cpp.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= G++ / Debug Done =======
echo.

echo ======= G++ / Release =======
call build_clang_gcc.bat --output automation_cpp.exe --compiler g++ --config release --source demos\\automation_cpp\\automation_cpp.cpp
if %errorlevel% neq 0 goto :ExitFailure

..\\bin\\win64\\g++\\release\\demos\\automation_cpp.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= G++ / Release Done =======
echo.


echo ======= MSVC (C) / Debug =======
call build_msvc.bat --output automation_c.exe --config debug --source demos\\automation_c\\automation_c.c
if %errorlevel% neq 0 goto :ExitFailure

..\\bin\\win64\\msvc\\debug\\demos\\automation_c.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= MSVC (C) / Debug Done =======
echo.

echo ======= MSVC (C) / Release =======
call build_msvc.bat --output automation_c.exe --config release --source demos\\automation_c\\automation_c.c
if %errorlevel% neq 0 goto :ExitFailure

..\\bin\\win64\\msvc\\release\\demos\\automation_c.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= MSVC (C) / Release Done =======
echo.


echo ======= MSVC (C++) / Debug =======
call build_msvc.bat --output automation_cpp.exe --config debug --source demos\\automation_cpp\\automation_cpp.cpp
if %errorlevel% neq 0 goto :ExitFailure

..\\bin\\win64\\msvc\\debug\\demos\\automation_cpp.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= MSVC (C++) / Debug Done =======
echo.

echo ======= MSVC (C++) / Release =======
call build_msvc.bat --output automation_cpp.exe --config release --source demos\\automation_cpp\\automation_cpp.cpp
if %errorlevel% neq 0 goto :ExitFailure

..\\bin\\win64\\msvc\\release\\demos\\automation_cpp.exe
if %errorlevel% neq 0 goto :ExitFailure
echo ======= MSVC (C++) / Release Done =======
echo.

goto :ExitSuccess


:ExitSuccess
echo No errors were detected.  Everything looks fine.
popd
goto :EOF

:ExitFailure
echo ERROR: Last operation was not successful.  Stopping...
popd
exit /b %errorlevel%