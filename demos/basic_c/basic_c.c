#include <Windows.h>

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/*
DM: this file just contains me hacking something together that solves our primary problem: test auto-registration
everything in this demo file right now is just to show how it _might_ work
there are no guarantees it will look anything like this when I start moving code into tantrum.h for others to play around with
but so far I'm somewhat happy with what I've got here
*/

#if defined( __GNUC__ ) || defined( __clang__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#endif

typedef enum tantrumTestResult_t {
	TANTRUM_TEST_RESULT_FAIL	= 0,
	TANTRUM_TEST_RESULT_SUCCESS,
	TANTRUM_TEST_RESULT_SKIPPED
} tantrumTestResult_t;

typedef tantrumTestResult_t ( *testFunc_t )( void );

#define TANTRUM_CONCAT_INTERNAL_( a, b )	a ## b
#define TANTRUM_CONCAT_INTERNAL( a, b )		TANTRUM_CONCAT_INTERNAL_( a, b )

#define TANTRUM_PASS()						return TANTRUM_TEST_RESULT_SUCCESS

#define TANTRUM_TEST( testName ) \
	tantrumTestResult_t ( testName )( void ); \
	__declspec( dllexport ) void TANTRUM_CONCAT_INTERNAL( tantrum_test_invoker_, __COUNTER__ )( void ) { \
		printf( "%s:\t", #testName ); \
\
		tantrumTestResult_t testResult = ( testName )(); \
\
		switch ( testResult ) { \
			case TANTRUM_TEST_RESULT_FAIL: \
				printf( "FAILED.\n" ); \
				break; \
\
			case TANTRUM_TEST_RESULT_SUCCESS: \
				printf( "OK.\n" ); \
				break; \
\
			case TANTRUM_TEST_RESULT_SKIPPED: \
				printf( "SKIPPED.\n" ); /* TODO: add skipped msg */ \
				break; \
\
		} \
	} \
	tantrumTestResult_t ( testName )( void )

TANTRUM_TEST( OrderingBeer )
{
	TANTRUM_PASS();
}

TANTRUM_TEST( ReOrderingBeer )
{
	TANTRUM_PASS();
}

TANTRUM_TEST( TableFlippingForBeer )
{
	TANTRUM_PASS();
}

int main( int argc, char** argv ) {
	( (void) argc );

	HANDLE handle = LoadLibrary( argv[0] );
	assert( handle );

	{
		// DM: yeah yeah yeah, I know: fixed-length string arrays bad
		// I'll write a tprintf at some point
		char testFuncNames[1024];
		testFunc_t testFunc = NULL;

		for ( uint32_t i = 0; i < __COUNTER__; i++ ) {
			snprintf( testFuncNames, 1024, "tantrum_test_invoker_%d", i );
			testFunc = (testFunc_t) GetProcAddress( handle, testFuncNames );
			assert( testFunc );

			testFunc();
		}
	}

	FreeLibrary( handle );
	handle = NULL;

	getchar();

	return 0;
}

#if defined( __GNUC__ ) || defined( __clang__ )
#pragma GCC diagnostic pop
#endif