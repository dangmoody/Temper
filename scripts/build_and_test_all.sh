#!/bin/bash

set -e

cd "$(dirname "$0")/.."

printf "======= Clang / Debug =======\n"
./build --config=automation-c
./bin/debug/automation_c_clang
printf "======= Clang / Debug Done =======\n"

printf "======= Clang / Release =======\n"
./build --config=automation-c --release
./bin/release/automation_c_clang
printf "======= Clang / Release Done =======\n"


printf "======= Clang++ / Debug =======\n"
./build --config=automation-cpp
./bin/debug/automation_cpp_clang
printf "======= Clang++ / Debug Done =======\n"

printf "======= Clang++ / Release =======\n"
./build --config=automation-cpp --release
./bin/release/automation_cpp_clang
printf "======= Clang++ / Release Done =======\n"


printf "======= GCC / Debug =======\n"
./build --config=automation-c --gcc
./bin/debug/automation_c_gcc
printf "======= GCC / Debug Done =======\n"

printf "======= GCC / Release =======\n"
./build --config=automation-c --gcc --release
./bin/release/automation_c_gcc
printf "======= GCC / Release Done =======\n"


printf "======= G++ / Debug =======\n"
./build --config=automation-cpp --gcc
./bin/debug/automation_cpp_gcc
printf "======= G++ / Debug Done =======\n"

printf "======= G++ / Release =======\n"
./build --config=automation-cpp --gcc --release
./bin/release/automation_cpp_gcc
printf "======= G++ / Release Done =======\n"

echo No errors were detected.  Everything looks fine.

exit 0