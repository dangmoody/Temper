#define TEMPER_IMPLEMENTATION
#include "../../temper.h"

#define USE_TEMPER 1

#if USE_TEMPER
#ifdef __clang__
#pragma clang diagnostic ignored "-Wextra-semi"
#endif

TEMPER_PARAMETRIC( DoSomething, TEMPER_FLAG_SHOULD_RUN, const bool condition ) {
	TEMPER_CHECK_TRUE( condition );
}

TEMPER_INVOKE_PARAMETRIC_TEST( DoSomething, test0, true );
#else	// USE_TEMPER
#include <stdio.h>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wextra-semi"
#endif

typedef enum testFlag_t {
	TEST_FLAG_SHOULD_RUN		= 0,
	TEST_FLAG_SHOULD_SKIP,
	TEST_FLAG_DEPRECATED
} testFlag_t;

//----------------------------------------------------------

typedef void( *testCallbackOnBeforeTest_t )( void );
typedef void( *testCallbackOnAfterTest_t )( void );

typedef void( *testCallback_t )( void );

//----------------------------------------------------------

typedef struct testInfo_t {
	testCallbackOnBeforeTest_t	OnBeforeTest;
	testCallback_t				TestFuncCallback;
	testCallbackOnAfterTest_t	OnAfterTest;
	double						testTimeTaken;
	testFlag_t					testingFlag;
	uint32_t					pad0;
	const char*					testNameStr;
	const char*					suiteNameStr;
} testInfo_t;

typedef struct testContext_t {
	uint64_t	testInfosCount;
	testInfo_t	testInfos[1024];
} testContext_t;

static testContext_t g_context;

#ifdef _MSC_VER
#define AUTO_RUN_FUNC( testName ) \
	void __temper_test_info_fetcher_ ## testName( void ); \
	__declspec( allocate( ".CRT$XCU" ) ) void ( *testName ## _ )( void ) = __temper_test_info_fetcher_ ## testName; \
	__pragma( comment( linker, "/include:" PREFIX #testName "_" ) ) \
	void __temper_test_info_fetcher_ ## testName( void )
#else
#define AUTO_RUN_FUNC( funcName ) \
	__attribute__( ( constructor ) ) \
	void __temper_test_info_fetcher_ ## funcName ( void ); \
	void __temper_test_info_fetcher_ ## funcName ( void )
#endif

#define TEST_PARAMETRIC( testName, runFlag, ... ) \
	TEST_PARAMETRIC_INTERNAL( 0, testName, NULL, NULL, runFlag, __VA_ARGS__ )

#define TEST_PARAMETRIC_INTERNAL( suiteName, testName, onBeforeName, onAfterName, runFlag, ... ) \
	void GetParametricTestInfo_ ## testName( testInfo_t* outInfo ); \
	void GetParametricTestInfo_ ## testName( testInfo_t* outInfo ) { \
		outInfo->OnBeforeTest	= onBeforeName; \
		outInfo->OnAfterTest	= onAfterName; \
		outInfo->testingFlag	= runFlag; \
		outInfo->suiteNameStr	= #suiteName; \
		outInfo->testNameStr	= #testName; \
	} \
\
	void testName ( __VA_ARGS__ ); \
	void testName ( __VA_ARGS__ )

#define INVOKE_PARAMETRIC( testName, invokationName, ... ) \
	void callParametricTest ## invokationName( void ); \
	void callParametricTest ## invokationName( void ) { \
		testName( __VA_ARGS__ ); \
	} \
\
	AUTO_RUN_FUNC( invokationName ) { \
		testInfo_t* testInfo = &g_context.testInfos[g_context.testInfosCount++]; \
		GetParametricTestInfo_ ## testName( testInfo ); \
		testInfo->TestFuncCallback = callParametricTest ## invokationName; \
	}

TEST_PARAMETRIC( DoSomething, TEST_FLAG_SHOULD_RUN, const char* msg ) {
	printf( "%s", msg );
}

INVOKE_PARAMETRIC( DoSomething, test0, "Hi!\n" );
#endif	// USE_TEMPER

int main( int argc, char** argv ) {
#if USE_TEMPER
	TEMPER_RUN( argc, argv );
	int exitCode = TEMPER_GET_EXIT_CODE();
	printf( "\nnew_style returned: %d.\n", exitCode );
	return exitCode;
#else	// USE_TEMPER
	( (void) argc );
	( (void) argv );

	for ( uint64_t i = 0; i < g_context.testInfosCount; i++ ) {
		testInfo_t* testInfo = &g_context.testInfos[i];

		testInfo->TestFuncCallback();
	}

	return 0;
#endif	// USE_TEMPER
}