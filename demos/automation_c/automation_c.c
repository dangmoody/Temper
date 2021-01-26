//#define TEMPER_ENABLE_SELF_TEST 1 // This is for testing temper only. Please don't add this in your production environment

#include "../../temper.h"

//----------------------------------------------------------

// If a test is expected to fail or abort in a certain way, we will remidy the failure
// in the CheckAndCleanResults_N test which will run after as Temper runs based on declaration
// order

//----------------------------------------------------------

typedef enum AutomationAccountFor_t {
	ACCOUNT_FOR_ONE_FAILURE = 0,
	ACCOUNT_FOR_ONE_ABORT,
	ACCOUNT_FOR_ONE_SKIP
} AutomationAccountFor_t;

//----------------------------------------------------------

static uint32_t CapturedPassCount = 0;
static uint32_t CapturedFailCount = 0;
static uint32_t CapturedAbortCount = 0;
static uint32_t CapturedSkipCount = 0;

//----------------------------------------------------------

static void CaptureTestCounts() {
	CapturedPassCount = g_temperTestContext.testsPassed;
	CapturedFailCount = g_temperTestContext.testsFailed;
	CapturedAbortCount = g_temperTestContext.testsAborted;
	CapturedSkipCount = g_temperTestContext.testsSkipped;
}

//----------------------------------------------------------

static bool AssertResults( uint32_t passDiff, uint32_t failDiff, uint32_t abortDiff, uint32_t skipDiff ) {
	// BUG - CONDITIONS SHOULD TAKE "const char* fmt, ..." - this is embarising.
	TEMPER_CHECK_EQUAL( g_temperTestContext.testsPassed, ( CapturedPassCount + passDiff ) );
	printf( "The passed test counter is not as expected: %d, %d\n", g_temperTestContext.testsPassed, CapturedPassCount + passDiff );
	TEMPER_CHECK_EQUAL( g_temperTestContext.testsFailed, ( CapturedFailCount + failDiff ) );
	printf( "The failed test counter is not as expected: %d, %d\n", g_temperTestContext.testsFailed, CapturedFailCount + failDiff );
	TEMPER_CHECK_EQUAL( g_temperTestContext.testsAborted, ( CapturedAbortCount + abortDiff ) );
	printf( "The aborted test counter is not as expected: %d, %d\n", g_temperTestContext.testsAborted, CapturedAbortCount + abortDiff );
	TEMPER_CHECK_EQUAL( g_temperTestContext.testsSkipped, ( CapturedSkipCount + skipDiff ) );
	printf( "The skipped test counter is not as expected: %d, %d\n", g_temperTestContext.testsSkipped, CapturedSkipCount + skipDiff );

	return g_temperTestContext.currentTestErrorCount == 0;
}

//----------------------------------------------------------

//	static bool AssertTestCounts( uint32_t errorCount ) {
//		TEMPER_CHECK_EQUAL_M( g_temperTestContext.currentTestErrorCount, errorCount, "this test has not produced the expected number of errors." );
//		return g_temperTestContext.currentTestErrorCount == 0;
//	}

//----------------------------------------------------------

static void AbsolveTest( const bool condition ) {
	if ( condition ) {
		g_temperTestContext.currentTestErrorCount = 0;

		TemperSetTextColorInternal( __TEMPER_COLOR_GREEN );
		__TEMPER_LOG( "Current test absolved\n" );
		TemperSetTextColorInternal( __TEMPER_COLOR_DEFAULT );
	}
}

//----------------------------------------------------------

static void AbsolvePreviousTest( const AutomationAccountFor_t claim ) {
	TemperSetTextColorInternal( __TEMPER_COLOR_GREEN );

	if ( claim == ACCOUNT_FOR_ONE_FAILURE ) {
		__TEMPER_ASSERT( g_temperTestContext.testsFailed > 0 );
		g_temperTestContext.testsPassed += 1;
		g_temperTestContext.testsFailed -= 1;
		__TEMPER_LOG( "Absolved previous fail\n" );
	}else if ( claim == ACCOUNT_FOR_ONE_ABORT ) {
		__TEMPER_ASSERT( g_temperTestContext.testsFailed > 0 );
		__TEMPER_ASSERT( g_temperTestContext.testsAborted > 0 );
		g_temperTestContext.testsPassed += 1;
		g_temperTestContext.testsFailed -= 1;
		g_temperTestContext.testsAborted -= 1;
		__TEMPER_LOG( "Absolved previous abort\n" );
	}else if ( claim == ACCOUNT_FOR_ONE_SKIP ) {
		__TEMPER_ASSERT( g_temperTestContext.testsSkipped > 0 );
		g_temperTestContext.testsPassed += 1;
		g_temperTestContext.testsSkipped -= 1;
		__TEMPER_LOG( "Absolved previous skip\n" );
	}

	TemperSetTextColorInternal( __TEMPER_COLOR_DEFAULT );
}

//----------------------------------------------------------

#define RESULT_DEPENDANT_TEST( name, flag ) TEMPER_TEST_C( name, CaptureTestCounts, NULL, flag )

//----------------------------------------------------------
// EXCEL_TestName - When a test is marked as "Should Run" it runs
//----------------------------------------------------------

RESULT_DEPENDANT_TEST( GivenIsolatedTest_WhenDeclared_IsExecuted, TEMPER_FLAG_SHOULD_RUN ) {
	TEMPER_CHECK_TRUE( true );
}

TEMPER_TEST( CheckAndCleanResults_0, TEMPER_FLAG_SHOULD_RUN ) {
	AssertResults( 1, 0, 0, 0 );
}

//----------------------------------------------------------
// EXCEL_TestName - When a test is marked as "Should Skip" it doesn't run
// &
// EXCEL_TestName - If a test is flagged with Skip, total tests skipped increments
//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WithSkipFlag_TriggersSkipCount, TEMPER_FLAG_SHOULD_SKIP ) {
	TEMPER_CHECK_TRUE_AM( false, "This test shouldn't have executed, it's flagged with Skip." );
}

TEMPER_TEST( CheckAndCleanResults_1, TEMPER_FLAG_SHOULD_RUN ) {
	if ( g_temperTestContext.testsSkipped == 1 ) {
		AbsolvePreviousTest( ACCOUNT_FOR_ONE_SKIP );
	}
}

//----------------------------------------------------------
// EXCEL_TestName - When a test is marked as "Depricated" it doesn't run
// &
// EXCEL_TestName - If a test is flagged with Deprecated, total tests skipped increments
//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WithDepricatedFlag_TriggersSkipCount, TEMPER_FLAG_DEPRECATED )
{
	TEMPER_CHECK_TRUE_AM( false, "This test shouldn't have executed, it's flagged as Deprecated." );
}

TEMPER_TEST( CheckAndCleanResults_2, TEMPER_FLAG_SHOULD_RUN ) {
	if ( g_temperTestContext.testsSkipped == 1 ) {
		AbsolvePreviousTest( ACCOUNT_FOR_ONE_SKIP );
	}
}

//----------------------------------------------------------
// EXCEL_TestName - When a test triggers any errors it increments the error count for the test correctly
//----------------------------------------------------------

TEMPER_TEST( GivenCheckTrue_WhenFails_ErrorCountIncrements, TEMPER_FLAG_SHOULD_RUN ) {
	bool countIsCorrect = true;
	TEMPER_CHECK_TRUE_M( false, "We expect this test to fail." );
	countIsCorrect = g_temperTestContext.currentTestErrorCount == 1 ? countIsCorrect : false;

	TEMPER_CHECK_TRUE_M( ( 5 == 7 ), "We expect this test to fail." );
	countIsCorrect = g_temperTestContext.currentTestErrorCount == 2 ? countIsCorrect : false;

	AbsolveTest( countIsCorrect );
}

//----------------------------------------------------------
// EXCEL_TestName - If a test triggered any errors, total tests failed increments
//----------------------------------------------------------

RESULT_DEPENDANT_TEST( GivenIsolatedTest_WhenDeclaredButHasError_IsExecutedAndFails, TEMPER_FLAG_SHOULD_RUN ) {
	TEMPER_CHECK_TRUE_M( false, "We expect this test to fail." );
}

TEMPER_TEST( CheckAndCleanResults_3, TEMPER_FLAG_SHOULD_RUN ) {
	if ( AssertResults( 0, 1, 0, 0 ) ) {
		AbsolvePreviousTest( ACCOUNT_FOR_ONE_FAILURE );
	}
}

//----------------------------------------------------------
// EXCEL_TestName - If a test triggered an aborts, total tests aborted increments
//----------------------------------------------------------

RESULT_DEPENDANT_TEST( GivenIsolatedTest_WhenDeclaredButWillAbort_IsExecutedAndAborts, TEMPER_FLAG_SHOULD_RUN ) {
	TEMPER_CHECK_TRUE_AM( false, "We expect this test to abort." );
}

TEMPER_TEST( CheckAndCleanResults_4, TEMPER_FLAG_SHOULD_RUN ) {
	if ( AssertResults( 0, 1, 1, 0 ) ) {
		AbsolvePreviousTest( ACCOUNT_FOR_ONE_ABORT );
	}
}

//----------------------------------------------------------

int main( int argc, char** argv ) {
	TEMPER_RUN( argc, argv );
	int exitCode = TEMPER_GET_EXIT_CODE();
	printf( "\nAutomation returned: %d.\n", exitCode );
	getchar();
	return exitCode;
}

//----------------------------------------------------------