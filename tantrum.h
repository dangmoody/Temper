#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#if defined( __GNUC__ ) || defined( __clang__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#endif // defined( __GNUC__ ) || defined( __clang__ )

//==========================================================
// STRUCTS
//==========================================================

typedef uint32_t tantrumBool32;

typedef enum tantrumTestFlag_t {
	TANTRUM_TEST_SHOULD_RUN	= 0,
	TANTRUM_TEST_SHOULD_SKIP,
	TANTRUM_TEST_DEPRECATED
} tantrumTestFlag_t;

//----------------------------------------------------------

typedef void( *testCallback_t )( void );

typedef tantrumBool32 ( *tantrumStringCompareFunc_t )( const char*, const char* );

typedef struct suiteTestInfo_t {
	testCallback_t		callback;
	tantrumTestFlag_t	testingFlag;
	const char*			testNameStr;
	const char*			suiteNameStr;
} suiteTestInfo_t;

typedef suiteTestInfo_t( *testInfoFetcherFunc_t )( void );

//----------------------------------------------------------

typedef struct tantrumTestContext_t {
	uint32_t		testsPassed;
	uint32_t		testsFailed;
	uint32_t		testsDodged;
	uint32_t		totalTestsDeclared; // Gets set in the main function with a preprocessor
	uint32_t		totalTestsFoundWithFilters;
	uint32_t		totalTestsExecuted;
	uint32_t		totalErrorsInCurrentTests;
	tantrumBool32	partialFilter;
	tantrumBool32	isFilteringTests;
	const char*		programName;
	const char*		suiteFilter;
	const char*		testFilter;
} tantrumTestContext_t;

//==========================================================
// GLOBALS
//==========================================================

static tantrumTestContext_t						g_tantrumTestContext;

//==========================================================
// FUNCTIONS - BASE HELPER/UTILITY FUNCTIONS
//==========================================================

static uint32_t TantrumGetPercentInternal( uint32_t yourValue, uint32_t yourMax )
{
	return ( uint32_t ) ( ( ( ( double ) yourValue ) / ( ( double ) yourMax ) ) * 100 );
}

//----------------------------------------------------------

static bool TantrumFloatEqualsInternal( const float a, const float b, const float epsilon ) {
	return fabsf( a - b ) > epsilon;
}

//----------------------------------------------------------

static const char* TantrumGetNextArgInternal( const int argIndex, const int argc, char** argv ) {
	assert( argc );
	assert( argv );

	return ( argIndex + 1 < argc ) ? argv[ argIndex + 1 ] : NULL;
}

//----------------------------------------------------------

static tantrumBool32 TantrumStringEqualsInternal( const char* a, const char* b ) {
	return strcmp( a, b ) == 0;
}

//----------------------------------------------------------

static tantrumBool32 TantrumStringContainsInternal( const char* str, const char* substring ) {
	return strstr( str, substring ) != NULL;
}

//----------------------------------------------------------

static void PrintTestExecutionInformation() {
	printf("=== TANTRUM TESTING REPORT ===\n");

	printf( "Total tests defined: %d\n", g_tantrumTestContext.totalTestsDeclared );
	if( g_tantrumTestContext.isFilteringTests ) {
		printf( "\t- Total tests matching filters: %d\n\t- Suite filter: %s\n\t- Test filter: %s\n\t- Partial results %s\n",
				g_tantrumTestContext.totalTestsFoundWithFilters, 
				g_tantrumTestContext.suiteFilter,
				g_tantrumTestContext.testFilter,
				g_tantrumTestContext.partialFilter ? "PERMITTED" : "DISCARDED" );
	}

	uint32_t totalFound = g_tantrumTestContext.totalTestsFoundWithFilters;
	printf( "Passed: %d ( %d%% )\n", g_tantrumTestContext.testsPassed, TantrumGetPercentInternal( g_tantrumTestContext.testsPassed, totalFound ) );
	printf( "Failed: %d ( %d%% )\n", g_tantrumTestContext.testsFailed, TantrumGetPercentInternal( g_tantrumTestContext.testsFailed, totalFound ) );
	printf( "Dodged: %d ( %d%% )\n", g_tantrumTestContext.testsDodged, TantrumGetPercentInternal( g_tantrumTestContext.testsDodged, totalFound ) );
}

//==========================================================
// PREPROCESSORS - TANTRUM INTERNAL
//==========================================================

#define TANTRUM_DEFAULT_EPSILON					0.00001f

//----------------------------------------------------------

#define TANTRUM_CONCAT_INTERNAL_FINAL( a, b )	a ## b

//----------------------------------------------------------

#define TANTRUM_CONCAT_INTERNAL( a, b )			TANTRUM_CONCAT_INTERNAL_FINAL( a, b )

//----------------------------------------------------------

#define TANTRUM_DEFINE_TEST_INTERNAL( suiteNameString, testName, runFlag ) \
\
	/*1. Create a function with a name matching the test.*/ \
	void ( testName )( void ); \
\
	/*2. Create a testName_TestInfo struct that will just wrap the test information meta data.*/ \
	typedef struct TANTRUM_CONCAT_INTERNAL( testName, _TestInfo ) { \
		suiteTestInfo_t testInformation; \
	} TANTRUM_CONCAT_INTERNAL( testName, _TestInfo ); \
\
	/*3. Create a global instance of this new struct for us to access and write data about this test to.*/ \
	extern TANTRUM_CONCAT_INTERNAL( testName, _TestInfo ) TANTRUM_CONCAT_INTERNAL( testName, _GlobalInfo ); \
	TANTRUM_CONCAT_INTERNAL( testName, _TestInfo ) TANTRUM_CONCAT_INTERNAL( testName, _GlobalInfo ); \
\
	/*4. Create our invoker_n function. This is what the runner will loop over to grab the test function as well as all the information concerning it*/ \
	__declspec( dllexport ) inline suiteTestInfo_t TANTRUM_CONCAT_INTERNAL( tantrum_test_info_fetcher_, __COUNTER__ )( void ) { \
		TANTRUM_CONCAT_INTERNAL( testName, _GlobalInfo ).testInformation.callback = testName; \
		TANTRUM_CONCAT_INTERNAL( testName, _GlobalInfo ).testInformation.suiteNameStr = suiteNameString; \
		TANTRUM_CONCAT_INTERNAL( testName, _GlobalInfo ).testInformation.testNameStr = #testName; \
		TANTRUM_CONCAT_INTERNAL( testName, _GlobalInfo ).testInformation.testingFlag = runFlag; \
		return TANTRUM_CONCAT_INTERNAL( testName, _GlobalInfo ).testInformation; \
	} \
\
	/*5. The test function declared at Step1 is now declared here by the user*/ \
	void ( testName )( void )

//----------------------------------------------------------

#define TANTRUM_TEST( testName, runFlag ) \
	TANTRUM_DEFINE_TEST_INTERNAL( NULL, testName, runFlag )

//----------------------------------------------------------

#define TANTRUM_SUITE_TEST( suiteName, testName, runFlag ) \
	TANTRUM_DEFINE_TEST_INTERNAL( #suiteName, testName, runFlag )

//----------------------------------------------------------

#define TANTRUM_DECLARE_PARAMETRIC_SUITE_TEST_INTERNAL( suiteName, testName, runFlag, ... )\
\
	/*1. Create a function with a name matching the test with the provided parameters.*/\
	void ( testName )( __VA_ARGS__ ); \
\
	/*2. Typedef this function type.*/ \
	typedef void ( *TANTRUM_CONCAT_INTERNAL( testName, _FuncType ) )( __VA_ARGS__ ); \
\
	/*3. Stash this function and run info in a struct unique to this.*/ \
	typedef struct TANTRUM_CONCAT_INTERNAL( testName, _ParametricTestInfo ) { \
		TANTRUM_CONCAT_INTERNAL( testName, _FuncType ) Callback; \
		tantrumTestFlag_t testingFlag; \
		const char* testNameStr; \
		const char* suiteNameStr; \
	} TANTRUM_CONCAT_INTERNAL( testName, _ParametricTestInfo ); \
\
	/*4. Create a global instance of this new struct for us to access and write data about this test to.*/ \
	extern TANTRUM_CONCAT_INTERNAL( testName, _ParametricTestInfo ) TANTRUM_CONCAT_INTERNAL( testName, _GlobalParametricInfo ); \
	TANTRUM_CONCAT_INTERNAL( testName, _ParametricTestInfo ) TANTRUM_CONCAT_INTERNAL( testName, _GlobalParametricInfo ); \
\
	/*5. Define an info binding function to tie all this information into the struct*/ \
	__declspec( dllexport ) inline void (TANTRUM_CONCAT_INTERNAL( testName, _ParametricTestInfoBinder ))(void){ \
		TANTRUM_CONCAT_INTERNAL( testName, _GlobalParametricInfo ).Callback = testName; \
		TANTRUM_CONCAT_INTERNAL( testName, _GlobalParametricInfo ).testingFlag = runFlag; \
		TANTRUM_CONCAT_INTERNAL( testName, _GlobalParametricInfo ).testNameStr = #testName; \
		TANTRUM_CONCAT_INTERNAL( testName, _GlobalParametricInfo ).suiteNameStr = suiteName; \
	}\
\
	/*6. The test function declared at Step1 is now declared here by the user*/\
	void ( testName )( __VA_ARGS__ )

//----------------------------------------------------------

#define TANTRUM_DECLARE_PARAMETRIC_TEST( testName, runFlag, ... )\
	TANTRUM_DECLARE_PARAMETRIC_SUITE_TEST_INTERNAL( NULL, testName, runFlag, __VA_ARGS__ )

//----------------------------------------------------------

#define TANTRUM_DECLARE_PARAMETRIC_SUITE_TEST( suiteName, testName, runFlag, ... )\
	TANTRUM_DECLARE_PARAMETRIC_SUITE_TEST_INTERNAL( #suiteName, testName, runFlag, __VA_ARGS__ )

//----------------------------------------------------------

#define TANTRUM_INVOKE_PARAMETRIC_TEST( nameOfTestToCall, parametricInvokationName, ... ) \
\
	/*1. Create a function with a name matching the test.*/ \
	void ( parametricInvokationName )( void ); \
\
	/*2. Define this test body immediately*/ \
	void ( parametricInvokationName )( void ) { TANTRUM_CONCAT_INTERNAL( nameOfTestToCall, _GlobalParametricInfo ).Callback( __VA_ARGS__ ); } \
\
	/*3. Create a testName_TestInfo struct that will just wrap the test information meta data.*/ \
	typedef struct TANTRUM_CONCAT_INTERNAL( parametricInvokationName, _TestInfo ) { \
		suiteTestInfo_t testInformation; \
	} TANTRUM_CONCAT_INTERNAL( parametricInvokationName, _TestInfo ); \
\
	/*4. Create a global instance of this new struct for us to access and write data about this test to.*/ \
	extern TANTRUM_CONCAT_INTERNAL( parametricInvokationName, _TestInfo ) TANTRUM_CONCAT_INTERNAL( parametricInvokationName, _GlobalInfo ); \
	TANTRUM_CONCAT_INTERNAL( parametricInvokationName, _TestInfo ) TANTRUM_CONCAT_INTERNAL( parametricInvokationName, _GlobalInfo ); \
\
	/*5. Create our invoker_n function. This is what the runner will loop over to grab the test function as well as all the information concerning it*/ \
	__declspec( dllexport ) inline suiteTestInfo_t TANTRUM_CONCAT_INTERNAL( tantrum_test_info_fetcher_, __COUNTER__ )( void ) { \
		TANTRUM_CONCAT_INTERNAL( nameOfTestToCall, _ParametricTestInfoBinder )();/*Make it so we can grab the needed information out of the test function's global info*/\
		TANTRUM_CONCAT_INTERNAL( parametricInvokationName, _GlobalInfo ).testInformation.callback = parametricInvokationName; \
		TANTRUM_CONCAT_INTERNAL( parametricInvokationName, _GlobalInfo ).testInformation.suiteNameStr = TANTRUM_CONCAT_INTERNAL( nameOfTestToCall, _GlobalParametricInfo ).suiteNameStr; \
		TANTRUM_CONCAT_INTERNAL( parametricInvokationName, _GlobalInfo ).testInformation.testNameStr = #parametricInvokationName; \
		TANTRUM_CONCAT_INTERNAL( parametricInvokationName, _GlobalInfo ).testInformation.testingFlag = TANTRUM_CONCAT_INTERNAL( nameOfTestToCall, _GlobalParametricInfo ).testingFlag; \
		return TANTRUM_CONCAT_INTERNAL( parametricInvokationName, _GlobalInfo ).testInformation; \
	}

//==========================================================
// PREPROCESSORS - CONDITION TESTING
//==========================================================

#define TANTRUM_TEST_TRUE( condition, message ) \
do { \
	if ( !( condition ) ) { \
		g_tantrumTestContext.totalErrorsInCurrentTests += 1; \
		printf( "TANTRUM_TEST_TRUE( %s ) has failed\n", #condition ); \
		printf( "%s\n", #message ); \
	} \
} while( 0 )

//----------------------------------------------------------

#define TANTRUM_TEST_EQUAL( conditionA, conditionB, message ) \
do { \
	if ( TantrumFloatEqualsInternal( conditionA, conditionB, TANTRUM_DEFAULT_EPSILON ) ) { \
		g_tantrumTestContext.totalErrorsInCurrentTests += 1; \
		printf( "TANTRUM_TEST_EQUAL( %f, %f ) has failed\n", (double) conditionA, (double) conditionB ); \
		printf( "%s\n", #message ); \
	} \
} while( 0 )

//----------------------------------------------------------

#define TANTRUM_TEST_NOT_EQUAL(conditionA, conditionB, message) \
do { \
	if ( TantrumFloatEqualsInternal( conditionA, conditionB, TANTRUM_DEFAULT_EPSILON ) ) { \
		g_tantrumTestContext.totalErrorsInCurrentTests += 1; \
		printf( "TANTRUM_TEST_NOT_EQUAL( %f, %f ) has failed\n", (double) conditionA, (double) conditionB ); \
		printf( "%s\n", #message ); \
	} \
} while( 0 )

//----------------------------------------------------------

#define TANTRUM_TEST_ALMOST_EQUAL( conditionA, conditionB, tolerance, message ) \
do { \
	if ( TantrumFloatEqualsInternal( conditionA, conditionB, tolerance ) ) { \
		g_tantrumTestContext.totalErrorsInCurrentTests += 1; \
		printf( "TANTRUM_TEST_ALMOST_EQUAL( %f, %f, %f ) has failed\n", (double) conditionA, (double) conditionB, (double) tolerance ); \
		printf( "%s\n", #message ); \
	} \
} while( 0 )

//----------------------------------------------------------

#define TANTRUM_TEST_NOT_ALMOST_EQUAL( conditionA, conditionB, tolerance, message ) \
do { \
	if ( !TantrumFloatEqualsInternal( conditionA, conditionB, tolerance ) ) { \
		g_tantrumTestContext.totalErrorsInCurrentTests += 1; \
		printf( "TANTRUM_TEST_NOT_ALMOST_EQUAL( %f, %f, %f ) has failed\n", (double) conditionA, (double) conditionB, (double) tolerance ); \
		printf( "%s\n", #message ); \
	} \
} while( 0 )

//----------------------------------------------------------

#define TANTRUM_TEST_GREATER_THAN( conditionA, conditionB, message ) \
do { \
	if ( conditionA > conditionB ) { \
		g_tantrumTestContext.totalErrorsInCurrentTests += 1; \
		printf( "TANTRUM_TEST_GREATER_THAN( %f, %f ) has failed\n", (double) conditionA, (double) conditionB ); \
		printf( "%s\n", #message ); \
	} \
} while( 0 )

//----------------------------------------------------------

#define TANTRUM_TEST_LESS_THAN( conditionA, conditionB, message ) \
do { \
	if ( conditionA < conditionB ) { \
		g_tantrumTestContext.totalErrorsInCurrentTests += 1; \
		printf( "TANTRUM_TEST_LESS_THAN( %f, %f ) has failed\n", (double) conditionA, (double) conditionB ); \
		printf( "%s\n", #message ); \
	} \
} while( 0 )

//==========================================================
// FUNCTIONS - PRIVATE API
//==========================================================

static void TantrumHandleCommandLineArgumentsInternal( int argc, char** argv ) {
#ifdef _WIN32
	char fullExePath[MAX_PATH];
	DWORD fullExePathLength = GetModuleFileName( NULL, fullExePath, MAX_PATH );
	if ( fullExePathLength == 0 ) {
		// TODO(DM): TantrumPrintErrorInternal
		printf( "ERROR: WinAPI call GetModuleFileName() failed: 0x%lX\n", GetLastError() );
		return;
	}

	g_tantrumTestContext.programName = fullExePath;
#else // _WIN32
#error Uncrecognised platform.  It appears Tantrum doesn't support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Tantrum/issues
#endif // _WIN32

	// parse command line args
	for ( int argIndex = 0; argIndex < argc; argIndex++ ) {
		const char* arg = argv[argIndex];

		if ( TantrumStringEqualsInternal( arg, "-s" ) ) {
			const char* nextArg = TantrumGetNextArgInternal( argIndex, argc, argv );
			// TODO(DM): if nextArg == NULL then error that the suite filter wasnt set and show usage to help user
			g_tantrumTestContext.suiteFilter = nextArg;
			g_tantrumTestContext.isFilteringTests = true;

			continue;
		}

		if ( TantrumStringEqualsInternal( arg, "-t" ) ) {
			const char* nextArg = TantrumGetNextArgInternal( argIndex, argc, argv );
			// TODO(DM): if nextArg == NULL then error that the test filter wasnt set and show usage to help user
			g_tantrumTestContext.testFilter = nextArg;
			g_tantrumTestContext.isFilteringTests = true;

			continue;
		}

		if ( TantrumStringEqualsInternal( arg, "-p" ) ) {
			g_tantrumTestContext.partialFilter = true;
			continue;
		}
	}

	// if partial filtering was enabled but the user did not then specify a suite or test filter then they need to know about incorrect usage
	if ( g_tantrumTestContext.partialFilter ) {
		if ( !g_tantrumTestContext.suiteFilter && !g_tantrumTestContext.testFilter ) {
			// TODO(DM): TantrumPrintErrorInternal
			printf( "ERROR: Partial filtering (-p) was enabled but suite or test filtering (-s, -t) was not.\n" );
			return;
		}
	}
}

//----------------------------------------------------------

static int TantrumExecuteAllTestsInternal() {
	// make the exe load itself
#ifdef _WIN32
	HANDLE handle = LoadLibrary( g_tantrumTestContext.programName );
	assert( handle );
#else // _WIN32
#error Uncrecognised platform.  It appears Tantrum doesn't support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Tantrum/issues
#endif // _WIN32

	// DM: yeah yeah yeah, I know: fixed-length string arrays bad
	// I'll write a tprintf at some point
	char testFuncNames[1024];
	testInfoFetcherFunc_t testInfoGrabberFunc = NULL;

	for ( uint32_t i = 0; i < g_tantrumTestContext.totalTestsDeclared; i++ ) {
		snprintf( testFuncNames, 1024, "tantrum_test_info_fetcher_%d", i );

		// get the test grabber functions out of the binary
#ifdef _WIN32
		testInfoGrabberFunc = (testInfoFetcherFunc_t) GetProcAddress( handle, testFuncNames );
#else // _WIN32
#error Uncrecognised platform.  It appears Tantrum doesn't support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Tantrum/issues
#endif // _WIN32

		assert( testInfoGrabberFunc );

		suiteTestInfo_t information = testInfoGrabberFunc();

		// if partial suite/test filtering is enabled then we want to check if the queried filter is in a part of the name they specified
		// otherwise partial filtering is off so we want to check for an exact string match
		tantrumStringCompareFunc_t stringCompareFunc = g_tantrumTestContext.partialFilter ? TantrumStringContainsInternal : TantrumStringEqualsInternal;

		bool isFilteredSuite = g_tantrumTestContext.suiteFilter && information.suiteNameStr && stringCompareFunc( information.suiteNameStr, g_tantrumTestContext.suiteFilter );

		if ( isFilteredSuite || !g_tantrumTestContext.suiteFilter ) {
			bool isFilteredTest = g_tantrumTestContext.testFilter && stringCompareFunc( information.testNameStr, g_tantrumTestContext.testFilter );

			if ( isFilteredTest || !g_tantrumTestContext.testFilter ) {
				g_tantrumTestContext.totalTestsFoundWithFilters += 1; // TANTRUM TELEMETRY

				// MY : I'm not checking the flag first as it'd still be helpful for search queries to see if the test even appears
				if ( information.testingFlag == TANTRUM_TEST_SHOULD_RUN ) {
					g_tantrumTestContext.totalErrorsInCurrentTests = 0;
					information.callback();
					g_tantrumTestContext.totalTestsExecuted += 1; // TANTRUM TELEMETRY

					if ( information.suiteNameStr ) {
						printf( "%s: ", information.suiteNameStr );
					}

					if ( g_tantrumTestContext.totalErrorsInCurrentTests > 0 ) {
						printf( "%s - FAILED\n\n", information.testNameStr );
						g_tantrumTestContext.testsFailed += 1; // TANTRUM TELEMETRY
					} else {
						printf( "%s - SUCCEEDED\n\n", information.testNameStr );
						g_tantrumTestContext.testsPassed += 1; // TANTRUM TELEMETRY
					}
				} else {
					const char* dodgeReason = information.testingFlag == TANTRUM_TEST_DEPRECATED ? "DEPRICATED" : "SHOULD_SKIP";
					printf( "NOT RUNNING \"%s\" AS IT WAS FLAGGED With \"%s\"\n\n", information.testNameStr, dodgeReason );
					g_tantrumTestContext.testsDodged += 1; // TANTRUM TELEMETRY
				}
			}
		}
	}

	PrintTestExecutionInformation();

	// cleanup
#ifdef _WIN32
	FreeLibrary( handle );
	handle = NULL;
#else // _WIN32
#error Uncrecognised platform.  It appears Tantrum doesn't support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Tantrum/issues
#endif // _WIN32

	return g_tantrumTestContext.testsFailed == 0 ? 0 : -1;
}

//----------------------------------------------------------

static int TantrumExecuteAllTestsWithArgumentsInternal( int argc, char** argv ) {
	TantrumHandleCommandLineArgumentsInternal( argc, argv );
	return TantrumExecuteAllTestsInternal();
}

//==========================================================
// PREPROCESSORS - USER API / SETUP
//==========================================================

// MY: I'd like to eventually add more security around this,
// such as ensuring it's only ever called/used once and thowing
// an error if it isn't. Maybe also (SOMEHOW) ensuring no test
// ever has a higher count.
#define TANTRUM_SETUP()									g_tantrumTestContext.totalTestsDeclared = __COUNTER__

//----------------------------------------------------------

#define TANTRUM_RUN_ALL_TESTS()							TantrumExecuteAllTestsInternal()

//----------------------------------------------------------

#define TANTRUM_RUN_ALL_TESTS_WITH_ARGS( argc, argv )	TantrumExecuteAllTestsWithArgumentsInternal( argc, argv )

//----------------------------------------------------------

#if defined( __GNUC__ ) || defined( __clang__ )
#pragma GCC diagnostic pop
#endif // defined( __GNUC__ ) || defined( __clang__ )

#ifdef __cplusplus
}
#endif
