#define TEMPER_UTIL_SELF_TEST_ENABLED // This is for testing temper only. Please don't add this in your production environment

#include "../../temper.h"

//----------------------------------------------------------

TEMPER_TEST(GivenIsolatedTest_WhenDeclared_IsExecuted, TEMPER_UTIL_EXPECT_SUCCESS, TEMPER_FLAG_SHOULD_RUN)
{
	TEMPER_CHECK_TRUE(true);
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredButHasError_IsExecutedAndFails, TEMPER_UTIL_EXPECT_FAIL, TEMPER_FLAG_SHOULD_RUN )
{
	TEMPER_CHECK_TRUE_M( false, "We expect this test to fail." );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredButWillAbort_IsExecutedAndAborts, TEMPER_UTIL_EXPECT_ABORT, TEMPER_FLAG_SHOULD_RUN )
{
	TEMPER_CHECK_TRUE_AM( false, "We expect this test to abort." );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredWithErrorAndAbort_IsExecutedFailsAndAborts, TEMPER_UTIL_EXPECT_FAIL | TEMPER_UTIL_EXPECT_ABORT, TEMPER_FLAG_SHOULD_RUN )
{
	TEMPER_CHECK_TRUE_M(false, "this failure is expected");
	TEMPER_CHECK_TRUE_AM( false, "We expect this test to abort." );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredWithSkipFlag_IsNotExecuted, TEMPER_UTIL_EXPECT_SUCCESS, TEMPER_FLAG_SHOULD_SKIP )
{
	TEMPER_CHECK_TRUE_M( false, "The 'skip' flag is broken. This should NOT have run!" );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredWithDeprecatedFlag_IsNotExecuted, TEMPER_UTIL_EXPECT_SUCCESS, TEMPER_FLAG_DEPRECATED )
{
	TEMPER_CHECK_TRUE_M( false, "The 'deprecated' flag is broken. This should NOT have run!" );
}

//----------------------------------------------------------

int main( int argc, char** argv )
{
	TEMPER_SETUP();
	int exitCode = TEMPER_RUN_ALL_TESTS_WITH_ARGS( argc, argv );
	printf( "\nAutomation returned: %d.\n", exitCode );
	getchar();
	return exitCode;
}

//----------------------------------------------------------