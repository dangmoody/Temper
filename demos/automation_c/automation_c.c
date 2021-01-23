#define TEMPER_ENABLE_SELF_TEST 1 // This is for testing temper only. Please don't add this in your production environment

#include "../../temper.h"

//----------------------------------------------------------

TEMPER_TEST(GivenIsolatedTest_WhenDeclared_IsExecuted, __TEMPER_TEST_EXPECT_FLAG_SUCCESS, TEMPER_FLAG_SHOULD_RUN)
{
	TEMPER_CHECK_TRUE(true);
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredButHasError_IsExecutedAndFails, __TEMPER_TEST_EXPECT_FLAG_FAIL, TEMPER_FLAG_SHOULD_RUN )
{
	TEMPER_CHECK_TRUE_M( false, "We expect this test to fail." );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredButWillAbort_IsExecutedAndAborts, __TEMPER_TEST_EXPECT_FLAG_ABORT, TEMPER_FLAG_SHOULD_RUN )
{
	TEMPER_CHECK_TRUE_AM( false, "We expect this test to abort." );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredWithErrorAndAbort_IsExecutedFailsAndAborts, __TEMPER_TEST_EXPECT_FLAG_FAIL | __TEMPER_TEST_EXPECT_FLAG_ABORT, TEMPER_FLAG_SHOULD_RUN )
{
	TEMPER_CHECK_TRUE_M(false, "this failure is expected");
	TEMPER_CHECK_TRUE_AM( false, "We expect this test to abort." );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredWithSkipFlag_IsNotExecuted, __TEMPER_TEST_EXPECT_FLAG_SUCCESS, TEMPER_FLAG_SHOULD_SKIP )
{
	TEMPER_CHECK_TRUE_M( false, "The 'skip' flag is broken. This should NOT have run!" );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredWithDeprecatedFlag_IsNotExecuted, __TEMPER_TEST_EXPECT_FLAG_SUCCESS, TEMPER_FLAG_DEPRECATED )
{
	TEMPER_CHECK_TRUE_M( false, "The 'deprecated' flag is broken. This should NOT have run!" );
}

//----------------------------------------------------------

int main( int argc, char** argv )
{
	TEMPER_RUN( argc, argv );
	int exitCode = TEMPER_GET_EXIT_CODE();
	printf( "\nAutomation returned: %d.\n", exitCode );
	getchar();
	return exitCode;
}

//----------------------------------------------------------