// DM: using this as temporary hacky work-around to test that temper does in fact compile in C++
// clang++ and g++ expect a "C++ input" (by which they mean a compilation unit to end in .cpp or the like)
// so we have this file just include the C file and it can't tell the difference
// all it cares about is the file extension and thats it
// so dont delete this file

#include "scale_test_c.c"
