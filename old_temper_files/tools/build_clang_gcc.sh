#!/bin/bash

# exit when any command fails
set -e

# if set to "clang" or "gcc" builds the C examples
# if set to "clang++" or "g++" builds the C++ example
g_compiler=$1

do_build () {
	compiler=$1
	output_filename=$2
	source_files="${@:3}"

	if [[ "${compiler}" == clang* ]]
	then
		compile_options="-Wall -Wextra -Werror -Wpedantic -Weverything -O3 -ffast-math"
	else
		compile_options="-Wall -Wextra -Werror -O3 -ffast-math"
	fi

	if [[ "${compiler}" == *++* ]]
	then
		std=""
	else
		std=-std=c99
	fi

	$compiler ${std} -o build/${output_filename}_${compiler}.exe ${source_files} ${compile_options} ${ignore_warnings}
}

if [ ! -d "build" ]; then
	mkdir build
fi

echo ------- Compiling with: ${g_compiler} -------

if [[ "${g_compiler}" == *++* ]]
then
	do_build ${g_compiler} example_cpp "examples/example_cpp.cpp examples/sample_suite_cpp.cpp"
else
	do_build ${g_compiler} example_basic examples/example_basic.c
	do_build ${g_compiler} example_suite "examples/example_suite.c examples/sample_suite.c"
fi

echo ------- Done -------