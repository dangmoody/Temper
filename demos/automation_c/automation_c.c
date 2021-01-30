#include "../../temper.h"
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"

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

static uint32_t capturedPassCount = 0;
static uint32_t capturedFailCount = 0;
static uint32_t capturedAbortCount = 0;
static uint32_t capturedSkipCount = 0;

//----------------------------------------------------------

static void CaptureTestCounts( void ) {
	capturedPassCount = g_temperTestContext.testsPassed;
	capturedFailCount = g_temperTestContext.testsFailed;
	capturedAbortCount = g_temperTestContext.testsAborted;
	capturedSkipCount = g_temperTestContext.testsSkipped;
}

//----------------------------------------------------------

static void ClearTestCounts( void ) {
	g_temperTestContext.testsPassed = 0;
	g_temperTestContext.testsFailed = 0;
	g_temperTestContext.testsAborted = 0;
	g_temperTestContext.testsSkipped = 0;
}

//----------------------------------------------------------

static void RestoreCapturedTestCounts( void ) {
	g_temperTestContext.testsPassed = capturedPassCount;
	g_temperTestContext.testsFailed = capturedFailCount;
	g_temperTestContext.testsAborted = capturedAbortCount;
	g_temperTestContext.testsSkipped = capturedSkipCount;
}

//----------------------------------------------------------

static bool AssertResults( uint32_t passDiff, uint32_t failDiff, uint32_t abortDiff, uint32_t skipDiff ) {
	TEMPER_CHECK_EQUAL_M( g_temperTestContext.testsPassed, ( capturedPassCount + passDiff ), "The passed test counter is not as expected: %d, %d\n", g_temperTestContext.testsPassed, capturedPassCount + passDiff );
	TEMPER_CHECK_EQUAL_M( g_temperTestContext.testsFailed, ( capturedFailCount + failDiff ), "The failed test counter is not as expected: %d, %d\n", g_temperTestContext.testsFailed, capturedFailCount + failDiff );
	TEMPER_CHECK_EQUAL_M( g_temperTestContext.testsAborted, ( capturedAbortCount + abortDiff ), "The aborted test counter is not as expected: %d, %d\n", g_temperTestContext.testsAborted, capturedAbortCount + abortDiff );
	TEMPER_CHECK_EQUAL_M( g_temperTestContext.testsSkipped, ( capturedSkipCount + skipDiff ), "The skipped test counter is not as expected: %d, %d\n", g_temperTestContext.testsSkipped, capturedSkipCount + skipDiff );

	return g_temperTestContext.currentTestErrorCount == 0;
}

//----------------------------------------------------------

//static bool AssertTestCounts( uint32_t errorCount ) {
//	TEMPER_CHECK_EQUAL_M( g_temperTestContext.currentTestErrorCount, errorCount, "this test has not produced the expected number of errors." );
//	return g_temperTestContext.currentTestErrorCount == 0;
//}

//----------------------------------------------------------

static void AbsolveTest( const bool condition ) {
	if ( condition ) {
		g_temperTestContext.currentTestErrorCount = 0;

		TemperSetTextColorInternal( TEMPERDEV__COLOR_GREEN );
		TEMPERDEV__LOG( "Current test absolved.\n" );
		TemperSetTextColorInternal( TEMPERDEV__COLOR_DEFAULT );
	}
}

//----------------------------------------------------------

static void AbsolvePreviousTest( const AutomationAccountFor_t claim ) {
	TemperSetTextColorInternal( TEMPERDEV__COLOR_GREEN );

	if ( claim == ACCOUNT_FOR_ONE_FAILURE ) {
		TEMPERDEV__ASSERT( g_temperTestContext.testsFailed > 0 );
		g_temperTestContext.testsPassed += 1;
		g_temperTestContext.testsFailed -= 1;
		TEMPERDEV__LOG( "Absolved previous fail.\n" );
	} else if ( claim == ACCOUNT_FOR_ONE_ABORT ) {
		TEMPERDEV__ASSERT( g_temperTestContext.testsFailed > 0 );
		TEMPERDEV__ASSERT( g_temperTestContext.testsAborted > 0 );
		g_temperTestContext.testsPassed += 1;
		g_temperTestContext.testsFailed -= 1;
		g_temperTestContext.testsAborted -= 1;
		TEMPERDEV__LOG( "Absolved previous abort.\n" );
	} else if ( claim == ACCOUNT_FOR_ONE_SKIP ) {
		TEMPERDEV__ASSERT( g_temperTestContext.testsSkipped > 0 );
		g_temperTestContext.testsPassed += 1;
		g_temperTestContext.testsSkipped -= 1;
		TEMPERDEV__LOG( "Absolved previous skip.\n" );
	}

	TemperSetTextColorInternal( TEMPERDEV__COLOR_DEFAULT );
}

//----------------------------------------------------------

static void PassOrFailTest(const bool AllowPass, const char* message) {
	if( AllowPass ) {
		AbsolveTest( true );
	} else {
		g_temperTestContext.currentTestErrorCount += 1;
		TEMPERDEV__LOG_ERROR( message );
	}
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
// EXCEL_TestName - When a test is marked as "Deprecated" it doesn't run
// &
// EXCEL_TestName - If a test is flagged with Deprecated, total tests skipped increments
//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WithDeprecatedFlag_TriggersSkipCount, TEMPER_FLAG_DEPRECATED ) {
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

	TEMPER_CHECK_TRUE_M( 5 == 7 && 8 + 2 == 11, "We expect this test to fail." );
	TEMPER_CHECK_TRUE_M( 5 == 5 && 8 + 2 == 11, "We expect this test to fail." );
	TEMPER_CHECK_TRUE_M( 5 == 5 && 8 + 2 == 10, "We expect this test to fail." );
	countIsCorrect = g_temperTestContext.currentTestErrorCount == 3 ? countIsCorrect : false;

	AbsolveTest( countIsCorrect );
}

//----------------------------------------------------------
// EXCEL_TestName - If a test triggered any errors, total tests failed increments
//----------------------------------------------------------

RESULT_DEPENDANT_TEST( GivenCheck_WhenErrorTriggered_FailsTest, TEMPER_FLAG_SHOULD_RUN ) {
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

RESULT_DEPENDANT_TEST( GivenICheck_WhenAbortTriggered_AbortsTest, TEMPER_FLAG_SHOULD_RUN ) {
	TEMPER_CHECK_TRUE_AM( false, "We expect this test to abort." );
	TEMPER_CHECK_TRUE_M( false, "We shouldn't hit this. Asserted in the CheckAndClean." );
}

TEMPER_TEST( CheckAndCleanResults_4, TEMPER_FLAG_SHOULD_RUN ) {
	if ( AssertResults( 0, 1, 1, 0 ) ) {
		AbsolvePreviousTest( ACCOUNT_FOR_ONE_ABORT );
	}
}

//----------------------------------------------------------
// EXCEL_TestName - When Temper has NO errors or aborts, the proposed error code is SUCCESS
//----------------------------------------------------------

TEMPER_TEST( GivenNoFailuresOrAborts_WhenExitCodeCalculated_ProvidesSuccessCode, TEMPER_FLAG_SHOULD_RUN ) {
	CaptureTestCounts();
	ClearTestCounts();
	TEMPER_CHECK_EQUAL_M( TEMPERDEV__EXIT_SUCCESS, TemperCalculateExitCode(), "Expected the success code to be returned for no errors & no aborts" );
	RestoreCapturedTestCounts();
}

//----------------------------------------------------------
// EXCEL_TestName - When temper has one or more errors and no aborts, the proposed error code is FAIL
//----------------------------------------------------------

TEMPER_TEST( GivenFailures_WhenExitCodeCalculated_ProvidesFailureCode, TEMPER_FLAG_SHOULD_RUN ) {
	CaptureTestCounts();
	ClearTestCounts();
	g_temperTestContext.testsFailed = 1;
	TEMPER_CHECK_EQUAL_M( TEMPERDEV__EXIT_FAILURE, TemperCalculateExitCode(), "Expected the failure code to be returned for there being errors" );
	RestoreCapturedTestCounts();
}

//----------------------------------------------------------
// EXCEL_TestName - When temper has one or more aborts and no errors, the proposed error code is FAIL
//----------------------------------------------------------

TEMPER_TEST( GivenAborts_WhenExitCodeCalculated_ProvidesFailureCode, TEMPER_FLAG_SHOULD_RUN ) {
	CaptureTestCounts();
	ClearTestCounts();
	g_temperTestContext.testsAborted = 1;
	TEMPER_CHECK_EQUAL_M( TEMPERDEV__EXIT_FAILURE, TemperCalculateExitCode(), "Expected the failure code to be returned for there being aborts" );
	RestoreCapturedTestCounts();
}

//----------------------------------------------------------
// CONDITION TEST TOOLS
//----------------------------------------------------------

#define CONDITION_TEST(testName) TEMPER_SUITE_TEST(ConditionTests, testName, TEMPER_FLAG_SHOULD_RUN)

//----------------------------------------------------------
// > CHECK TRUE
//----------------------------------------------------------

CONDITION_TEST( CheckTrue_GivenFalse_ErrorCountIncrements ) {
	bool errorCountCoorect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_TRUE( false );
	errorCountCoorect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCoorect : false;
	PassOrFailTest( errorCountCoorect, "Should have incremented the error count to 1.\n" );
}

CONDITION_TEST( CheckTrue_GivenTrue_ErrorCountStays ) {
	bool errorCountCoorect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_TRUE( true );
	errorCountCoorect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCoorect : false;
	PassOrFailTest( errorCountCoorect, "Shouldn't have incremented the error count.\n" );
}

CONDITION_TEST( CheckTrue_GivenLongFalseStatement_ErrorCountIncrements ) {
	bool errorCountCoorect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_TRUE( ( ( 2 * 8 ) / 4 ) == 4 && 7 - 7 );
	errorCountCoorect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCoorect : false;
	PassOrFailTest( errorCountCoorect, "Should have incremented the error count to 1.\n" );
}

CONDITION_TEST( CheckTrue_GivenLongTrueStatement_ErrorCountStays ) {
	bool errorCountCoorect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_TRUE( ( ( 2 * 8 ) / 4 ) == 4 && 7 - 6 );
	errorCountCoorect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCoorect : false;
	PassOrFailTest( errorCountCoorect, "Shouldn't have incremented the error count.\n" );
}

//----------------------------------------------------------
// > CHECK FALSE
//----------------------------------------------------------

CONDITION_TEST( CheckFalse_GivenFalse_ErrorCountStays ) {
	bool errorCountCoorect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_FALSE( false );
	errorCountCoorect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCoorect : false;
	PassOrFailTest( errorCountCoorect, "Shouldn't have incremented the error count.\n" );
}

CONDITION_TEST( CheckFalse_GivenTrue_ErrorCountIncrements ) {
	bool errorCountCoorect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_FALSE( true );
	errorCountCoorect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCoorect : false;
	PassOrFailTest( errorCountCoorect, "Should have incremented the error count to 1.\n" );
}

CONDITION_TEST( CheckFalse_GivenLongFalseStatement_ErrorCountStays ) {
	bool errorCountCoorect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_FALSE( ( ( 2 * 8 ) / 4 ) == 4 && 7 - 7 );
	errorCountCoorect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCoorect : false;
	PassOrFailTest( errorCountCoorect, "Shouldn't have incremented the error count.\n" );
}

CONDITION_TEST( CheckFalse_GivenLongTrueStatement_ErrorCountIncrements ) {
	bool errorCountCoorect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_FALSE( ( ( 2 * 8 ) / 4 ) == 4 && 7 - 6 );
	errorCountCoorect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCoorect : false;
	PassOrFailTest( errorCountCoorect, "Should have incremented the error count to 1.\n" );
}

//----------------------------------------------------------
// > CHECK EQUAL
//----------------------------------------------------------



//----------------------------------------------------------
// > CHECK FLOAT EQUAL
//----------------------------------------------------------



//----------------------------------------------------------
// > CHECK ALMOST EQUAL
//----------------------------------------------------------



//----------------------------------------------------------
// > CHECK NOT ALMOST EQUAL
//----------------------------------------------------------



//----------------------------------------------------------

int main( int argc, char** argv ) {
	TEMPER_RUN( argc, argv );
	int exitCode = TEMPER_GET_EXIT_CODE();
	printf( "\nAutomation returned: %d.\n", exitCode );
	getchar();
	return exitCode;
}

//----------------------------------------------------------