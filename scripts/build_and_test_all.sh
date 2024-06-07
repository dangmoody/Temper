#!/bin/bash

set -e

printf "======= Clang / Debug =======\n"
source scripts/build_clang_gcc.sh --output automation_c.exe --compiler clang --config debug --source tests/automation_c/automation_c.c
./bin/linux/clang/debug/tests/automation_c.exe
printf "======= Clang / Debug Done =======\n"

printf "======= Clang / Release =======\n"
source scripts/build_clang_gcc.sh --output automation_c.exe --compiler clang --config release --source tests/automation_c/automation_c.c
./bin/linux/clang/release/tests/automation_c.exe
printf "======= Clang / Release Done =======\n"


printf "======= Clang++ / Debug =======\n"
source scripts/build_clang_gcc.sh --output automation_cpp.exe --compiler clang++ --config debug --source tests/automation_cpp/automation_cpp.cpp
./bin/linux/clang++/debug/tests/automation_cpp.exe
printf "======= Clang++ / Debug Done =======\n"

printf "======= Clang++ / Release =======\n"
source scripts/build_clang_gcc.sh --output automation_cpp.exe --compiler clang++ --config release --source tests/automation_cpp/automation_cpp.cpp
./bin/linux/clang++/release/tests/automation_cpp.exe
printf "======= Clang++ / Release Done =======\n"


printf "======= GCC / Debug =======\n"
source scripts/build_clang_gcc.sh --output automation_c.exe --compiler gcc --config debug --source tests/automation_c/automation_c.c
./bin/linux/gcc/debug/tests/automation_c.exe
printf "======= GCC / Debug Done =======\n"

printf "======= GCC / Release =======\n"
source scripts/build_clang_gcc.sh --output automation_c.exe --compiler gcc --config release --source tests/automation_c/automation_c.c
./bin/linux/gcc/release/tests/automation_c.exe
printf "======= GCC / Release Done =======\n"


printf "======= G++ / Debug =======\n"
source scripts/build_clang_gcc.sh --output automation_cpp.exe --compiler g++ --config debug --source tests/automation_cpp/automation_cpp.cpp
./bin/linux/g++/debug/tests/automation_cpp.exe
printf "======= G++ / Debug Done =======\n"

printf "======= G++ / Release =======\n"
source scripts/build_clang_gcc.sh --output automation_cpp.exe --compiler g++ --config release --source tests/automation_cpp/automation_cpp.cpp
./bin/linux/g++/release/tests/automation_cpp.exe
printf "======= G++ / Release Done =======\n"

exit 0