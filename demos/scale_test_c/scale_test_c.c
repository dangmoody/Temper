#include "../../tantrum.h"

#include "vector2d.h"
#include "vector2d_tests.c"

//#ifdef TANTRUM_TESTS_ENABLED

int main( int argc, char** argv ){
	TANTRUM_SETUP();
	int returnValue = TANTRUM_RUN_ALL_TESTS_WITH_ARGS( argc, argv );
	//getchar();
	return returnValue;
}

//#else

//int main( int argc, char** argv ){
//	// Your production code goes here
//}
//#endif //TANTRUM_TESTS_ENABLED