// MY: TODO - should we leave this as is Dan or would you rather we added a compiler argument so it's even less explicitly documented
#define TEMPER_SELF_TEST_ENABLED

#include "../../temper.h"

//----------------------------------------------------------

TEMPER_TEST(GivenIsolatedTest_WhenDeclared_IsExecuted, TEMPER_TEST_EXPECTATION_NONE, TEMPER_TEST_FLAG_SHOULD_RUN)
{
	TEMPER_TEST_TRUE(true);
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredButHasError_IsExecutedAndFails, TEMPER_TEST_EXPECTATION_FLAG_FAIL, TEMPER_TEST_FLAG_SHOULD_RUN )
{
	TEMPER_TEST_TRUE_M( false, "We expect this test to fail." );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredButWillAbort_IsExecutedAndAborts, TEMPER_TEST_EXPECTATION_FLAG_ABORT, TEMPER_TEST_FLAG_SHOULD_RUN )
{
	TEMPER_TEST_TRUE_OR_ABORT_M( false, "We expect this test to abort." );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredWithErrorAndAbort_IsExecutedFailsAndAborts, TEMPER_TEST_EXPECTATION_FLAG_FAIL | TEMPER_TEST_EXPECTATION_FLAG_ABORT, TEMPER_TEST_FLAG_SHOULD_RUN )
{
	TEMPER_TEST_TRUE_M(false, "this failure is expected");
	TEMPER_TEST_TRUE_OR_ABORT_M( false, "We expect this test to abort." );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredWithSkipFlag_IsNotExecuted, TEMPER_TEST_EXPECTATION_FLAG_FAIL, TEMPER_TEST_FLAG_SHOULD_SKIP )
{
	TEMPER_TEST_TRUE_M( false, "The 'skip' flag is broken. This should NOT have run!" );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredWithDepricatedFlag_IsNotExecuted, TEMPER_TEST_EXPECTATION_FLAG_FAIL, TEMPER_TEST_FLAG_DEPRECATED )
{
	TEMPER_TEST_TRUE_M( false, "The 'depricated' flag is broken. This should NOT have run!" );
}

//----------------------------------------------------------

int main( int argc, char** argv )
{
	TEMPER_SETUP();
	int returnValue = TEMPER_RUN_ALL_TESTS_WITH_ARGS( argc, argv );
	getchar();
	return returnValue;
}

//----------------------------------------------------------