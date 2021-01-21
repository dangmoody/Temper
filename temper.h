/*
===========================================================================

Temper
v2.0.0

Distributed under MIT License:
Copyright (c) 2021:

	Dan Moody (daniel.guy.moody@gmail.com)
	Mike Young (IllThinkAboutIt@DoesntExist.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


TODO: documentation here


Changelog:
v2.0.0, <RELEASE DATE HERE>:
	* Tests are now self-registering.  All you need to do now is write the test code and the tests will get called automatically for you (unless the test is marked as skipped).
		* Because of this, the functions `TEMPER_RUN_TEST` and `TEMPER_SKIP_TEST` have been removed.
		* If you want to skip a test now you must now do so by setting the test flag.
		* Due to how tests are now registered, `TEMPER_SUITE` has also been removed.
	* Added parametric testing.
	* Added partial filtering for tests and suites.
		* When enabled, will search for suites/tests that only contain the filter given instead of searching for an exact match.
		* Disabled by default.  Use `-p` command line argument to enable.
	* Added self-testing functionality (TO BE USED ONLY FOR TEMPER DEVELOPERS).
	* Tests now run in their own thread.
		* This allows tests to always exit even if a test is aborted when running code not directly inside the test function.
	* Made various parts of the internal API extendable/overridable to help hook Temper into your codebase.
		* Write into `g_temperTestContext.callbacks` directly to override Temper's default internal functionality.
	* Removed the `-a` command line argument since this is now configured per check per test.
	* The default console output is no longer on one line to be more accomodating of test suites that have console output.
	* Tests that fail will no longer exit on the first failure, they will report all failures before exiting.
		* If you want a test to exit if it fails use the `_OR_ABORT` suffix on your test function.
	* Colored text console output is now always on.
		* Therefore the command line argument `-c` has been removed.
	* Much nicer internal API.  Nearly everything has been completely re-written from scratch.

v1.1.1, 1st October 2019:
	* Fix bug when parsing the --time-unit command line argument.

v1.1.0, 22nd September 2019:
	* Tests now display how long they took to run (defaulting to milliseconds).
		* You can configure this yourself via the --time-unit command line argument.
		* The unit you set must be either: "seconds", "ms", "us", "ns", or "clocks" (without speech marks).

v1.0.1, 16th April 2019:
	* Support for macOS.
	* Fixed some other weird issues appearing on some other flavours of Clang and GCC on Linux.

v1.0.0, 13th February 2019:
	* Initial release.

===========================================================================
*/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if defined( __clang__ )
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
#pragma clang diagnostic ignored "-Wdouble-promotion"
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#if defined( __APPLE__ )
// DM: only disabling this one to avoid a warning that gets generated when trying to convert function pointers to void*
// if anyone knows of a better way to get around that without disabling all pedantic warnings I'd love to hear about it
// submit an issue telling me how: https://github.com/dangmoody/Temper/issues
#pragma clang diagnostic ignored "-Wpedantic"
#endif
#elif defined( __GNUC__ )	// defined( __clang__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
// DM: only disabling this one to avoid a warning that gets generated when trying to convert function pointers to void*
// if anyone knows of a better way to get around that without disabling all pedantic warnings I'd love to hear about it
// submit an issue telling me how: https://github.com/dangmoody/Temper/issues
#pragma GCC diagnostic ignored "-Wpedantic"
#elif defined( _MSC_VER )
#pragma warning( push, 4 )
#pragma warning( disable : 4505 )	// unused function
#endif	// defined( __clang__ )

#if defined( __linux__ ) || defined( __APPLE__ )
#pragma push_macro( "_POSIX_C_SOURCE" )
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#if defined( _WIN32 )
#include <Windows.h>
#elif defined( __APPLE__ ) || defined( __linux__ )
#include <unistd.h>
#include <dlfcn.h>
#include <errno.h>
#include <sys/stat.h>
#if defined( __linux__ )
#include <linux/limits.h>
#elif defined( __APPLE__ )
#include <sys/syslimits.h>
#include <mach-o/dyld.h>
#endif
#include <time.h>
#include <pthread.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

#if defined( _WIN32 )
#define TEMPER_API	__declspec( dllexport )
#elif defined( __APPLE__ ) || defined( __linux__ )
#define TEMPER_API	__attribute__( ( visibility( "default" ) ) )
#else
#error Uncrecognised platform.  It appears Temper does not support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Temper/issues
#endif

#ifdef __cplusplus
#define TEMPER_EXTERN_C	extern "C"
#else
#define TEMPER_EXTERN_C
#endif

#if defined( _WIN32 )
#define TEMPER_MAX_PATH	MAX_PATH
#elif defined( __APPLE__ ) || defined( __linux__ )	// _WIN32
#define TEMPER_MAX_PATH	PATH_MAX
#else	// _WIN32
#error Uncrecognised platform.  It appears Temper does not support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Temper/issues
#endif	// _WIN32

#define TEMPER_BIT( x )	( 1 << ( x ) )

//==========================================================
// Public API
//==========================================================

#define TEMPER_SETUP() \
do { \
	g_temperTestContext.totalTestsDeclared = __COUNTER__; /* MUST NOT be in a function otherwise value of __COUNTER__ is not correct */ \
\
	TemperSetupInternal(); \
} while ( 0 )

//----------------------------------------------------------

#define TEMPER_RUN_ALL_TESTS()							TemperExecuteAllTestsInternal()

//----------------------------------------------------------

#define TEMPER_RUN_ALL_TESTS_WITH_ARGS( argc, argv )	TemperExecuteAllTestsWithArgumentsInternal( argc, argv )

//----------------------------------------------------------

#define TEMPER_TEST_TRUE( condition ) \
	TemperTestTrueInternal( condition, "TEMPER_TEST_TRUE(" #condition ")", false, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_TRUE_M( condition, message ) \
	TemperTestTrueInternal( condition, "TEMPER_TEST_TRUE_M(" #condition ", ...)", false, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_TRUE_OR_ABORT( condition ) \
	TemperTestTrueInternal( condition, "TEMPER_TEST_TRUE_OR_ABORT(" #condition ")", true, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_TRUE_OR_ABORT_M( condition, message ) \
	TemperTestTrueInternal( condition, "TEMPER_TEST_TRUE_OR_ABORT_M(" #condition ", ...)", true, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_FALSE( condition ) \
	TemperTestTrueInternal( !(condition), "TEMPER_TEST_FALSE(" #condition ")", false, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_FALSE_M( condition, message ) \
	TemperTestTrueInternal( !(condition), "TEMPER_TEST_FALSE_M(" #condition ", ...)", false, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_FALSE_OR_ABORT( condition ) \
	TemperTestTrueInternal( !(condition), "TEMPER_TEST_FALSE_OR_ABORT(" #condition ")", true, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_FALSE_OR_ABORT_M( condition, message ) \
	TemperTestTrueInternal( !(condition), "TEMPER_TEST_FALSE_OR_ABORT_M(" #condition ", ...)", true, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_EQUAL( conditionA, conditionB ) \
	TemperTestTrueInternal( conditionA == conditionB, "TEMPER_TEST_EQUAL(" #conditionA ", " #conditionB ")", false, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_EQUAL_M( conditionA, conditionB, message ) \
	TemperTestTrueInternal( conditionA == conditionB, "TEMPER_TEST_EQUAL_M(" #conditionA ", " #conditionB ", ...)", false, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_EQUAL_OR_ABORT( conditionA, conditionB ) \
	TemperTestTrueInternal( conditionA == conditionB, "TEMPER_TEST_EQUAL_OR_ABORT(" #conditionA ", " #conditionB ")", true, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_EQUAL_OR_ABORT_M( conditionA, conditionB, message ) \
	TemperTestTrueInternal( conditionA == conditionB, "TEMPER_TEST_EQUAL_OR_ABORT_M(" #conditionA ", " #conditionB ", ...)", true, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_NOT_EQUAL( conditionA, conditionB ) \
	TemperTestTrueInternal( conditionA != conditionB, "TEMPER_TEST_NOT_EQUAL(" #conditionA ", " #conditionB ")", false, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_NOT_EQUAL_M( conditionA, conditionB, message ) \
	TemperTestTrueInternal( conditionA != conditionB, "TEMPER_TEST_NOT_EQUAL_M(" #conditionA ", " #conditionB ", ...)", false, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_NOT_EQUAL_OR_ABORT( conditionA, conditionB ) \
	TemperTestTrueInternal( conditionA != conditionB, "TEMPER_TEST_NOT_EQUAL_OR_ABORT(" #conditionA ", " #conditionB ")", true, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_NOT_EQUAL_OR_ABORT_M( conditionA, conditionB, message ) \
	TemperTestTrueInternal( conditionA != conditionB, "TEMPER_TEST_NOT_EQUAL_OR_ABORT_M(" #conditionA ", " #conditionB ", ...)", true, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_FLOAT_EQUAL( conditionA, conditionB ) \
	TemperTestTrueInternal( TEMPER_FLOAT_EQUALS( conditionA, conditionB, TEMPER_DEFAULT_EPSILON ), "TEMPER_TEST_FLOAT_EQUAL(" #conditionA ", " #conditionB ")", false, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_FLOAT_EQUAL_M( conditionA, conditionB, message ) \
	TemperTestTrueInternal( TEMPER_FLOAT_EQUALS( conditionA, conditionB, TEMPER_DEFAULT_EPSILON ), "TEMPER_TEST_FLOAT_EQUAL_M(" #conditionA ", " #conditionB ", ...)", false, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_FLOAT_EQUAL_OR_ABORT( conditionA, conditionB ) \
	TemperTestTrueInternal( TEMPER_FLOAT_EQUALS( conditionA, conditionB, TEMPER_DEFAULT_EPSILON ), "TEMPER_TEST_FLOAT_EQUAL_OR_ABORT(" #conditionA ", " #conditionB ")", true, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_FLOAT_EQUAL_OR_ABORT_M( conditionA, conditionB, message ) \
	TemperTestTrueInternal( TEMPER_FLOAT_EQUALS( conditionA, conditionB, TEMPER_DEFAULT_EPSILON ), "TEMPER_TEST_FLOAT_EQUAL_OR_ABORT_M(" #conditionA ", " #conditionB ", ...)", true, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_ALMOST_EQUAL( conditionA, conditionB, tolerance ) \
	TemperTestTrueInternal( TEMPER_FLOAT_EQUALS( conditionA, conditionB, tolerance ), "TEMPER_TEST_ALMOST_EQUAL(" #conditionA ", " #conditionB ", " #tolerance ")", false, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_ALMOST_EQUAL_M( conditionA, conditionB, tolerance, message ) \
	TemperTestTrueInternal( TEMPER_FLOAT_EQUALS( conditionA, conditionB, tolerance ), "TEMPER_TEST_ALMOST_EQUAL_M(" #conditionA ", " #conditionB ", " #tolerance ", ...)", false, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_ALMOST_EQUAL_OR_ABORT( conditionA, conditionB, tolerance ) \
	TemperTestTrueInternal( TEMPER_FLOAT_EQUALS( conditionA, conditionB, tolerance ), "TEMPER_TEST_ALMOST_EQUAL_OR_ABORT(" #conditionA ", " #conditionB ", " #tolerance ")", true, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_ALMOST_EQUAL_OR_ABORT_M( conditionA, conditionB, tolerance, message ) \
	TemperTestTrueInternal( TEMPER_FLOAT_EQUALS( conditionA, conditionB, tolerance ), "TEMPER_TEST_ALMOST_EQUAL_OR_ABORT_M(" #conditionA ", " #conditionB ", " #tolerance ", ...)", true, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_NOT_ALMOST_EQUAL( conditionA, conditionB, tolerance ) \
	TemperTestTrueInternal( !TEMPER_FLOAT_EQUALS( conditionA, conditionB, tolerance ), "TEMPER_TEST_NOT_ALMOST_EQUAL(" #conditionA ", " #conditionB ", " #tolerance ")", false, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_NOT_ALMOST_EQUAL_M( conditionA, conditionB, tolerance, message ) \
	TemperTestTrueInternal( !TEMPER_FLOAT_EQUALS( conditionA, conditionB, tolerance ), "TEMPER_TEST_NOT_ALMOST_EQUAL_M(" #conditionA ", " #conditionB ", " #tolerance ", ...)", false, message, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_NOT_ALMOST_EQUAL_OR_ABORT( conditionA, conditionB, tolerance ) \
	TemperTestTrueInternal( !TEMPER_FLOAT_EQUALS( conditionA, conditionB, tolerance ), "TEMPER_TEST_NOT_ALMOST_EQUAL_OR_ABORT(" #conditionA ", " #conditionB ", " #tolerance ")", true, NULL, __FILE__, __LINE__ )

//----------------------------------------------------------

#define TEMPER_TEST_NOT_ALMOST_EQUAL_OR_ABORT_M( conditionA, conditionB, tolerance, message ) \
	TemperTestTrueInternal( !TEMPER_FLOAT_EQUALS( conditionA, conditionB, tolerance ), "TEMPER_TEST_NOT_ALMOST_EQUAL_OR_ABORT_M(" #conditionA ", " #conditionB ", " #tolerance ", ...)", true, message, __FILE__, __LINE__ )

//==========================================================
// User-Overridable Preprocessor defines
//
// By default, Temper will use it's own internal implementations for things.
// But you can override them to help hook Temper into your codebase.
// This must be done before including temper.h
//==========================================================

#ifndef TEMPER_EXIT_SUCCESS
#define TEMPER_EXIT_SUCCESS		EXIT_SUCCESS
#endif

#ifndef TEMPER_EXIT_FAILURE
#define TEMPER_EXIT_FAILURE		EXIT_FAILURE
#endif

#ifndef TEMPER_ASSERT
#define TEMPER_ASSERT			assert
#endif

#ifndef TEMPER_SNPRINTF
#define TEMPER_SNPRINTF			snprintf
#endif

//==========================================================
// TYPES
//==========================================================

typedef enum temperTestFlag_t {
	TEMPER_TEST_FLAG_SHOULD_RUN	= 0,
	TEMPER_TEST_FLAG_SHOULD_SKIP,
	TEMPER_TEST_FLAG_DEPRECATED
} temperTestFlag_t;

typedef enum temperTimeUnit_t {
	TEMPER_TIME_UNIT_CLOCKS		= 0,
	TEMPER_TIME_UNIT_NS,
	TEMPER_TIME_UNIT_US,
	TEMPER_TIME_UNIT_MS,
	TEMPER_TIME_UNIT_SECONDS
} temperTimeUnit_t;

//----------------------------------------------------------

typedef enum temperTestExpectationFlagBits_t {
	TEMPER_TEST_EXPECTATION_NONE		= 0,
	TEMPER_TEST_EXPECTATION_FLAG_FAIL	= TEMPER_BIT( 0 ),
	TEMPER_TEST_EXPECTATION_FLAG_ABORT	= TEMPER_BIT( 1 )
} temperTestExpectationFlagBits_t;
typedef uint32_t temperTestExpectationFlags_t;

//----------------------------------------------------------

typedef uint32_t temperBool32;

//----------------------------------------------------------

typedef void( *temperTestCallback_t )( void );

//----------------------------------------------------------

typedef struct temperSuiteTestInfo_t {
	temperTestCallback_t			Callback;
	double							testTimeTaken;
	temperTestFlag_t				testingFlag;
	temperTestExpectationFlags_t	expectationFlags;
	const char*						testNameStr;
	const char*						suiteNameStr;
} temperSuiteTestInfo_t;

typedef temperSuiteTestInfo_t( *temperTestInfoFetcherFunc_t )( void );

//----------------------------------------------------------

typedef struct temperCallbacks_t {
	void	( *Log )( const char* fmt, ... );
	void	( *LogWarning )( const char* fmt, ... );
	void	( *LogError )( const char* fmt, ... );
	bool	( *StringEquals )( const char* a, const char* b );
	bool	( *StringContains )( const char* a, const char* b );
	void*	( *GetProcAddress )( void* handle, const char* funcName );
	void	( *OnBeforeTest )( const temperSuiteTestInfo_t* testInfo );
	void 	( *RunTestThread )( temperSuiteTestInfo_t* testInfo );
	bool	( *FloatEquals )( const float a, const float b, const float epsilon );
	double	( *GetTimestamp )( void );
	void	( *OnAfterTest )( const temperSuiteTestInfo_t* testInfo );
	// DM: cold in cache, these are called infrequently, once, or during shutdown
	void*	( *LoadEXEHandle )( void );
	void	( *UnloadEXEHandle )( void* handle );
	void	( *OnAllTestsFinished )( void );
} temperCallbacks_t;

//----------------------------------------------------------

typedef struct temperTestContext_t {
	// overridable callbacks - you can set them directly
	temperCallbacks_t	callbacks;

#ifdef _WIN32
	LARGE_INTEGER		timestampFrequency;
#endif
	double				currentTestStartTime;
	double				currentTestEndTime;
	double				totalExecutionTime;
	uint32_t			testsPassed;
	uint32_t			testsFailed;
	uint32_t			testsAborted;
	uint32_t			testsSkipped;
	uint32_t			totalTestsDeclared; // Gets set in the main function with a preprocessor
	uint32_t			totalTestsFoundWithFilters;
	uint32_t			totalTestsExecuted;
	uint32_t			currentTestErrorCount;
	temperBool32		currentTestWasAborted;
	temperBool32		partialFilter;
	temperTimeUnit_t	timeUnit;
	uint32_t			pad0;
	char				programName[TEMPER_MAX_PATH];
	const char*			suiteFilterPrevious;
	const char*			suiteFilter;
	const char*			testFilter;
} temperTestContext_t;

//==========================================================
// GLOBALS
//==========================================================

static temperTestContext_t		g_temperTestContext;

//==========================================================
// PREPROCESSORS - TEMPER INTERNAL
//==========================================================

#if defined( _WIN32 )
#define TEMPER_EXIT_TEST_THREAD_INTERNAL()		ExitThread( TEMPER_EXIT_FAILURE )
#else
#define TEMPER_EXIT_TEST_THREAD_INTERNAL()		pthread_exit( NULL )
#endif

//----------------------------------------------------------

#define TEMPER_DEFAULT_EPSILON					0.00001f

//----------------------------------------------------------

#define TEMPER_CONCAT_INTERNAL_FINAL( a, b )	a ## b

//----------------------------------------------------------

#define TEMPER_CONCAT_INTERNAL( a, b )			TEMPER_CONCAT_INTERNAL_FINAL( a, b )

//----------------------------------------------------------

#define TEMPER_DEFINE_TEST_INTERNAL( counter, suiteNameString, testName, testExpectationFlags, runFlag ) \
\
	/*1. Create a function with a name matching the test.*/ \
	void ( testName )( void ); \
\
	/*2. Create a testName_TestInfo struct that will just wrap the test information meta data.*/ \
	typedef struct TEMPER_CONCAT_INTERNAL( testName, _TestInfo ) { \
		temperSuiteTestInfo_t testInformation; \
	} TEMPER_CONCAT_INTERNAL( testName, _TestInfo ); \
\
	/*3. Create a global instance of this new struct for us to access and write data about this test to.*/ \
	extern TEMPER_CONCAT_INTERNAL( testName, _TestInfo ) TEMPER_CONCAT_INTERNAL( testName, _GlobalInfo ); \
	TEMPER_CONCAT_INTERNAL( testName, _TestInfo ) TEMPER_CONCAT_INTERNAL( testName, _GlobalInfo ); \
\
	/*4. Create our invoker_n function. This is what the runner will loop over to grab the test function as well as all the information concerning it*/ \
	/* HACK(DM): I shouldn't have to add extern "C" before each declaration here to make this work for c++ compiled binaries.  I already did that at the top of the header! How is that NOT a compiler bug!? */ \
	TEMPER_EXTERN_C temperSuiteTestInfo_t TEMPER_API TEMPER_CONCAT_INTERNAL( temper_test_info_fetcher_, counter )( void ); \
	temperSuiteTestInfo_t TEMPER_CONCAT_INTERNAL( temper_test_info_fetcher_, counter )( void ) { \
		TEMPER_CONCAT_INTERNAL( testName, _GlobalInfo ).testInformation.Callback = testName; \
		TEMPER_CONCAT_INTERNAL( testName, _GlobalInfo ).testInformation.suiteNameStr = suiteNameString; \
		TEMPER_CONCAT_INTERNAL( testName, _GlobalInfo ).testInformation.expectationFlags = testExpectationFlags; \
		TEMPER_CONCAT_INTERNAL( testName, _GlobalInfo ).testInformation.testNameStr = #testName; \
		TEMPER_CONCAT_INTERNAL( testName, _GlobalInfo ).testInformation.testingFlag = runFlag; \
		return TEMPER_CONCAT_INTERNAL( testName, _GlobalInfo ).testInformation; \
	} \
\
	/*5. The test function declared at Step1 is now declared here by the user*/ \
	void ( testName )( void )

//----------------------------------------------------------

#ifdef TEMPER_SELF_TEST_ENABLED
#define TEMPER_TEST( testName, expectationFlags, runFlag ) \
	TEMPER_DEFINE_TEST_INTERNAL( __COUNTER__, NULL, testName, expectationFlags, runFlag )
#else
#define TEMPER_TEST( testName, runFlag ) \
	TEMPER_DEFINE_TEST_INTERNAL( __COUNTER__, NULL, testName, TEMPER_TEST_EXPECTATION_NONE, runFlag )
#endif //TEMPER_SELF_TEST_ENABLED

//----------------------------------------------------------

#ifdef TEMPER_SELF_TEST_ENABLED
#define TEMPER_SUITE_TEST( suiteName, testName, testExpectationFlags, runFlag ) \
	TEMPER_DEFINE_TEST_INTERNAL( __COUNTER__, #suiteName, testName, testExpectationFlags, runFlag )
#else
#define TEMPER_SUITE_TEST( suiteName, testName, runFlag ) \
	TEMPER_DEFINE_TEST_INTERNAL( __COUNTER__, #suiteName, testName, TEMPER_TEST_EXPECTATION_NONE, runFlag )
#endif //TEMPER_SELF_TEST_ENABLED

//----------------------------------------------------------

#define TEMPER_DECLARE_PARAMETRIC_SUITE_TEST_INTERNAL( suiteName, testName, testExpectationFlags, runFlag, ... )\
\
	/*1. Create a function with a name matching the test with the provided parameters.*/\
	void ( testName )( __VA_ARGS__ ); \
\
	/*2. Typedef this function type.*/ \
	typedef void ( *TEMPER_CONCAT_INTERNAL( testName, _FuncType ) )( __VA_ARGS__ ); \
\
	/*3. Stash this function and run info in a struct unique to this.*/ \
	typedef struct TEMPER_CONCAT_INTERNAL( testName, _ParametricTestInfo ) { \
		TEMPER_CONCAT_INTERNAL( testName, _FuncType ) Callback; \
		temperTestFlag_t				testingFlag; \
		temperTestExpectationFlags_t	expectationFlags; \
		const char*						testNameStr; \
		const char*						suiteNameStr; \
	} TEMPER_CONCAT_INTERNAL( testName, _ParametricTestInfo ); \
\
	/*4. Create a global instance of this new struct for us to access and write data about this test to.*/ \
	extern TEMPER_CONCAT_INTERNAL( testName, _ParametricTestInfo ) TEMPER_CONCAT_INTERNAL( testName, _GlobalParametricInfo ); \
	TEMPER_CONCAT_INTERNAL( testName, _ParametricTestInfo ) TEMPER_CONCAT_INTERNAL( testName, _GlobalParametricInfo ); \
\
	/*5. Define an info binding function to tie all this information into the struct*/ \
	/* HACK(DM): I shouldn't have to add extern "C" before each declaration here to make this work for c++ compiled binaries.  I already did that at the top of the header! How is that NOT a compiler bug!? */ \
	TEMPER_EXTERN_C void TEMPER_API TEMPER_CONCAT_INTERNAL( testName, _ParametricTestInfoBinder )( void ); \
	void TEMPER_CONCAT_INTERNAL( testName, _ParametricTestInfoBinder )( void ) { \
		TEMPER_CONCAT_INTERNAL( testName, _GlobalParametricInfo ).Callback = testName; \
		TEMPER_CONCAT_INTERNAL( testName, _GlobalParametricInfo ).testingFlag = runFlag; \
		TEMPER_CONCAT_INTERNAL( testName, _GlobalParametricInfo ).expectationFlags = testExpectationFlags; \
		TEMPER_CONCAT_INTERNAL( testName, _GlobalParametricInfo ).testNameStr = #testName; \
		TEMPER_CONCAT_INTERNAL( testName, _GlobalParametricInfo ).suiteNameStr = suiteName; \
	}\
\
	/*6. The test function declared at Step1 is now declared here by the user*/\
	void ( testName )( __VA_ARGS__ )

//----------------------------------------------------------

#ifdef TEMPER_SELF_TEST_ENABLED
#define TEMPER_DECLARE_PARAMETRIC_TEST( testName, testExpectationFlags, runFlag, ... )\
	TEMPER_DECLARE_PARAMETRIC_SUITE_TEST_INTERNAL( NULL, testName, testExpectationFlags, runFlag, __VA_ARGS__ )
#else
#define TEMPER_DECLARE_PARAMETRIC_TEST( testName, runFlag, ... )\
	TEMPER_DECLARE_PARAMETRIC_SUITE_TEST_INTERNAL( NULL, testName, TEMPER_TEST_EXPECTATION_NONE, runFlag, __VA_ARGS__ )
#endif //TEMPER_SELF_TEST_ENABLED

//----------------------------------------------------------

#ifdef TEMPER_SELF_TEST_ENABLED
#define TEMPER_DECLARE_PARAMETRIC_SUITE_TEST( suiteName, testName, testExpectationFlags, runFlag, ... )\
	TEMPER_DECLARE_PARAMETRIC_SUITE_TEST_INTERNAL( #suiteName, testName, testExpectationFlags, runFlag, __VA_ARGS__ )
#else
#define TEMPER_DECLARE_PARAMETRIC_SUITE_TEST( suiteName, testName, runFlag, ... )\
	TEMPER_DECLARE_PARAMETRIC_SUITE_TEST_INTERNAL( #suiteName, testName, TEMPER_TEST_EXPECTATION_NONE, runFlag, __VA_ARGS__ )
#endif //TEMPER_SELF_TEST_ENABLED

//----------------------------------------------------------

#define TEMPER_INVOKE_PARAMETRIC_TEST_INTERNAL( counter, nameOfTestToCall, testExpectationFlags, ... ) \
\
	/*1. Create a function with a name matching the test.*/ \
	void ( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ) )( void ); \
\
	/*2. Define this test body immediately*/ \
	void ( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ) )( void ) { \
		TEMPER_CONCAT_INTERNAL( nameOfTestToCall, _GlobalParametricInfo ).Callback( __VA_ARGS__ ); \
	} \
\
	/*3. Create a testName_TestInfo struct that will just wrap the test information meta data.*/ \
	typedef struct TEMPER_CONCAT_INTERNAL( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ), _TestInfo ) { \
		temperSuiteTestInfo_t testInformation; \
	} TEMPER_CONCAT_INTERNAL( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ), _TestInfo ); \
\
	/*4. Create a global instance of this new struct for us to access and write data about this test to.*/ \
	extern TEMPER_CONCAT_INTERNAL( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ), _TestInfo ) TEMPER_CONCAT_INTERNAL( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ), _GlobalInfo ); \
	TEMPER_CONCAT_INTERNAL( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ), _TestInfo ) TEMPER_CONCAT_INTERNAL( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ), _GlobalInfo ); \
\
	/*5. Create our invoker_n function. This is what the runner will loop over to grab the test function as well as all the information concerning it*/ \
	/* HACK(DM): I shouldn't have to add extern "C" before each declaration here to make this work for c++ compiled binaries.  I already did that at the top of the header! How is that NOT a compiler bug!? */ \
	TEMPER_EXTERN_C temperSuiteTestInfo_t TEMPER_API TEMPER_CONCAT_INTERNAL( temper_test_info_fetcher_, counter )( void ); \
	temperSuiteTestInfo_t TEMPER_CONCAT_INTERNAL( temper_test_info_fetcher_, counter )( void ) { \
		TEMPER_CONCAT_INTERNAL( nameOfTestToCall, _ParametricTestInfoBinder )();/*Make it so we can grab the needed information out of the test function's global info*/\
		TEMPER_CONCAT_INTERNAL( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ), _GlobalInfo ).testInformation.Callback = TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ); \
		TEMPER_CONCAT_INTERNAL( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ), _GlobalInfo ).testInformation.suiteNameStr = TEMPER_CONCAT_INTERNAL( nameOfTestToCall, _GlobalParametricInfo ).suiteNameStr; \
		TEMPER_CONCAT_INTERNAL( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ), _GlobalInfo ).testInformation.expectationFlags = testExpectationFlags; \
		TEMPER_CONCAT_INTERNAL( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ), _GlobalInfo ).testInformation.testNameStr = #nameOfTestToCall; \
		TEMPER_CONCAT_INTERNAL( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ), _GlobalInfo ).testInformation.testingFlag = TEMPER_CONCAT_INTERNAL( nameOfTestToCall, _GlobalParametricInfo ).testingFlag; \
		return TEMPER_CONCAT_INTERNAL( TEMPER_CONCAT_INTERNAL( temper_parametric_wrapper_, counter ), _GlobalInfo ).testInformation; \
	} \
\
	/* leave this at the end so the macro can end with a semicolon */ \
	temperSuiteTestInfo_t TEMPER_API TEMPER_CONCAT_INTERNAL( temper_test_info_fetcher_, counter )( void )

//----------------------------------------------------------

#ifdef TEMPER_SELF_TEST_ENABLED
#define TEMPER_INVOKE_PARAMETRIC_TEST( nameOfTestToCall, testExpectationFlags, ... ) \
	TEMPER_INVOKE_PARAMETRIC_TEST_INTERNAL( __COUNTER__, nameOfTestToCall, testExpectationFlags, __VA_ARGS__ )
#else
#define TEMPER_INVOKE_PARAMETRIC_TEST( nameOfTestToCall, ... ) \
	TEMPER_INVOKE_PARAMETRIC_TEST_INTERNAL( __COUNTER__, nameOfTestToCall, TEMPER_TEST_EXPECTATION_NONE, __VA_ARGS__ )
#endif // TEMPER_SELF_TEST_ENABLED

//==========================================================
// Internal Functions
//
// You as the user probably don't want to be directly touching these.
//==========================================================

#if defined( _WIN32 )
#define TEMPER_COLOR_DEFAULT	0x07
#define TEMPER_COLOR_RED		0x0C
#define TEMPER_COLOR_GREEN		0x02
#define TEMPER_COLOR_YELLOW		0x0E

typedef uint32_t				temperTextColor_t;
#elif defined( __linux__ ) || defined( __APPLE__ )
#define TEMPER_COLOR_DEFAULT	"\033[0m"
#define TEMPER_COLOR_RED		"\033[0;31m"
#define TEMPER_COLOR_GREEN		"\033[0;32m"
#define TEMPER_COLOR_YELLOW		"\033[1;33m"

typedef const char*				temperTextColor_t;
#endif // defined( _WIN32 )

//----------------------------------------------------------

static void TemperSetTextColorInternal( const temperTextColor_t color ) {
#if defined( _WIN32 )
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), (WORD) color );
#elif defined( __APPLE__ ) || defined( __linux__ )
	printf( "%s", color );
#else
#error Uncrecognised platform.  It appears Temper does not support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Temper/issues
#endif
}

//----------------------------------------------------------

static void TemperLogInternal( const char* fmt, ... ) {
	TEMPER_ASSERT( fmt );

	va_list args;
	va_start( args, fmt );
	vprintf( fmt, args );
	va_end( args );
}

//----------------------------------------------------------

static void TemperLogWarningInternal( const char* fmt, ... ) {
	TEMPER_ASSERT( fmt );

	va_list args;
	va_start( args, fmt );

	TemperSetTextColorInternal( TEMPER_COLOR_RED );

	printf( "WARNING: " );

	TemperSetTextColorInternal( TEMPER_COLOR_YELLOW );

	vprintf( fmt, args );

	TemperSetTextColorInternal( TEMPER_COLOR_DEFAULT );

	va_end( args );
}

//----------------------------------------------------------

static void TemperLogErrorInternal( const char* fmt, ... ) {
	TEMPER_ASSERT( fmt );

	va_list args;
	va_start( args, fmt );

	TemperSetTextColorInternal( TEMPER_COLOR_RED );

	printf( "ERROR: " );

	TemperSetTextColorInternal( TEMPER_COLOR_YELLOW );

	vprintf( fmt, args );

	TemperSetTextColorInternal( TEMPER_COLOR_DEFAULT );

	va_end( args );
}

//----------------------------------------------------------

static uint32_t TemperGetPercentInternal( uint32_t yourValue, uint32_t yourMax ) {
	return (uint32_t) ( ( ( (float) yourValue ) / ( (float) yourMax ) ) * 100 );
}

//----------------------------------------------------------

static bool TemperFloatEqualsInternal( const float a, const float b, const float epsilon ) {
	return fabsf( a - b ) <= epsilon;
}

//----------------------------------------------------------

static const char* TemperGetNextArgInternal( const int argIndex, const int argc, char** argv ) {
	TEMPER_ASSERT( argc );
	TEMPER_ASSERT( argv );

	return ( argIndex + 1 < argc ) ? argv[argIndex + 1] : NULL;
}

//----------------------------------------------------------

static bool TemperStringEqualsInternal( const char* a, const char* b ) {
	TEMPER_ASSERT( a );
	TEMPER_ASSERT( b );

	return strcmp( a, b ) == 0;
}

//----------------------------------------------------------

static bool TemperStringContainsInternal( const char* str, const char* substring ) {
	return strstr( str, substring ) != NULL;
}

//----------------------------------------------------------

static double TemperGetTimestampInternal( void ) {
#if defined( _WIN32 )
	LARGE_INTEGER now;
	QueryPerformanceCounter( &now );

	switch ( g_temperTestContext.timeUnit ) {
		case TEMPER_TIME_UNIT_CLOCKS:	return ( (double) now.QuadPart );
		case TEMPER_TIME_UNIT_NS:		return ( (double) ( now.QuadPart * 1000000000 ) / (double) g_temperTestContext.timestampFrequency.QuadPart );
		case TEMPER_TIME_UNIT_US:		return ( (double) ( now.QuadPart * 1000000 ) / (double) g_temperTestContext.timestampFrequency.QuadPart );
		case TEMPER_TIME_UNIT_MS:		return ( (double) ( now.QuadPart * 1000 ) / (double) g_temperTestContext.timestampFrequency.QuadPart );
		case TEMPER_TIME_UNIT_SECONDS:	return ( (double) ( now.QuadPart ) / (double) g_temperTestContext.timestampFrequency.QuadPart );
	}
#elif defined( __APPLE__ ) || defined( __linux__ )	// defined( _WIN32 )
	struct timespec now;
	clock_gettime( CLOCK_MONOTONIC, &now );

	int64_t clocks = (int64_t) ( now.tv_sec * 1000000000 + now.tv_nsec );

	switch ( g_temperTestContext.timeUnit ) {
		case TEMPER_TIME_UNIT_CLOCKS:	return (double) clocks;
		case TEMPER_TIME_UNIT_NS:		return (double) clocks;
		case TEMPER_TIME_UNIT_US:		return (double) clocks / 1000.0;
		case TEMPER_TIME_UNIT_MS:		return (double) clocks / 1000000.0;
		case TEMPER_TIME_UNIT_SECONDS:	return (double) clocks / 1000000000.0;
	}
#else	// defined( _WIN32 )
#error Uncrecognised platform.  It appears Temper does not support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Temper/issues
#endif	// defined( _WIN32 )

	// should never get here
	TEMPER_ASSERT( false && "Unrecognised time unit passed into TemperGetTimestampInternal().\n" );

	return 0.0;
}

//----------------------------------------------------------

static void TemperShowUsageInternal( void ) {
	g_temperTestContext.callbacks.Log(
		"Arguments:\n"
		"    [-h|--help]\n"
		"        Shows this help and then exits.\n"
		"\n"
		"    -t <test>\n"
		"        Only run the test with the given name.\n"
		"\n"
		"    -s <suite>\n"
		"        Only run tests in the suite with the given name.\n"
		"\n"
		"    -p\n"
		"        Enable partial filtering, which will only run tests and suites that contain the text specified in the filters.\n"
		"\n"
		"    --time-unit [seconds|ms|us|ns|clocks]\n"
		"        Set the units to measure test times in.\n"
		"        The default is microseconds.\n"
		"\n"
	);
}

//----------------------------------------------------------

static bool TemperHandleCommandLineArgumentsInternal( int argc, char** argv ) {
	// parse command line args
	for ( int argIndex = 0; argIndex < argc; argIndex++ ) {
		const char* arg = argv[argIndex];

		if ( g_temperTestContext.callbacks.StringEquals( arg, "-h" ) || g_temperTestContext.callbacks.StringEquals( arg, "--help" ) ) {
			TemperShowUsageInternal();
			return false;
		}

		if ( g_temperTestContext.callbacks.StringEquals( arg, "-s" ) ) {
			const char* nextArg = TemperGetNextArgInternal( argIndex, argc, argv );
			if ( !nextArg ) {
				g_temperTestContext.callbacks.LogError( "Value for argument \"%s\" was not set.\n", arg );
				TemperShowUsageInternal();
				return false;
			}

			g_temperTestContext.suiteFilter = nextArg;

			continue;
		}

		if ( g_temperTestContext.callbacks.StringEquals( arg, "-t" ) ) {
			const char* nextArg = TemperGetNextArgInternal( argIndex, argc, argv );
			if ( !nextArg ) {
				g_temperTestContext.callbacks.LogError( "Value for argument \"%s\" was not set.\n", arg );
				TemperShowUsageInternal();
				return false;
			}

			g_temperTestContext.testFilter = nextArg;

			continue;
		}

		if ( g_temperTestContext.callbacks.StringEquals( arg, "-p" ) ) {
			g_temperTestContext.partialFilter = true;
			continue;
		}

		if ( g_temperTestContext.callbacks.StringEquals( arg, "--time-unit" ) ) {
			const char* nextArg = TemperGetNextArgInternal( argIndex, argc, argv );
			if ( !nextArg ) {
				g_temperTestContext.callbacks.LogError( "Value for argument \"%s\" was not set.\n", arg );
				TemperShowUsageInternal();
				return false;
			}

			if ( g_temperTestContext.callbacks.StringEquals( nextArg, "seconds" ) ) {
				g_temperTestContext.timeUnit = TEMPER_TIME_UNIT_SECONDS;
			} else if ( g_temperTestContext.callbacks.StringEquals( nextArg, "ms" ) ) {
				g_temperTestContext.timeUnit = TEMPER_TIME_UNIT_MS;
			} else if ( g_temperTestContext.callbacks.StringEquals( nextArg, "us" ) ) {
				g_temperTestContext.timeUnit = TEMPER_TIME_UNIT_US;
			} else if ( g_temperTestContext.callbacks.StringEquals( nextArg, "ns" ) ) {
				g_temperTestContext.timeUnit = TEMPER_TIME_UNIT_NS;
			} else if ( g_temperTestContext.callbacks.StringEquals( nextArg, "clocks" ) ) {
				g_temperTestContext.timeUnit = TEMPER_TIME_UNIT_CLOCKS;
			} else {
				g_temperTestContext.callbacks.LogError(
					"Invalid time unit \"%s\" specified.  Please select from one of the following:\n"
					"\t- seconds\n"
					"\t- ms\n"
					"\t- us\n"
					"\t- ns\n"
					"\t- clocks\n"
					"\n",
					nextArg
				);

				TemperShowUsageInternal();

				return false;
			}

			continue;
		}
	}

	// if partial filtering was enabled but the user did not then specify a suite or test filter then they need to know about incorrect usage
	if ( g_temperTestContext.partialFilter ) {
		if ( !g_temperTestContext.suiteFilter && !g_temperTestContext.testFilter ) {
			g_temperTestContext.callbacks.LogError( "Partial filtering (-p) was enabled but suite or test filtering (-s, -t) was not.\n\n" );

			TemperShowUsageInternal();

			return false;
		}
	}

	return true;
}

//----------------------------------------------------------

static void* TemperLoadEXEHandleInternal( void ) {
#if defined( _WIN32 )
	HMODULE handle = LoadLibrary( g_temperTestContext.programName );
	TEMPER_ASSERT( handle );
	return handle;
#elif defined( __APPLE__ ) || defined( __linux__ )	// defined( _WIN32 )
	void* handle = dlopen( NULL, RTLD_LAZY );
	TEMPER_ASSERT( handle );
	return handle;
#else	// defined( _WIN32 )
#error Uncrecognised platform.  It appears Temper does not support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Temper/issues
#endif	// defined( _WIN32 )
}

//----------------------------------------------------------

static void* TemperGetProcAddressInternal( void* handle, const char* funcName ) {
	TEMPER_ASSERT( handle );
	TEMPER_ASSERT( funcName );

	void* proc = NULL;

#ifdef _WIN32
	proc = (void*) GetProcAddress( (HMODULE) handle, funcName );
#elif defined( __APPLE__ ) || defined( __linux__ )	// defined( _WIN32 )
	proc = dlsym( handle, funcName );
#else	// defined( _WIN32 )
#error Uncrecognised platform.  It appears Temper does not support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Temper/issues
#endif	// defined( _WIN32 )

	if ( !proc ) {
		const char* platformErrorMsg = "";
#if defined( __APPLE__ ) || defined( __linux__ )
		platformErrorMsg =
			"\n"
			"On MacOS and Linux you need to explicitly allow dynamic symbol exporting via your compiler options.\n"
			"E.G.: Using \"--export-dynamic\" or some other variant.\n";
#endif

		g_temperTestContext.callbacks.LogError( "Failed to find function \"%s\".%s\n", funcName, platformErrorMsg );
	}

	return proc;
}

//----------------------------------------------------------

static void TemperUnloadEXEHandleInternal( void* handle ) {
	TEMPER_ASSERT( handle );

#if defined( _WIN32 )
	FreeLibrary( (HMODULE) handle );
	handle = NULL;
#elif defined( __APPLE__ ) || defined( __linux__ )	// _WIN32
	int closeError = dlclose( handle );
	if ( closeError ) {
		g_temperTestContext.callbacks.LogError( "%s.\n", dlerror() );
	}

	handle = NULL;
#else	// _WIN32
#error Uncrecognised platform.  It appears Temper does not support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Temper/issues
#endif	// _WIN32
}

//----------------------------------------------------------

static bool TemperGetFullEXEPathInternal( void ) {
#if defined( _WIN32 )
	DWORD fullExePathLength = GetModuleFileName( NULL, g_temperTestContext.programName, MAX_PATH );
	if ( fullExePathLength == 0 ) {
		g_temperTestContext.callbacks.LogError( "WinAPI call GetModuleFileName() failed: 0x%lX\n", GetLastError() );
		return false;
	}

	g_temperTestContext.programName[fullExePathLength] = 0;
#elif defined( __linux__ )	// defined( _WIN32 )
	int err = 0;

	const char* exeFilenameVirtual = "/proc/self/exe";

	struct stat exeFileInfo;
	if ( lstat( exeFilenameVirtual, &exeFileInfo ) == -1 ) {
		err = errno;
		g_temperTestContext.callbacks.LogError( "lstat() failed: %s.\n", strerror( err ) );
		return false;
	}

	ssize_t fullExePathLength = readlink( exeFilenameVirtual, g_temperTestContext.programName, (size_t) exeFileInfo.st_size + 1 );
	err = errno;
	if ( fullExePathLength == -1 ) {
		g_temperTestContext.callbacks.LogError( "readlink() failed: %s.\n", strerror( err ) );
		return false;
	}

	g_temperTestContext.programName[exeFileInfo.st_size] = 0;
#elif defined( __APPLE__ )	// defined( _WIN32 )
	int err = 0;

	uint32_t bufsize = TEMPER_MAX_PATH;

	if ( _NSGetExecutablePath( g_temperTestContext.programName, &bufsize ) != 0 ) {
		err = errno;
		g_temperTestContext.callbacks.LogError( "_NSGetExecutablePath() failed: %s.\n", strerror( err ) );
		return false;
	}

	g_temperTestContext.programName[bufsize] = 0;
#else	// defined( _WIN32 )
#error Uncrecognised platform.  It appears Temper does not support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Temper/issues
#endif	// defined( _WIN32 )

	return true;
}

//----------------------------------------------------------

#if defined( _WIN32 )
typedef unsigned long	temperThreadHandle_t;
#elif defined( __APPLE__ ) || defined( __linux__ )	// defined( _WIN32 )
typedef void*			temperThreadHandle_t;
#else	// defined( _WIN32 )
#error Uncrecognised platform.  It appears Temper does not support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Temper/issues
#endif	// defined( _WIN32 )

// its ok to write directly to the global because only one test thread runs at a time
// if multiple test threads were running asynchronously then probably want to atomic increment at the very end of the test thread
static temperThreadHandle_t TemperThreadProcInternal( void* data ) {
	TEMPER_ASSERT( data );

	temperSuiteTestInfo_t* information = (temperSuiteTestInfo_t*) data;
	TEMPER_ASSERT( information );

	g_temperTestContext.currentTestStartTime = g_temperTestContext.callbacks.GetTimestamp();
	information->Callback();
	g_temperTestContext.currentTestEndTime = g_temperTestContext.callbacks.GetTimestamp();

	return 0;
}

//----------------------------------------------------------

static void TemperRunTestThreadInternal( temperSuiteTestInfo_t* information ) {
	TEMPER_ASSERT( information );

#if defined( _WIN32 )
	HANDLE testThread = CreateThread( NULL, 0, TemperThreadProcInternal, information, 0, NULL );
	TEMPER_ASSERT( testThread );

	DWORD result = WaitForMultipleObjects( 1, &testThread, TRUE, UINT32_MAX );
	TEMPER_ASSERT( result == WAIT_OBJECT_0 );

	DWORD exitCode = (DWORD) -1;
	BOOL gotExitCode = GetExitCodeThread( testThread, &exitCode );
	TEMPER_ASSERT( gotExitCode );

	CloseHandle( testThread );
	testThread = NULL;
#elif defined( __APPLE__ ) || ( __linux__ )	// defined( _WIN32 )
	int err = 0;

	pthread_t thread;
	pthread_attr_t threadAttribs;
	pthread_attr_init( &threadAttribs );
	if ( pthread_create( &thread, &threadAttribs, TemperThreadProcInternal, information ) != 0 ) {
		err = errno;
		g_temperTestContext.callbacks.LogError( "Failed to create test thread: %s.\n", strerror( err ) );
		return;
	}

	void* exitCode;
	if ( pthread_join( thread, &exitCode ) != 0 ) {
		err = errno;
		g_temperTestContext.callbacks.LogError( "Failed to wait for test thread to finish: %s.\n", strerror( err ) );
		return;
	}
#else	// defined( _WIN32 )
#error Uncrecognised platform.  It appears Temper does not support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Temper/issues
#endif	// defined( _WIN32 )
}

//----------------------------------------------------------

static const char* TemperGetTimeUnitStringInternal( void ) {
	switch ( g_temperTestContext.timeUnit ) {
		case TEMPER_TIME_UNIT_CLOCKS:	return "clocks";
		case TEMPER_TIME_UNIT_NS:		return "nanoseconds";
		case TEMPER_TIME_UNIT_US:		return "microseconds";
		case TEMPER_TIME_UNIT_MS:		return "milliseconds";
		case TEMPER_TIME_UNIT_SECONDS:	return "seconds";

		default:
			TEMPER_ASSERT( false && "Temper test context time unit was invalid somehow!?" );
			return NULL;
	}
}

//----------------------------------------------------------

static void TemperOnBeforeTestInternal( const temperSuiteTestInfo_t* information ) {
	TEMPER_ASSERT( information );

	if ( g_temperTestContext.suiteFilterPrevious && information->suiteNameStr ) {
		if ( !g_temperTestContext.callbacks.StringEquals( g_temperTestContext.suiteFilterPrevious, information->suiteNameStr ) ) {
			g_temperTestContext.callbacks.Log( "------------------------------------------------------------\n\n" );
			g_temperTestContext.suiteFilterPrevious = information->suiteNameStr;
		}
	}

	if ( information->suiteNameStr ) {
		g_temperTestContext.callbacks.Log( "TEST \t- \"%s\" : \"%s\"\n", information->suiteNameStr, information->testNameStr );
	} else {
		g_temperTestContext.callbacks.Log( "TEST \t- \"%s\"\n", information->testNameStr );
	}
}

//----------------------------------------------------------

static void TemperOnAfterTestInternal( const temperSuiteTestInfo_t* information ) {
	TEMPER_ASSERT( information );

	if ( information->testingFlag == TEMPER_TEST_FLAG_SHOULD_RUN ) {
		const char* timeUnitStr = TemperGetTimeUnitStringInternal();

		if ( g_temperTestContext.currentTestWasAborted ) {
			TemperSetTextColorInternal( TEMPER_COLOR_RED );
			g_temperTestContext.callbacks.Log( "=== TEST ABORTED (%.3f %s) ===\n\n", g_temperTestContext.currentTestEndTime - g_temperTestContext.currentTestStartTime, timeUnitStr );
			TemperSetTextColorInternal( TEMPER_COLOR_DEFAULT );
		} else if ( g_temperTestContext.currentTestErrorCount > 0 ) {
			TemperSetTextColorInternal( TEMPER_COLOR_RED );
			g_temperTestContext.callbacks.Log( "TEST FAILED (%.3f %s)\n\n", g_temperTestContext.currentTestEndTime - g_temperTestContext.currentTestStartTime, timeUnitStr );
			TemperSetTextColorInternal( TEMPER_COLOR_DEFAULT );
		} else {
			TemperSetTextColorInternal( TEMPER_COLOR_GREEN );
			g_temperTestContext.callbacks.Log( "TEST SUCCEEDED (%.3f %s)\n\n", g_temperTestContext.currentTestEndTime - g_temperTestContext.currentTestStartTime, timeUnitStr );
			TemperSetTextColorInternal( TEMPER_COLOR_DEFAULT );
		}
	} else {
		const char* skipReason = information->testingFlag == TEMPER_TEST_FLAG_DEPRECATED ? "DEPRECATED" : "SHOULD_SKIP";
		TemperSetTextColorInternal( TEMPER_COLOR_YELLOW );
		g_temperTestContext.callbacks.Log( "TEST FLAGGED \"%s\"\n\n", skipReason );
		TemperSetTextColorInternal( TEMPER_COLOR_DEFAULT );
	}
}

//----------------------------------------------------------

static void TemperAbortTestOnFailInternal( const bool abortOnFail ) {
	if ( abortOnFail ) {
		g_temperTestContext.currentTestEndTime = g_temperTestContext.callbacks.GetTimestamp();
		g_temperTestContext.testsAborted += 1;
		g_temperTestContext.currentTestWasAborted = true;

		TEMPER_EXIT_TEST_THREAD_INTERNAL();
	}
}

//----------------------------------------------------------

static void TemperTestTrueInternal( const bool condition, const char* conditionStr, const bool abortOnFail, const char* message, const char* file, const uint32_t line ) {
	if ( !( condition ) ) {
		g_temperTestContext.currentTestErrorCount += 1;

		// DM: could probably make this user-overridable
		{
			const char* newLine = NULL;
			const char* actualMessage = NULL;

			if ( message ) {
				actualMessage = message;
				newLine = "\n";
			} else {
				actualMessage = "";
				newLine = "";
			}

			TemperSetTextColorInternal( TEMPER_COLOR_RED );
			g_temperTestContext.callbacks.Log( "FAILED: " );
			TemperSetTextColorInternal( TEMPER_COLOR_YELLOW );
			g_temperTestContext.callbacks.Log( "%s at %s line %d.\n%s%s", conditionStr, file, line, actualMessage, newLine );
			TemperSetTextColorInternal( TEMPER_COLOR_DEFAULT );
		}

		TemperAbortTestOnFailInternal( abortOnFail );
	}
}

//----------------------------------------------------------

static void TemperOnAllTestsFinishedInternal( void ) {
	g_temperTestContext.callbacks.Log(
		"------------------------------------------------------------\n"
		"\n"
		"\n=== ALL TESTS FINISHED ===\n"
		"Total time taken: %.3f %s\n"
		"Total tests defined: %d\n"
		, g_temperTestContext.totalExecutionTime, TemperGetTimeUnitStringInternal()
		, g_temperTestContext.totalTestsDeclared
	);

	if ( g_temperTestContext.suiteFilter || g_temperTestContext.testFilter ) {
		g_temperTestContext.callbacks.Log( "\t- Total tests matching filters: %d\n\t- Suite filter: %s\n\t- Test filter: %s\n\t- Partial results %s\n",
				g_temperTestContext.totalTestsFoundWithFilters,
				g_temperTestContext.suiteFilter,
				g_temperTestContext.testFilter,
				g_temperTestContext.partialFilter ? "PERMITTED" : "DISCARDED" );
	}

	uint32_t totalFound = g_temperTestContext.totalTestsFoundWithFilters;
	g_temperTestContext.callbacks.Log(
		"Passed:   %d ( %d%% )\n"
		"Failed:   %d ( %d%% )\n"
		"Aborted:  %d ( %d%% )\n"
		"Skipped:  %d ( %d%% )\n",
		g_temperTestContext.testsPassed,  TemperGetPercentInternal( g_temperTestContext.testsPassed,  totalFound ),
		g_temperTestContext.testsFailed,  TemperGetPercentInternal( g_temperTestContext.testsFailed,  totalFound ),
		g_temperTestContext.testsAborted, TemperGetPercentInternal( g_temperTestContext.testsAborted, totalFound ),
		g_temperTestContext.testsSkipped, TemperGetPercentInternal( g_temperTestContext.testsSkipped, totalFound )
	);
}

//----------------------------------------------------------

// MY: I'd like to eventually add more security around this,
// such as ensuring it's only ever called/used once and thowing
// an error if it isn't. Maybe also (SOMEHOW) ensuring no test
// ever has a higher count.
static void TemperSetupInternal( void ) {
	// for any callbacks that werent overridden just set the default internal implementation
	{
		if ( !g_temperTestContext.callbacks.Log )					g_temperTestContext.callbacks.Log = TemperLogInternal;
		if ( !g_temperTestContext.callbacks.LogWarning )			g_temperTestContext.callbacks.LogWarning = TemperLogWarningInternal;
		if ( !g_temperTestContext.callbacks.LogError )				g_temperTestContext.callbacks.LogError = TemperLogErrorInternal;
		if ( !g_temperTestContext.callbacks.StringEquals )			g_temperTestContext.callbacks.StringEquals = TemperStringEqualsInternal;
		if ( !g_temperTestContext.callbacks.StringContains )		g_temperTestContext.callbacks.StringContains = TemperStringContainsInternal;
		if ( !g_temperTestContext.callbacks.GetProcAddress )		g_temperTestContext.callbacks.GetProcAddress = TemperGetProcAddressInternal;
		if ( !g_temperTestContext.callbacks.OnBeforeTest )			g_temperTestContext.callbacks.OnBeforeTest = TemperOnBeforeTestInternal;
		if ( !g_temperTestContext.callbacks.RunTestThread )			g_temperTestContext.callbacks.RunTestThread = TemperRunTestThreadInternal;
		if ( !g_temperTestContext.callbacks.FloatEquals )			g_temperTestContext.callbacks.FloatEquals = TemperFloatEqualsInternal;
		if ( !g_temperTestContext.callbacks.GetTimestamp )			g_temperTestContext.callbacks.GetTimestamp = TemperGetTimestampInternal;
		if ( !g_temperTestContext.callbacks.OnAfterTest )			g_temperTestContext.callbacks.OnAfterTest = TemperOnAfterTestInternal;
		if ( !g_temperTestContext.callbacks.OnAllTestsFinished )	g_temperTestContext.callbacks.OnAllTestsFinished = TemperOnAllTestsFinishedInternal;
		if ( !g_temperTestContext.callbacks.LoadEXEHandle )			g_temperTestContext.callbacks.LoadEXEHandle = TemperLoadEXEHandleInternal;
		if ( !g_temperTestContext.callbacks.UnloadEXEHandle )		g_temperTestContext.callbacks.UnloadEXEHandle = TemperUnloadEXEHandleInternal;
	}

#ifdef _WIN32
	QueryPerformanceFrequency( &g_temperTestContext.timestampFrequency );
#endif

	g_temperTestContext.currentTestStartTime = 0.0;
	g_temperTestContext.currentTestEndTime = 0.0;
	g_temperTestContext.totalExecutionTime = 0.0;
	g_temperTestContext.testsPassed = 0;
	g_temperTestContext.testsFailed = 0;
	g_temperTestContext.testsAborted = 0;
	g_temperTestContext.testsSkipped = 0;
	g_temperTestContext.totalTestsFoundWithFilters = 0;
	g_temperTestContext.totalTestsExecuted = 0;
	g_temperTestContext.currentTestErrorCount = 0;
	g_temperTestContext.currentTestWasAborted = false;
	g_temperTestContext.partialFilter = false;
	g_temperTestContext.timeUnit = TEMPER_TIME_UNIT_US;
	g_temperTestContext.suiteFilterPrevious = NULL;
	g_temperTestContext.suiteFilter = NULL;
	g_temperTestContext.testFilter = NULL;
}

//----------------------------------------------------------

static bool TemperIsSuiteFilteredInternal( const char* suiteName ) {
	if ( !g_temperTestContext.suiteFilter ) {
		return true;
	}

	if ( !suiteName ) {
		return false;
	}

	if ( g_temperTestContext.partialFilter ) {
		return g_temperTestContext.callbacks.StringContains( suiteName, g_temperTestContext.suiteFilter );
	} else {
		return g_temperTestContext.callbacks.StringEquals( suiteName, g_temperTestContext.suiteFilter );
	}
}

//----------------------------------------------------------

static bool TemperIsTestFilteredInternal( const char* testName ) {
	if ( !g_temperTestContext.testFilter ) {
		return true;
	}

	if ( !testName ) {
		return false;
	}

	if ( g_temperTestContext.partialFilter ) {
		return g_temperTestContext.callbacks.StringContains( testName, g_temperTestContext.testFilter );
	} else {
		return g_temperTestContext.callbacks.StringEquals( testName, g_temperTestContext.testFilter );
	}
}

//----------------------------------------------------------

static int TemperExecuteAllTestsInternal() {
	if ( !TemperGetFullEXEPathInternal() ) {
		return TEMPER_EXIT_FAILURE;
	}

	// make the exe load itself
	void* handle = g_temperTestContext.callbacks.LoadEXEHandle();

	// DM: I have never seen a function name exceed 64 characters, let alone 1024
	// so this shouldn't be a problem
	char testFuncName[1024];

	double start = g_temperTestContext.callbacks.GetTimestamp();

	for ( uint32_t i = 0; i < g_temperTestContext.totalTestsDeclared; i++ ) {
		TEMPER_SNPRINTF( testFuncName, 1024, "temper_test_info_fetcher_%d", i );

		// get the test grabber function out of the binary
		temperTestInfoFetcherFunc_t funcInfoGrabber = (temperTestInfoFetcherFunc_t) g_temperTestContext.callbacks.GetProcAddress( handle, testFuncName );

		if ( !funcInfoGrabber ) {
			return TEMPER_EXIT_FAILURE;
		}

		temperSuiteTestInfo_t information = funcInfoGrabber();

		// check if whether the suite/test passed the filter first before checking if the run flag was set
		// otherwise the test could be marked as run/skip but still pass the filter and it would never show in the output
		// TODO(DM): profile doing a loop like this with branching vs. adding everything that passes the filter first to a list of things to run
		// we care only about raw execution time in that test and whether or not the initial pass was faster than just running the loop with branching
		if ( TemperIsSuiteFilteredInternal( information.suiteNameStr ) ) {
			if ( TemperIsTestFilteredInternal( information.testNameStr ) ) {
				g_temperTestContext.totalTestsFoundWithFilters += 1;

				g_temperTestContext.callbacks.OnBeforeTest( &information );

				if ( information.testingFlag == TEMPER_TEST_FLAG_SHOULD_RUN ) {
					g_temperTestContext.currentTestErrorCount = 0;
					g_temperTestContext.currentTestWasAborted = false;

					g_temperTestContext.callbacks.RunTestThread( &information );

					information.testTimeTaken = g_temperTestContext.currentTestEndTime - g_temperTestContext.currentTestStartTime;

					g_temperTestContext.totalTestsExecuted += 1;

#ifndef TEMPER_SELF_TEST_ENABLED
					if ( g_temperTestContext.currentTestErrorCount > 0 ) {
						g_temperTestContext.testsFailed += 1;
					} else {
						g_temperTestContext.testsPassed += 1;
					}
#else
					temperBool32 expectedToAbort = ( information.expectationFlags & TEMPER_TEST_EXPECTATION_FLAG_ABORT );

					if ( ( expectedToAbort && g_temperTestContext.currentTestWasAborted ) ||
						 ( ( information.expectationFlags & TEMPER_TEST_EXPECTATION_FLAG_FAIL ) && g_temperTestContext.currentTestErrorCount > 0 ) ) {
						g_temperTestContext.testsPassed += 1;

						// we only care about un-exected aborts / failures
						g_temperTestContext.testsAborted -= ( expectedToAbort && g_temperTestContext.currentTestWasAborted ) ? 1 : 0;
						g_temperTestContext.currentTestErrorCount = 0;
						g_temperTestContext.currentTestWasAborted = false;
					} else if ( g_temperTestContext.currentTestErrorCount == 0 ) {
						g_temperTestContext.testsPassed += 1;
					} else {
						g_temperTestContext.testsFailed += 1;
					}
#endif //TEMPER_SELF_TEST_ENABLED
				} else {
					g_temperTestContext.testsSkipped += 1;
				}

				g_temperTestContext.callbacks.OnAfterTest( &information );
			}
		}
	}

	double end = g_temperTestContext.callbacks.GetTimestamp();
	g_temperTestContext.totalExecutionTime = end - start;

	g_temperTestContext.callbacks.OnAllTestsFinished();

	// cleanup
	g_temperTestContext.callbacks.UnloadEXEHandle( handle );

	return g_temperTestContext.testsFailed == 0 ? TEMPER_EXIT_SUCCESS : TEMPER_EXIT_FAILURE;
}

//----------------------------------------------------------

static int TemperExecuteAllTestsWithArgumentsInternal( int argc, char** argv ) {
	if ( !TemperHandleCommandLineArgumentsInternal( argc, argv ) ) {
		return TEMPER_EXIT_FAILURE;
	}

	return TemperExecuteAllTestsInternal();
}

//----------------------------------------------------------

#if defined( __linux__ ) || defined( __APPLE__ )
#pragma pop_macro( "_POSIX_C_SOURCE" )
#endif

#if defined( __clang__ )
#pragma clang diagnostic pop
#elif defined( __GNUC__ )
#pragma GCC diagnostic pop
#elif defined( _MSC_VER )
#pragma warning( pop )
#endif // defined( __GNUC__ ) || defined( __clang__ )

#ifdef __cplusplus
}
#endif
