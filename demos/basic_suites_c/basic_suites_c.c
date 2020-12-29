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
	TANTRUM_TEST_RESULT_DODGED
} tantrumTestResult_t;

typedef enum tantrumTestFlag_t {
	TANTRUM_TEST_SHOULD_RUN		= 0,
	TANTRUM_TEST_SHOULD_SKIP,
	TANTRUM_TEST_DEPRICATED
} tantrumTestFlag_t;

typedef struct testInfo {
	tantrumTestResult_t	testingFlag;
	tantrumTestResult_t	testResults;
	const char*			testNameStr;
} testInfo;

typedef struct suiteTestInfo {
	tantrumTestResult_t	testingFlag;
	tantrumTestResult_t	testResults;
	const char*			testNameStr;
	const char*			testSuiteNameStr;
} suiteTestInfo;

typedef testInfo( *testFunc_t )( void );

#define TANTRUM_CONCAT_INTERNAL_( a, b )	a ## b
#define TANTRUM_CONCAT_INTERNAL( a, b )		TANTRUM_CONCAT_INTERNAL_( a, b )

#define TANTRUM_TEST( testName, runFlag ) \
	tantrumTestResult_t ( testName )( void ); \
\
	typedef struct TANTRUM_CONCAT_INTERNAL( testName, _testInfo ) { \
		testInfo testInformation; \
	} TANTRUM_CONCAT_INTERNAL( testName, _testInfo ); \
\
	static TANTRUM_CONCAT_INTERNAL( testName, _testInfo ) TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ); \
\
	__declspec( dllexport ) testInfo TANTRUM_CONCAT_INTERNAL( tantrum_test_invoker_, __COUNTER__ )( void ) { \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testNameStr = #testName; \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testingFlag = (int) runFlag; \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testResults = TANTRUM_TEST_RESULT_DODGED; \
		if (runFlag == 0) { \
			TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testResults = ( testName )(); \
		} \
		return TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation; \
	} \
	tantrumTestResult_t ( testName )( void )

TANTRUM_TEST( OrderingBeer, TANTRUM_TEST_SHOULD_RUN )
{
	return TANTRUM_TEST_RESULT_SUCCESS;
}

TANTRUM_TEST( ReOrderingBeer, TANTRUM_TEST_SHOULD_RUN )
{
	return TANTRUM_TEST_RESULT_FAIL;
}

TANTRUM_TEST( ReReOrderingBeer, TANTRUM_TEST_DEPRICATED )
{
	return TANTRUM_TEST_RESULT_SUCCESS;
}

TANTRUM_TEST( TableFlippingForBeer, TANTRUM_TEST_SHOULD_SKIP )
{
	return TANTRUM_TEST_RESULT_SUCCESS;
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

			testInfo information = testFunc();
			switch( information.testResults ) {
				case TANTRUM_TEST_RESULT_FAIL:
					printf( "TestName: %s - FAILED\n", information.testNameStr );
					break;

				case TANTRUM_TEST_RESULT_SUCCESS:
					printf( "TestName: %s - SUCCEEDED\n", information.testNameStr );
					break;

				case TANTRUM_TEST_RESULT_DODGED:
					printf( "TestName: %s - NOT_EXECUTED\n", information.testNameStr );
					break;
			}
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