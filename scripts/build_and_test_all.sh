#!/bin/bash

set -e

printf "======= Clang / Debug =======\n"
~/builder/bin/builder build_clang.cpp --config=automation-c-debug
./bin/debug/clang/automation_c_clang
printf "======= Clang / Debug Done =======\n"

printf "======= Clang / Release =======\n"
~/builder/bin/builder build_clang.cpp --config=automation-c-release
./bin/release/clang/automation_c_clang
printf "======= Clang / Release Done =======\n"


printf "======= Clang++ / Debug =======\n"
~/builder/bin/builder build_clang.cpp --config=automation-cpp-debug
./bin/debug/clang/automation_cpp_clang
printf "======= Clang++ / Debug Done =======\n"

printf "======= Clang++ / Release =======\n"
~/builder/bin/builder build_clang.cpp --config=automation-cpp-release
./bin/release/clang/automation_cpp_clang
printf "======= Clang++ / Release Done =======\n"


printf "======= GCC / Debug =======\n"
~/builder/bin/builder build_gcc.cpp --config=automation-c-debug
./bin/debug/gcc/automation_c_gcc
printf "======= GCC / Debug Done =======\n"

printf "======= GCC / Release =======\n"
~/builder/bin/builder build_gcc.cpp --config=automation-c-release
./bin/release/gcc/automation_c_gcc
printf "======= GCC / Release Done =======\n"


printf "======= G++ / Debug =======\n"
~/builder/bin/builder build_gcc.cpp --config=automation-cpp-debug
./bin/debug/gcc/automation_cpp_gcc
printf "======= G++ / Debug Done =======\n"

printf "======= G++ / Release =======\n"
~/builder/bin/builder build_gcc.cpp --config=automation-cpp-release
./bin/release/gcc/automation_cpp_gcc
printf "======= G++ / Release Done =======\n"

echo No errors were detected.  Everything looks fine.

exit 0