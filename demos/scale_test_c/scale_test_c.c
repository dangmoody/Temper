#include "tantrum_scale_test.h"
#include "vector2d.h"
#include "vector2D_tests.c"

#if defined( __GNUC__ ) || defined( __clang__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#endif

//#ifdef TANTRUM_TESTS_ENABLED
int main( int argc, char** argv )
{
	TANTRUM_SETUP();

	return TantrumExecuteAllTestsWithArguments( argc, argv );
}
//#else
// int main( int argc, char** argv )
// {
//		// production code goes here
// }
//#endif //TANTRUM_TESTS_ENABLED

#if defined( __GNUC__ ) || defined( __clang__ )
#pragma GCC diagnostic pop
#endif