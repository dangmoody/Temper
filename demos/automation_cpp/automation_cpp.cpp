#define TEMPER_IMPLEMENTATION
#include "../../temper.h"

#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"

//----------------------------------------------------------

TEMPER_TEST( Placeholder, TEMPER_FLAG_SHOULD_RUN ) {
	TEMPER_CHECK_TRUE_M(true, "C++ doesn't work!");
}

//----------------------------------------------------------

int main( int argc, char** argv ) {
	TEMPER_RUN( argc, argv );
	int exitCode = TEMPER_GET_EXIT_CODE();
	printf( "\nAutomation returned: %d.\n", exitCode );
	return exitCode;
}

//----------------------------------------------------------