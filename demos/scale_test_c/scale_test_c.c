#include "tantrum_scale_test.h"
#include "vector2d.h"
#include "vector2d_tests.c"

//#ifdef TANTRUM_TESTS_ENABLED
int main( int argc, char** argv ){
	TANTRUM_SETUP();
	return TANTRUM_RUN_ALL_TESTS_WITH_ARGS( argc, argv );
}
//#else
//int main( int argc, char** argv ){
//	// Your production code goes here
//}
//#endif //TANTRUM_TESTS_ENABLED