#include <Windows.h>

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/*
DM: I'm not happy with the fact that TANTRUM_TEST and TANTRUM_SUITE_TEST is duplicated
I also don't think the current setup will work for when trying to filter by suite because "suiteless" tests have no suite string to check against
I think it might be better to remove testInfo_t entirely and replace it with suiteTestInfo_t
that would get rid of the WET code and suiteless tests could just have suiteNameStr set to NULL - which would still work for filtering suites
I've written an example of this inside filtering.c
*/

//================================================================

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
	TANTRUM_TEST_DEPRECATED
} tantrumTestFlag_t;

typedef struct testInfo_t {
	tantrumTestFlag_t	testingFlag;
	tantrumTestResult_t	testResults;
	const char*			testNameStr;
} testInfo_t;

typedef struct suiteTestInfo_t {
	tantrumTestFlag_t	testingFlag;
	tantrumTestResult_t	testResults;
	const char*			testNameStr;
	const char*			suiteNameStr;
} suiteTestInfo_t;

typedef testInfo_t ( *testFunc_t )( void );

#define TANTRUM_CONCAT_INTERNAL_( a, b )	a ## b
#define TANTRUM_CONCAT_INTERNAL( a, b )		TANTRUM_CONCAT_INTERNAL_( a, b )

#define TANTRUM_TEST( testName, runFlag ) \
	tantrumTestResult_t ( testName )( void ); \
\
	typedef struct TANTRUM_CONCAT_INTERNAL( testName, _testInfo ) { \
		testInfo_t testInformation; \
	} TANTRUM_CONCAT_INTERNAL( testName, _testInfo ); \
\
	static TANTRUM_CONCAT_INTERNAL( testName, _testInfo ) TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ); \
\
	__declspec( dllexport ) testInfo_t TANTRUM_CONCAT_INTERNAL( tantrum_test_invoker_, __COUNTER__ )( void ) { \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testNameStr = #testName; \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testingFlag = runFlag; \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testResults = TANTRUM_TEST_RESULT_DODGED; \
		if ( runFlag == TANTRUM_TEST_SHOULD_RUN ) { \
			TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testResults = ( testName )(); \
		} \
		return TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation; \
	} \
	tantrumTestResult_t ( testName )( void )

#define TANTRUM_SUITE_TEST( suiteName, testName, runFlag ) \
	tantrumTestResult_t ( testName )( void ); \
\
	typedef struct TANTRUM_CONCAT_INTERNAL( testName, _suiteTestInfo ) { \
		suiteTestInfo_t testInformation; \
	} TANTRUM_CONCAT_INTERNAL( testName, _suiteTestInfo ); \
\
	static TANTRUM_CONCAT_INTERNAL( testName, _suiteTestInfo ) TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ); \
\
	__declspec( dllexport ) suiteTestInfo_t TANTRUM_CONCAT_INTERNAL( tantrum_test_invoker_, __COUNTER__ )( void ) { \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.suiteNameStr = #suiteName; \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testNameStr = #testName; \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testingFlag = runFlag; \
		TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testResults = TANTRUM_TEST_RESULT_DODGED; \
		if ( runFlag == TANTRUM_TEST_SHOULD_RUN ) { \
			TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation.testResults = ( testName )(); \
		} \
		return TANTRUM_CONCAT_INTERNAL( testName, GlobalInfo ).testInformation; \
	} \
	tantrumTestResult_t ( testName )( void )

//================================================================


TANTRUM_TEST( OrderingBeer, TANTRUM_TEST_SHOULD_RUN )
{
	return TANTRUM_TEST_RESULT_SUCCESS;
}

TANTRUM_TEST( ReOrderingBeer, TANTRUM_TEST_SHOULD_RUN )
{
	return TANTRUM_TEST_RESULT_FAIL;
}

TANTRUM_TEST( ReReOrderingBeer, TANTRUM_TEST_DEPRECATED )
{
	return TANTRUM_TEST_RESULT_SUCCESS;
}

TANTRUM_TEST( TableFlippingForBeer, TANTRUM_TEST_SHOULD_SKIP )
{
	return TANTRUM_TEST_RESULT_SUCCESS;
}

TANTRUM_SUITE_TEST( MySuite, DansSuiteTest, TANTRUM_TEST_SHOULD_RUN ) {
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

			testInfo_t information = testFunc();

			switch ( information.testResults ) {
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