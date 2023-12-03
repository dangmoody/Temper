#define TEMPER_IMPLEMENTATION
#define TEMPER_CUSTOM_TEST_PRIORITY
#define TEMPER_DEFAULT_TEST_PRIORITY AUTOMATION_TEST_PRIORITY_NORMAL
#include "../../temper.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#pragma clang diagnostic ignored "-Wpadded"
#endif

//----------------------------------------------------------

// If a test is expected to fail or abort in a certain way, we will remidy the failure
// in the CheckAndCleanResults_N test which will run after as Temper runs based on declaration
// order

//----------------------------------------------------------

typedef enum automationTestPriority_t {
	AUTOMATION_TEST_PRIORITY_HIGH	= 0,
	AUTOMATION_TEST_PRIORITY_NORMAL,
	AUTOMATION_TEST_PRIORITY_LOW,
} automationTestPriority_t;

//----------------------------------------------------------

typedef enum automationAccountFor_t {
	ACCOUNT_FOR_ONE_FAILURE = 0,
	ACCOUNT_FOR_ONE_ABORT,
	ACCOUNT_FOR_ONE_SKIP,
	ACCOUNT_FOR_QUIT_ATTEMPT
} automationAccountFor_t;

//----------------------------------------------------------

static uint32_t capturedPassCount = 0;
static uint32_t capturedFailCount = 0;
static uint32_t capturedAbortCount = 0;
static uint32_t capturedSkipCount = 0;
static uint32_t capturedQuitCount = 0;

static uint32_t numHighPriorityTestsRun = 0;
static uint32_t numNormalPriorityTestsRun = 0;
static uint32_t numLowPriorityTestsRun = 0;

//----------------------------------------------------------

#define THE_ABORT_TEST_FAILURE_NUMBER 1
static uint32_t testAbortTestNumberWeNeverExpectSet = 0;

//----------------------------------------------------------

static void DumpInfo(const char* prefix) {
	printf( "INFO_DUMP(%s): pass = %d/%d, fail = %d/%d, abort = %d/%d, quit = %d/%d\nskip = %d/%d\n",
			prefix,
			capturedPassCount, g_temperTestContext.testsPassed,
			capturedFailCount, g_temperTestContext.testsFailed,
			capturedAbortCount, g_temperTestContext.testsAborted,
			capturedQuitCount, g_temperTestContext.testsQuit,
			capturedSkipCount, g_temperTestContext.testsSkipped );
}

//----------------------------------------------------------

static void CaptureTestCounts( void ) {
	capturedPassCount = g_temperTestContext.testsPassed;
	capturedFailCount = g_temperTestContext.testsFailed;
	capturedAbortCount = g_temperTestContext.testsAborted;
	capturedQuitCount = g_temperTestContext.testsQuit;
	capturedSkipCount = g_temperTestContext.testsSkipped;
	DumpInfo( "CaptureCounts" );
}

//----------------------------------------------------------

static void ClearTestCounts( void ) {
	g_temperTestContext.testsPassed = 0;
	g_temperTestContext.testsFailed = 0;
	g_temperTestContext.testsAborted = 0;
	g_temperTestContext.testsQuit = 0;
	g_temperTestContext.testsSkipped = 0;
}

//----------------------------------------------------------

static void RestoreCapturedTestCounts( void ) {
	g_temperTestContext.testsPassed = capturedPassCount;
	g_temperTestContext.testsFailed = capturedFailCount;
	g_temperTestContext.testsAborted = capturedAbortCount;
	g_temperTestContext.testsQuit = capturedQuitCount;
	g_temperTestContext.testsSkipped = capturedSkipCount;
}

//----------------------------------------------------------

static bool AssertResults( uint32_t passDiff, uint32_t failDiff, uint32_t abortDiff, uint32_t quitDiff, uint32_t skipDiff ) {
	TEMPER_CHECK_EQUAL_M( g_temperTestContext.testsPassed,  ( capturedPassCount + passDiff ),   "The passed test counter is not as expected: (Temper recorded: %d, tests recorded: %d)\n",  g_temperTestContext.testsPassed,  capturedPassCount + passDiff   );
	TEMPER_CHECK_EQUAL_M( g_temperTestContext.testsFailed,  ( capturedFailCount + failDiff ),   "The failed test counter is not as expected: (Temper recorded: %d, tests recorded: %d)\n",  g_temperTestContext.testsFailed,  capturedFailCount + failDiff   );
	TEMPER_CHECK_EQUAL_M( g_temperTestContext.testsAborted, ( capturedAbortCount + abortDiff ), "The aborted test counter is not as expected: (Temper recorded: %d, tests recorded: %d)\n", g_temperTestContext.testsAborted, capturedAbortCount + abortDiff );
	TEMPER_CHECK_EQUAL_M( g_temperTestContext.testsQuit,    ( capturedQuitCount + quitDiff ),   "The aborted test counter is not as expected: (Temper recorded: %d, tests recorded: %d)\n", g_temperTestContext.testsQuit,    capturedQuitCount + abortDiff  );
	TEMPER_CHECK_EQUAL_M( g_temperTestContext.testsSkipped, ( capturedSkipCount + skipDiff ),   "The skipped test counter is not as expected: (Temper recorded: %d, tests recorded: %d)\n", g_temperTestContext.testsSkipped, capturedSkipCount + skipDiff   );

	return g_temperTestContext.currentTestErrorCount == 0;
}

//----------------------------------------------------------

static void AbsolveTest( const bool condition ) {
	if ( condition ) {
		g_temperTestContext.currentTestErrorCount = 0;

		TemperSetTextColorInternal( TEMPERDEV_COLOR_GREEN );
		g_temperTestContext.callbacks.Log( stdout, "Current test absolved.\n" );
		TemperSetTextColorInternal( TEMPERDEV_COLOR_DEFAULT );
	}
}

//----------------------------------------------------------

static void AbsolvePreviousTest( const automationAccountFor_t claim ) {
	TemperSetTextColorInternal( TEMPERDEV_COLOR_GREEN );

	if ( claim == ACCOUNT_FOR_ONE_FAILURE ) {
		TEMPERDEV_ASSERT( g_temperTestContext.testsFailed > 0 );
		g_temperTestContext.testsPassed += 1;
		g_temperTestContext.testsFailed -= 1;
		g_temperTestContext.callbacks.Log( stdout, "Absolved previous fail." );
	} else if ( claim == ACCOUNT_FOR_ONE_ABORT ) {
		TEMPERDEV_ASSERT( g_temperTestContext.testsFailed > 0 );
		TEMPERDEV_ASSERT( g_temperTestContext.testsAborted > 0 );
		g_temperTestContext.testsPassed += 1;
		g_temperTestContext.testsFailed -= 1;
		g_temperTestContext.testsAborted -= 1;
		g_temperTestContext.callbacks.Log( stdout, "Absolved previous abort." );
	} else if ( claim == ACCOUNT_FOR_ONE_SKIP ) {
		TEMPERDEV_ASSERT( g_temperTestContext.testsSkipped > 0 );
		g_temperTestContext.testsPassed += 1;
		g_temperTestContext.testsSkipped -= 1;
		g_temperTestContext.callbacks.Log( stdout, "Absolved previous skip." );
	}else if ( claim == ACCOUNT_FOR_QUIT_ATTEMPT ) {
		TEMPERDEV_ASSERT( g_temperTestContext.testsFailed > 0 );
		TEMPERDEV_ASSERT( g_temperTestContext.testsAborted > 0 );
		TEMPERDEV_ASSERT( g_temperTestContext.testsQuit > 0 );
		g_temperTestContext.testsPassed += 1;
		g_temperTestContext.testsFailed -= 1;
		g_temperTestContext.testsAborted -= 1;
		g_temperTestContext.testsQuit -= 1;
		g_temperTestContext.callbacks.Log( stdout, "Absolved quit.\n" );
	}

	TemperSetTextColorInternal( TEMPERDEV_COLOR_DEFAULT );
}

//----------------------------------------------------------

static void PassOrFailTest(const bool AllowPass, const char* message) {
	if( AllowPass ) {
		AbsolveTest( true );
	} else {
		g_temperTestContext.currentTestErrorCount += 1;
		g_temperTestContext.callbacks.LogError( message );
	}
}


//----------------------------------------------------------

#define RESULT_DEPENDANT_TEST( name, flag )				TEMPER_TEST_C( name, CaptureTestCounts, NULL, flag )
#define CONDITION_TEST( testName )						TEMPER_TEST_SUITE( ConditionTests, testName, TEMPER_FLAG_SHOULD_RUN )
#define RESULT_DEPDENDANT_TEST_PARAMETRIC( name, ... )	TEMPER_TEST_PARAMETRIC_C( name, CaptureTestCounts, NULL, TEMPER_FLAG_SHOULD_RUN, __VA_ARGS__ )

//----------------------------------------------------------
// EXCEL_TestName - When a test is marked as "Should Run" it runs
//----------------------------------------------------------

RESULT_DEPENDANT_TEST( IsolatedTest_WhenDeclared_IsExecuted, TEMPER_FLAG_SHOULD_RUN ) {
	TEMPER_CHECK_TRUE( true );
}

TEMPER_TEST( CheckAndCleanResults_0, TEMPER_FLAG_SHOULD_RUN ) {
	AssertResults( 1, 0, 0, 0, 0 );
}

//----------------------------------------------------------
// EXCEL_TestName - When a test is marked as "Should Skip" it doesn't run
// &
// EXCEL_TestName - If a test is flagged with Skip, total tests skipped increments
//----------------------------------------------------------

TEMPER_TEST( IsolatedTest_WithSkipFlag_TriggersSkipCount, TEMPER_FLAG_SHOULD_SKIP ) {
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

TEMPER_TEST( IsolatedTest_WithDeprecatedFlag_TriggersSkipCount, TEMPER_FLAG_DEPRECATED ) {
	TEMPER_CHECK_TRUE_AM( false, "This test shouldn't have executed, it's flagged as Deprecated." );
}

TEMPER_TEST( CheckAndCleanResults_2, TEMPER_FLAG_SHOULD_RUN ) {
	if ( g_temperTestContext.testsSkipped == 1 ) {
		AbsolvePreviousTest( ACCOUNT_FOR_ONE_SKIP );
	}
}

//----------------------------------------------------------
// EXCEL_TestName - When a parametric test is marked as "Should Run" then all invokes run
//----------------------------------------------------------

RESULT_DEPDENDANT_TEST_PARAMETRIC( ParametricTest_WithRunFlag_IsExecuted, const bool check ) {
	TEMPER_CHECK_TRUE( check );
}

TEMPER_INVOKE_PARAMETRIC_TEST( ParametricTest_WithRunFlag_IsExecuted, true );

TEMPER_TEST( CheckAndCleanResults_3, TEMPER_FLAG_SHOULD_RUN ) {
	AssertResults( 1, 0, 0, 0, 0 );
}

//----------------------------------------------------------
// EXCEL_TestName - When a parametric test is marked as "Deprecated" then all invokes are skipped
// &
// EXCEL_TestName - When a parametric test is marked as "Should skip" then all invokes are skipped
//----------------------------------------------------------

TEMPER_TEST_PARAMETRIC( ParametricTest_WithDeprecatedFlag_TriggersSkipCount, TEMPER_FLAG_DEPRECATED, const bool check ) {
	TEMPER_CHECK_TRUE_AM( check, "This test shouldn't have executed, it's flagged as Deprecated." );
}

TEMPER_INVOKE_PARAMETRIC_TEST( ParametricTest_WithDeprecatedFlag_TriggersSkipCount, false );

TEMPER_TEST( CheckAndCleanResults_4, TEMPER_FLAG_SHOULD_RUN ) {
	if ( g_temperTestContext.testsSkipped == 1 ) {
		AbsolvePreviousTest( ACCOUNT_FOR_ONE_SKIP );
	}
}

TEMPER_TEST_PARAMETRIC( ParametricTest_WithSkipFlag_TriggersSkipCount, TEMPER_FLAG_SHOULD_SKIP, const bool check ) {
	TEMPER_CHECK_TRUE_AM( check, "This test shouldn't have executed, it's flagged as Skipped." );
}

TEMPER_INVOKE_PARAMETRIC_TEST( ParametricTest_WithSkipFlag_TriggersSkipCount, false );

TEMPER_TEST( CheckAndCleanResults_5, TEMPER_FLAG_SHOULD_RUN ) {
	if ( g_temperTestContext.testsSkipped == 1 ) {
		AbsolvePreviousTest( ACCOUNT_FOR_ONE_SKIP );
	}
}

//----------------------------------------------------------
// EXCEL_TestName - Paramatric tests can accept structs and classes as parms
//----------------------------------------------------------

// int deliberately comes after the string because I want to test if Temper can deal with badly-packed data structures
typedef struct person_t {
	const char*	name;
	uint32_t	age;
} person_t;

TEMPER_TEST_PARAMETRIC( ParametricTest_WhenDeclaredWithStructParm_StructParmIsValid, TEMPER_FLAG_SHOULD_RUN, person_t* person, const char* expectedName, const uint32_t expectedAge ) {
	// general data validation
	TEMPER_CHECK_TRUE_AM( person != NULL, "person ptr is NULL." );
	TEMPER_CHECK_TRUE_AM( person->name != NULL, "person->name ptr inside \"%s\" is NULL." );

	// actual comparing what was passed in vs what was expected
	TEMPER_CHECK_TRUE_AM( strcmp( person->name, expectedName ) == 0, "person->name was expected to be \"%s\" but was actually \"%s\".\n", expectedName, person->name );
	TEMPER_CHECK_TRUE_AM( person->age == expectedAge, "person->age was expected to be \"%d\" but was actually \"%d\".\n", expectedAge, person->age );
}

TEMPER_INVOKE_PARAMETRIC_TEST( ParametricTest_WhenDeclaredWithStructParm_StructParmIsValid, &(person_t) { "Dan",     25  }, "Dan",     25  );
TEMPER_INVOKE_PARAMETRIC_TEST( ParametricTest_WhenDeclaredWithStructParm_StructParmIsValid, &(person_t) { "Mike",    25  }, "Mike",    25  );
TEMPER_INVOKE_PARAMETRIC_TEST( ParametricTest_WhenDeclaredWithStructParm_StructParmIsValid, &(person_t) { "Bilbo",   111 }, "Bilbo",   111 );
TEMPER_INVOKE_PARAMETRIC_TEST( ParametricTest_WhenDeclaredWithStructParm_StructParmIsValid, &(person_t) { "Aragorn", 87  }, "Aragorn", 87  );

//----------------------------------------------------------
// EXCEL_TestName - When a test triggers any errors it increments the error count for the test correctly
//----------------------------------------------------------

TEMPER_TEST( CheckTrue_WhenFails_ErrorCountIncrements, TEMPER_FLAG_SHOULD_RUN ) {
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

RESULT_DEPENDANT_TEST( TemperCheck_WhenErrorTriggered_FailsTest, TEMPER_FLAG_SHOULD_RUN ) {
	TEMPER_CHECK_TRUE_M( false, "We expect this test to fail." );
}

TEMPER_TEST( CheckAndCleanResults_6, TEMPER_FLAG_SHOULD_RUN ) {
	if ( AssertResults( 0, 1, 0, 0, 0 ) ) {
		AbsolvePreviousTest( ACCOUNT_FOR_ONE_FAILURE );
	}
}

//----------------------------------------------------------
// EXCEL_TestName - If a test triggered an aborts, total tests aborted increments
//----------------------------------------------------------

RESULT_DEPENDANT_TEST( CheckTrue_WhenAbortTriggered_AbortsTest, TEMPER_FLAG_SHOULD_RUN ) {
	TEMPER_CHECK_TRUE_AM( false, "We expect this test to abort." );
	testAbortTestNumberWeNeverExpectSet = THE_ABORT_TEST_FAILURE_NUMBER;
}

TEMPER_TEST( CheckAndCleanResults_7, TEMPER_FLAG_SHOULD_RUN ) {
	if ( AssertResults( 0, 1, 1, 0, 0 ) ) {
		AbsolvePreviousTest( ACCOUNT_FOR_ONE_ABORT );
	}

	TEMPER_CHECK_NOT_EQUAL_M(testAbortTestNumberWeNeverExpectSet, THE_ABORT_TEST_FAILURE_NUMBER, "Aborts in tests do not kill threads as the failure number was set.");
	testAbortTestNumberWeNeverExpectSet = 0;
}

RESULT_DEPDENDANT_TEST_PARAMETRIC( CheckTrue_WhenAbortTriggered_AbortsParametricTest, const bool check ) {
	TEMPER_CHECK_TRUE_AM( check, "We expect this test to abort." );
	testAbortTestNumberWeNeverExpectSet = THE_ABORT_TEST_FAILURE_NUMBER;
}

TEMPER_INVOKE_PARAMETRIC_TEST( CheckTrue_WhenAbortTriggered_AbortsParametricTest, false );

TEMPER_TEST( CheckAndCleanResults_8, TEMPER_FLAG_SHOULD_RUN ) {
	if( AssertResults( 0, 1, 1, 0, 0 ) ) {
		AbsolvePreviousTest( ACCOUNT_FOR_ONE_ABORT );
	}

	TEMPER_CHECK_NOT_EQUAL_M(testAbortTestNumberWeNeverExpectSet, THE_ABORT_TEST_FAILURE_NUMBER, "Aborts in parameteric tests do not kill threads as the failure number was set.");
	testAbortTestNumberWeNeverExpectSet = 0;
}

//----------------------------------------------------------
// EXCEL_TestName - When Temper has NO errors or aborts, the proposed error code is SUCCESS
//----------------------------------------------------------

TEMPER_TEST( NoFailuresOrAborts_WhenExitCodeCalculated_ProvidesSuccessCode, TEMPER_FLAG_SHOULD_RUN ) {
	CaptureTestCounts();
	ClearTestCounts();
	TEMPER_CHECK_EQUAL_M( TEMPERDEV_EXIT_SUCCESS, TemperCalculateExitCode(), "Expected the success code to be returned for no errors & no aborts" );
	RestoreCapturedTestCounts();
}

//----------------------------------------------------------
// EXCEL_TestName - When temper has one or more errors and no aborts, the proposed error code is FAIL
//----------------------------------------------------------

TEMPER_TEST( Failures_WhenExitCodeCalculated_ProvidesFailureCode, TEMPER_FLAG_SHOULD_RUN ) {
	CaptureTestCounts();
	ClearTestCounts();
	g_temperTestContext.testsFailed = 1;
	TEMPER_CHECK_EQUAL_M( TEMPERDEV_EXIT_FAILURE, TemperCalculateExitCode(), "Expected the failure code to be returned for there being errors" );
	RestoreCapturedTestCounts();
}

//----------------------------------------------------------
// EXCEL_TestName - When temper has one or more aborts and no errors, the proposed error code is FAIL
//----------------------------------------------------------

TEMPER_TEST( Aborts_WhenExitCodeCalculated_ProvidesFailureCode, TEMPER_FLAG_SHOULD_RUN ) {
	CaptureTestCounts();
	ClearTestCounts();
	g_temperTestContext.testsAborted = 1;
	TEMPER_CHECK_EQUAL_M( TEMPERDEV_EXIT_FAILURE, TemperCalculateExitCode(), "Expected the failure code to be returned for there being aborts" );
	RestoreCapturedTestCounts();
}

//----------------------------------------------------------
// > PRIORITY TESTS - make sure these are not defined in order (both in the file and between each other) so as to actually test we can reorder them
//----------------------------------------------------------

TEMPER_TEST_P( TestPriority_HighBeforeMediumAndLow, TEMPER_FLAG_SHOULD_RUN, AUTOMATION_TEST_PRIORITY_HIGH ) {
	TEMPER_CHECK_TRUE( numHighPriorityTestsRun == 0 );	// test hasnt finished yet so cound should still be 0
	TEMPER_CHECK_TRUE( numNormalPriorityTestsRun == 0 );
	TEMPER_CHECK_TRUE( numLowPriorityTestsRun == 0 );

	numHighPriorityTestsRun += 1;
}

TEMPER_TEST_P( TestPriority_MediumBeforeLowAndAfterHigh, TEMPER_FLAG_SHOULD_RUN, AUTOMATION_TEST_PRIORITY_NORMAL ) {
	TEMPER_CHECK_TRUE( numHighPriorityTestsRun == 1 );
	TEMPER_CHECK_TRUE( numNormalPriorityTestsRun == 0 );	// test hasnt finished yet so cound should still be 0
	TEMPER_CHECK_TRUE( numLowPriorityTestsRun == 0 );

	numNormalPriorityTestsRun += 1;
}

TEMPER_TEST_P( TestPriority_LowAfterMediumAndHigh, TEMPER_FLAG_SHOULD_RUN, AUTOMATION_TEST_PRIORITY_LOW ) {
	TEMPER_CHECK_TRUE( numHighPriorityTestsRun == 1 );
	TEMPER_CHECK_TRUE( numNormalPriorityTestsRun == 1 );
	TEMPER_CHECK_TRUE( numLowPriorityTestsRun == 0 );	// test hasnt finished yet so cound should still be 0

	numLowPriorityTestsRun += 1;
}

//----------------------------------------------------------
// > QUIT TESTS
//----------------------------------------------------------

RESULT_DEPENDANT_TEST( CheckTrue_WhenQuitTriggered_QuitInvokedAndAbortsTest, TEMPER_FLAG_SHOULD_RUN ) {
	g_temperTestContext.negateQuitAttempts = true;
	TEMPER_CHECK_TRUE_QM(false, "Expected error 3 - We expect this test to quit now.\n");
	testAbortTestNumberWeNeverExpectSet = THE_ABORT_TEST_FAILURE_NUMBER;
}

TEMPER_TEST( CheckAndCleanResults_9, TEMPER_FLAG_SHOULD_RUN ) {
	g_temperTestContext.negateQuitAttempts = false; // we do not quit ourselves within this test but if we fail to absolve we will want the quit status of the previous test to fall through and end the run.
	if ( AssertResults( 0, 1, 1, 1, 0 ) ) {
		AbsolvePreviousTest( ACCOUNT_FOR_QUIT_ATTEMPT );
	}

	TEMPER_CHECK_NOT_EQUAL_M(testAbortTestNumberWeNeverExpectSet, THE_ABORT_TEST_FAILURE_NUMBER, "Quits do not trigger aborts as the failure number was set.");
	testAbortTestNumberWeNeverExpectSet = 0;
}

RESULT_DEPDENDANT_TEST_PARAMETRIC( CheckTrue_WhenQuitTriggered_QuitInvokedAndAbortsParametricTest, const bool check ) {
	g_temperTestContext.negateQuitAttempts = true;
	TEMPER_CHECK_TRUE_QM( check, "We expect this test to quit." );
	testAbortTestNumberWeNeverExpectSet = THE_ABORT_TEST_FAILURE_NUMBER;
}

TEMPER_INVOKE_PARAMETRIC_TEST( CheckTrue_WhenQuitTriggered_QuitInvokedAndAbortsParametricTest, false );

TEMPER_TEST( CheckAndCleanResults_10, TEMPER_FLAG_SHOULD_RUN ) {
	g_temperTestContext.negateQuitAttempts = false; // we do not quit ourselves within this test but if we fail to absolve we will want the quit status of the previous test to fall through and end the run.
	if( AssertResults( 0, 1, 1, 1, 0 ) ) {
		AbsolvePreviousTest( ACCOUNT_FOR_QUIT_ATTEMPT );
	}

	TEMPER_CHECK_NOT_EQUAL_M(testAbortTestNumberWeNeverExpectSet, THE_ABORT_TEST_FAILURE_NUMBER, "Aborts in parameteric tests do not kill threads as the failure number was set.");
	testAbortTestNumberWeNeverExpectSet = 0;
}

//----------------------------------------------------------
// > CHECK TRUE
//----------------------------------------------------------

CONDITION_TEST( CheckTrue_FalseParsed_ErrorCountIncrements ) {
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_TRUE( false );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 1." );
}

CONDITION_TEST( CheckTrue_TrueParsed_ErrorCountStays ) {
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_TRUE( true );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Shouldn't have incremented the error count." );
}

CONDITION_TEST( CheckTrue_LongFalseStatementParsed_ErrorCountIncrements ) {
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_TRUE( ( ( 2 * 8 ) / 4 ) == 4 && 7 - 7 );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 1." );
}

CONDITION_TEST( CheckTrue_LongTrueStatementParsed_ErrorCountStays ) {
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_TRUE( ( ( 2 * 8 ) / 4 ) == 4 && 7 - 6 );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Shouldn't have incremented the error count." );
}

//----------------------------------------------------------
// > CHECK FALSE
//----------------------------------------------------------

CONDITION_TEST( CheckFalse_FalseParsed_ErrorCountStays ) {
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_FALSE( false );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Shouldn't have incremented the error count." );
}

CONDITION_TEST( CheckFalse_TrueParsed_ErrorCountIncrements ) {
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_FALSE( true );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 1." );
}

CONDITION_TEST( CheckFalse_LongFalseStatementParsed_ErrorCountStays ) {
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_FALSE( ( ( 2 * 8 ) / 4 ) == 4 && 7 - 7 );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Shouldn't have incremented the error count." );
}

CONDITION_TEST( CheckFalse_LongTrueStatementParsed_ErrorCountIncrements ) {
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_FALSE( ( ( 2 * 8 ) / 4 ) == 4 && 7 - 6 );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 1." );
}

//----------------------------------------------------------
// > CHECK EQUAL
//----------------------------------------------------------

CONDITION_TEST( CheckEqual_WhenTwoValuesAreEqual_ErrorCountStays ) {
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_EQUAL( 8, 8 );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Shouldn't have incremented the error count." );
}

CONDITION_TEST( CheckFalse_WhenTwoValuesAreNotEqual_ErrorCountIncrements ) {
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_EQUAL( 4, 8 );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 1." );
}

//----------------------------------------------------------
// > CHECK FLOAT EQUAL
//----------------------------------------------------------

CONDITION_TEST( CheckFloatEqual_ValuesAroundUpperLowerBoundaries_ErrorCountIncrementsWhenExpected ) {
	const float lhs = 5.0f;
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_FLOAT_EQUAL( lhs, 5.0f );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	TEMPER_CHECK_FLOAT_EQUAL( lhs, 5.000001f );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	TEMPER_CHECK_FLOAT_EQUAL( lhs, 5.000002f );		// Above upper threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	TEMPER_CHECK_FLOAT_EQUAL( lhs, 4.999999f );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	TEMPER_CHECK_FLOAT_EQUAL( lhs, 4.999992f );		// Below lower threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 2 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 2." );
}

//----------------------------------------------------------
// > CHECK NOT FLOAT EQUAL
//----------------------------------------------------------

CONDITION_TEST( CheckNotFloatEqual_ValuesAroundUpperLowerBoundaries_ErrorCountIncrementsWhenExpected ) {
	const float lhs = 5.0f;
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_NOT_FLOAT_EQUAL( lhs, 5.0f );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	TEMPER_CHECK_NOT_FLOAT_EQUAL( lhs, 5.000001f );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 2 ? errorCountCorrect : false;
	TEMPER_CHECK_NOT_FLOAT_EQUAL( lhs, 5.000002f );		// Above upper threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 2 ? errorCountCorrect : false;
	TEMPER_CHECK_NOT_FLOAT_EQUAL( lhs, 4.999999f );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 3 ? errorCountCorrect : false;
	TEMPER_CHECK_NOT_FLOAT_EQUAL( lhs, 4.999992f );		// Below lower threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 3 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 2." );
}

//----------------------------------------------------------
// > CHECK FLOAT_S EQUAL
//----------------------------------------------------------

CONDITION_TEST( CheckFloatSEqual_ValuesAroundUpperLowerBoundaries_ErrorCountIncrementsWhenExpected ) {
	const float lhs = 5.0f;
	const float epsilon = 7.5f;
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_FLOAT_WITHIN_RANGE( lhs, 5.0f, epsilon );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	TEMPER_CHECK_FLOAT_WITHIN_RANGE( lhs, 12.5f, epsilon );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	TEMPER_CHECK_FLOAT_WITHIN_RANGE( lhs, 12.6f, epsilon );		// Above upper threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	TEMPER_CHECK_FLOAT_WITHIN_RANGE( lhs, -2.5f, epsilon );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	TEMPER_CHECK_FLOAT_WITHIN_RANGE( lhs, -2.6f, epsilon );		// Below lower threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 2 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 2." );
}

//----------------------------------------------------------
// > CHECK NOT FLOAT_S EQUAL
//----------------------------------------------------------

CONDITION_TEST( CheckNotFloatSEqual_ValuesAroundUpperLowerBoundaries_ErrorCountIncrementsWhenExpected ) {
	const float lhs = 5.0f;
	const float epsilon = 7.5f;
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_FLOAT_NOT_WITHIN_RANGE( lhs, 5.0f, epsilon );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	TEMPER_CHECK_FLOAT_NOT_WITHIN_RANGE( lhs, 12.5f, epsilon );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 2 ? errorCountCorrect : false;
	TEMPER_CHECK_FLOAT_NOT_WITHIN_RANGE( lhs, 12.6f, epsilon );		// Above upper threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 2 ? errorCountCorrect : false;
	TEMPER_CHECK_FLOAT_NOT_WITHIN_RANGE( lhs, -2.5f, epsilon );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 3 ? errorCountCorrect : false;
	TEMPER_CHECK_FLOAT_NOT_WITHIN_RANGE( lhs, -2.6f, epsilon );		// Below lower threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 3 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 3." );
}

//----------------------------------------------------------
// > CHECK DOUBLE EQUAL
//----------------------------------------------------------

CONDITION_TEST( CheckDoubleEqual_ValuesAroundUpperLowerBoundaries_ErrorCountIncrementsWhenExpected ) {
	const double lhs = 5.0;
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_DOUBLE_EQUAL( lhs, 5.0 );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	TEMPER_CHECK_DOUBLE_EQUAL( lhs, 5.00000000000001 );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	TEMPER_CHECK_DOUBLE_EQUAL( lhs, 5.00000000000002 );		// Above upper threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	TEMPER_CHECK_DOUBLE_EQUAL( lhs, 4.99999999999999 );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	TEMPER_CHECK_DOUBLE_EQUAL( lhs, 4.99999999999992 );		// Below lower threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 2 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 2." );
}

//----------------------------------------------------------
// > CHECK NOT DOUBLE EQUAL
//----------------------------------------------------------

CONDITION_TEST( CheckNotDoubleEqual_ValuesAroundUpperLowerBoundaries_ErrorCountIncrementsWhenExpected ) {
	const double lhs = 5.0;
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_NOT_DOUBLE_EQUAL( lhs, 5.0 );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	TEMPER_CHECK_NOT_DOUBLE_EQUAL( lhs, 5.00000000000001 );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 2 ? errorCountCorrect : false;
	TEMPER_CHECK_NOT_DOUBLE_EQUAL( lhs, 5.00000000000002 );		// Above upper threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 2 ? errorCountCorrect : false;
	TEMPER_CHECK_NOT_DOUBLE_EQUAL( lhs, 4.99999999999999 );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 3 ? errorCountCorrect : false;
	TEMPER_CHECK_NOT_DOUBLE_EQUAL( lhs, 4.99999999999992 );		// Below lower threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 3 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 2." );
}

//----------------------------------------------------------
// > CHECK DOUBLE_S EQUAL
//----------------------------------------------------------

CONDITION_TEST( CheckDoubleSEqual_ValuesAroundUpperLowerBoundaries_ErrorCountIncrementsWhenExpected ) {
	const double lhs = 5.0;
	const double epsilon = 7.5;
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_DOUBLE_WITHIN_RANGE( lhs, 5.0, epsilon );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	TEMPER_CHECK_DOUBLE_WITHIN_RANGE( lhs, 12.5, epsilon );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? errorCountCorrect : false;
	TEMPER_CHECK_DOUBLE_WITHIN_RANGE( lhs, 12.6, epsilon );		// Above upper threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	TEMPER_CHECK_DOUBLE_WITHIN_RANGE( lhs, -2.5, epsilon );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	TEMPER_CHECK_DOUBLE_WITHIN_RANGE( lhs, -2.6, epsilon );		// Below lower threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 2 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 2." );
}

//----------------------------------------------------------
// > CHECK NOT DOUBLE_S EQUAL
//----------------------------------------------------------

CONDITION_TEST( CheckNotDoubleSEqual_ValuesAroundUpperLowerBoundaries_ErrorCountIncrementsWhenExpected ) {
	const double lhs = 5.0;
	const double epsilon = 7.5;
	bool errorCountCorrect = g_temperTestContext.currentTestErrorCount == 0 ? true : false;
	TEMPER_CHECK_DOUBLE_NOT_WITHIN_RANGE( lhs, 5.0, epsilon );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 1 ? errorCountCorrect : false;
	TEMPER_CHECK_DOUBLE_NOT_WITHIN_RANGE( lhs, 12.5, epsilon );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 2 ? errorCountCorrect : false;
	TEMPER_CHECK_DOUBLE_NOT_WITHIN_RANGE( lhs, 12.6, epsilon );		// Above upper threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 2 ? errorCountCorrect : false;
	TEMPER_CHECK_DOUBLE_NOT_WITHIN_RANGE( lhs, -2.5, epsilon );
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 3 ? errorCountCorrect : false;
	TEMPER_CHECK_DOUBLE_NOT_WITHIN_RANGE( lhs, -2.6, epsilon );		// Below lower threshold
	errorCountCorrect = g_temperTestContext.currentTestErrorCount == 3 ? errorCountCorrect : false;
	PassOrFailTest( errorCountCorrect, "Should have incremented the error count to 3." );
}

//----------------------------------------------------------

#if defined( __clang__ )
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#endif

int main( int argc, char** argv ) {
	TEMPER_RUN( argc, argv );
	int exitCode = TEMPER_GET_EXIT_CODE();
	printf( "\nAutomation returned: %d.\n", exitCode );
	return exitCode;
}

#if defined( __clang__ )
#pragma clang diagnostic pop
#endif

//----------------------------------------------------------

#ifdef __clang__
#pragma clang diagnostic pop
#endif