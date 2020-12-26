#include "../temper.h"

#include <stdio.h>

TEMPER_SUITE_EXTERN( TheSuite );

static void OnSuiteStarting( void* data ) {
	( (void) data );

	printf( "About to run a test suite.\n" );
}

static void OnSuiteEnded( void* data ) {
	( (void) data );

	printf( "Test suite finished.\n" );
}

static void OnTestStarting( void* data ) {
	( (void) data );

	printf( "Test starting.\n" );
}

static void OnTestEnded( void* data ) {
	( (void) data );

	printf( "Test finished.\n" );
}

TEMPER_DEFS();

int main( int argc, char** argv ) {
	TEMPER_SET_COMMAND_LINE_ARGS( argc, argv );

	TEMPER_SET_SUITE_START_CALLBACK( OnSuiteStarting, NULL );
	TEMPER_SET_SUITE_END_CALLBACK( OnSuiteEnded, NULL );

	TEMPER_SET_TEST_START_CALLBACK( OnTestStarting, NULL );
	TEMPER_SET_TEST_END_CALLBACK( OnTestEnded, NULL );

	TEMPER_RUN_SUITE( TheSuite );

	TEMPER_SHOW_STATS();

	return TEMPER_EXIT_CODE();
}
