#include "../../temper.h"

#include "vector2d.h"
#include "vector2d_tests.c"

//#ifdef TEMPER_TESTS_ENABLED

int main( int argc, char** argv ){
	TEMPER_SETUP();
	int returnValue = TEMPER_RUN_ALL_TESTS_WITH_ARGS( argc, argv );
	//getchar();
	return returnValue;
}

//#else

//int main( int argc, char** argv ){
//	// Your production code goes here
//}
//#endif //TEMPER_TESTS_ENABLED
