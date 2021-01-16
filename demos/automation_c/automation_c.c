// MY: TODO - should we leave this as is Dan or would you rather we added a compiler argument so it's even less explicitly documented
#define TEMPER_SELF_TEST_ENABLED

#include "../../temper.h"

//----------------------------------------------------------

TEMPER_TEST(GivenIsolatedTest_WhenDeclared_IsExecuted, false, false, TEMPER_TEST_FLAG_SHOULD_RUN)
{
	TEMPER_TEST_TRUE(true);
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredButHasError_IsExecutedAndFails, true, false, TEMPER_TEST_FLAG_SHOULD_RUN )
{
	TEMPER_TEST_TRUE_M( false, "We expect this test to fail." );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredButWillAbort_IsExecutedAndAborts, false, true, TEMPER_TEST_FLAG_SHOULD_RUN )
{
	TEMPER_TEST_TRUE_OR_ABORT_M( false, "We expect this test to abort." );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredWithErrorAndAbort_IsExecutedFailsAndAborts, true, true, TEMPER_TEST_FLAG_SHOULD_RUN )
{
	TEMPER_TEST_TRUE_M(false, "this failure is expected");
	TEMPER_TEST_TRUE_OR_ABORT_M( false, "We expect this test to abort." );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredWithSkipFlag_IsNotExecuted, false, false, TEMPER_TEST_FLAG_SHOULD_SKIP )
{
	TEMPER_TEST_TRUE_M( false, "The 'skip' flag is broken. This should NOT have run!" );
}

//----------------------------------------------------------

TEMPER_TEST( GivenIsolatedTest_WhenDeclaredWithDepricatedFlag_IsNotExecuted, false, false, TEMPER_TEST_FLAG_DEPRECATED )
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