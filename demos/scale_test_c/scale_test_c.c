#include "../../temper.h"

#include "vector2d.h"
#include "vector2d_tests.c"

//#ifdef TEMPER_TESTS_ENABLED
int main( int argc, char** argv ) {
	TEMPER_RUN_WITH_ARGS( argc, argv );
	int returnValue = TEMPER_GET_EXIT_CODE();
	getchar();
	return returnValue;
}
//#else
//int main( int argc, char** argv ){
//  Your production code goes here
//}
//#endif //TEMPER_TESTS_ENABLED
