#include "tantrum_scale_test.h"
#include "vector2d.h"
#include "vector2d_tests.c"

//#ifdef TANTRUM_TESTS_ENABLED
int main( int argc, char** argv )
{
	TANTRUM_SETUP();

	int returnCode = TantrumExecuteAllTestsWithArguments( argc, argv );
	getchar();
	return returnCode;
}
//#else
// int main( int argc, char** argv )
// {
//		// production code goes here
// }
//#endif //TANTRUM_TESTS_ENABLED