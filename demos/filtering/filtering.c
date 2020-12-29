#include <Windows.h>

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/*
DM: you need to run this demo with command line arguments to see filtering working:

	-s <suite name> to only run suites with that name
	-t <test name> to only run tests with that name

you can also combine both of them to only run a specific test in a specific suite

this is also the best I can do for unifying TANTRUM_TEST() and TANTRUM_SUITE_TEST() right now

I'm not so sure I like the unification of tests and "suite tests" because the NULL suite name string has added a lot of extra branching
*/

//================================================================

#if defined( __GNUC__ ) || defined( __clang__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#pragma GCC diagnostic ignored "-Wcomment"
#endif

static const char* TantrumGetNextArgInternal( const int argIndex, const int argc, char** argv ) {
	assert( argc );
	assert( argv );

	return ( argIndex + 1 < argc ) ? argv[argIndex + 1] : NULL;
}

typedef enum tantrumTestResult_t {
	TANTRUM_TEST_RESULT_FAIL	= 0,
	TANTRUM_TEST_RESULT_SUCCESS,
	TANTRUM_TEST_RESULT_DODGED
} tantrumTestResult_t;

typedef enum tantrumTestFlag_t {
	TANTRUM_TEST_SHOULD_RUN		= 0,
	TANTRUM_TEST_SHOULD_SKIP,
	TANTRUM_TEST_DEPRECATED
} tantrumTestFlag_t;

typedef struct suiteTestInfo_t suiteTestInfo_t;

typedef suiteTestInfo_t ( *testInvoker_t )( void );
typedef tantrumTestResult_t ( *testCallback_t )( void );

typedef struct suiteTestInfo_t {
	testCallback_t		callback;
	tantrumTestFlag_t	testingFlag;
	tantrumTestResult_t	testResults;
	const char*			testNameStr;
	const char*			suiteNameStr;
} suiteTestInfo_t;

#define TANTRUM_CONCAT_INTERNAL_( a, b )	a ## b
#define TANTRUM_CONCAT_INTERNAL( a, b )		TANTRUM_CONCAT_INTERNAL_( a, b )

#define TANTRUM_DEFINE_TEST_INTERNAL( suiteName, suiteNameString, testName, runFlag ) \
	tantrumTestResult_t ( testName )( void ); \
\
	typedef struct TANTRUM_CONCAT_INTERNAL( testName, _testInfo ) { \
		suiteTestInfo_t testInformation; \
	} TANTRUM_CONCAT_INTERNAL( testName, _testInfo ); \
\
	static TANTRUM_CONCAT_INTERNAL( testName, _testInfo ) TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ); \
\
	__declspec( dllexport ) suiteTestInfo_t TANTRUM_CONCAT_INTERNAL( tantrum_test_invoker_, __COUNTER__ )( void ) { \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.callback = testName; \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.suiteNameStr = suiteNameString; \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testNameStr = #testName; \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testingFlag = runFlag; \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testResults = TANTRUM_TEST_RESULT_DODGED; \
		return TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation; \
	} \
	tantrumTestResult_t ( testName )( void )

#define TANTRUM_TEST( testName, runFlag ) \
	TANTRUM_DEFINE_TEST_INTERNAL( suiteName, NULL, testName, runFlag )

#define TANTRUM_SUITE_TEST( suiteName, testName, runFlag ) \
	TANTRUM_DEFINE_TEST_INTERNAL( suiteName, #suiteName, testName, runFlag )

//================================================================


TANTRUM_TEST( OrderingBeer, TANTRUM_TEST_SHOULD_RUN ) {
	return TANTRUM_TEST_RESULT_SUCCESS;
}

TANTRUM_TEST( ReOrderingBeer, TANTRUM_TEST_SHOULD_RUN ) {
	return TANTRUM_TEST_RESULT_FAIL;
}

TANTRUM_TEST( ReReOrderingBeer, TANTRUM_TEST_DEPRECATED ) {
	return TANTRUM_TEST_RESULT_SUCCESS;
}

TANTRUM_TEST( TableFlippingForBeer, TANTRUM_TEST_SHOULD_SKIP ) {
	return TANTRUM_TEST_RESULT_SUCCESS;
}

TANTRUM_SUITE_TEST( MySuite, DansSuiteTest, TANTRUM_TEST_SHOULD_RUN ) {
	return TANTRUM_TEST_RESULT_SUCCESS;
}

TANTRUM_SUITE_TEST( MySuite, DansSuiteTest2, TANTRUM_TEST_SHOULD_RUN ) {
	return TANTRUM_TEST_RESULT_SUCCESS;
}

int main( int argc, char** argv ) {
	( (void) argc );

	// TODO(DM): add a global tantrumTestContext_t like Temper 1.0 has and put these two string vars in it
	// force both to NULL to run all the tests
	const char* suiteFilter = NULL;
	const char* testFilter = NULL;

	// parse command line args
	for ( int argIndex = 0; argIndex < argc; argIndex++ ) {
		const char* arg = argv[argIndex];

		if ( strcmp( arg, "-s" ) == 0 ) {
			const char* nextArg = TantrumGetNextArgInternal( argIndex, argc, argv );
			// TODO(DM): if nextArg == NULL then error that the suite filter wasnt set and show usage to help user
			suiteFilter = nextArg;

			continue;
		}

		if ( strcmp( arg, "-t" ) == 0 ) {
			const char* nextArg = TantrumGetNextArgInternal( argIndex, argc, argv );
			// TODO(DM): if nextArg == NULL then error that the test filter wasnt set and show usage to help user
			testFilter = nextArg;

			continue;
		}
	}

	{
		HANDLE handle = LoadLibrary( argv[0] );
		assert( handle );

		// DM: yeah yeah yeah, I know: fixed-length string arrays bad
		// I'll write a tprintf at some point
		char testFuncNames[1024];
		testInvoker_t testFunc = NULL;

		for ( uint32_t i = 0; i < __COUNTER__; i++ ) {
			snprintf( testFuncNames, 1024, "tantrum_test_invoker_%d", i );
			testFunc = (testInvoker_t) GetProcAddress( handle, testFuncNames );
			assert( testFunc );

			suiteTestInfo_t information = testFunc();

			bool isFilteredSuite = suiteFilter && information.suiteNameStr && strcmp( information.suiteNameStr, suiteFilter ) == 0;

			if ( isFilteredSuite || !suiteFilter ) {
				bool isFilteredTest = testFilter && strcmp( information.testNameStr, testFilter ) == 0;

				if ( isFilteredTest || !testFilter ) {
					// DM: given this is now where information.testResults gets set, we can maybe remove that member?
					information.testResults = information.callback();

					if ( information.suiteNameStr ) {
						printf( "%s: ", information.suiteNameStr );
					}

					switch ( information.testResults ) {
						case TANTRUM_TEST_RESULT_FAIL:
							printf( "%s - FAILED\n", information.testNameStr );
							break;

						case TANTRUM_TEST_RESULT_SUCCESS:
							printf( "%s - SUCCEEDED\n", information.testNameStr );
							break;

						case TANTRUM_TEST_RESULT_DODGED:
							printf( "%s - NOT_EXECUTED\n", information.testNameStr );
							break;
					}
				}
			}
		}

		FreeLibrary( handle );
		handle = NULL;
	}

	getchar();

	return 0;
}

#if defined( __GNUC__ ) || defined( __clang__ )
#pragma GCC diagnostic pop
#endif