#include "../../temper.h"
#include "vector2d.h"
#include "vector2d.c"

TEMPER_SUITE_TEST( VectorOperators, GivenTwoVectors_WhenAddedTogether_ThenAddedCorrectly, TEMPER_TEST_FLAG_SHOULD_RUN ){
	vector2d A = { 2.f,4.f };
	vector2d B = { 4.f,6.f };
	vector2d Result = Vector2D_Add( A, B );
	TEMPER_TEST_FLOAT_EQUAL_M( Result.x, 6.f, "Vector2D_Add function is broken" );
	TEMPER_TEST_FLOAT_EQUAL_M( Result.y, 10.f, "Vector2D_Add function is broken" );
}

TEMPER_SUITE_TEST( VectorOperators, GivenTwoVectors_WhenSubtractedTogether_ThenSubtractCorrectly, TEMPER_TEST_FLAG_SHOULD_RUN ){
	vector2d A = { 2.f,4.f };
	vector2d B = { 4.f,6.f };
	vector2d Result = Vector2D_Sub( A, B );
	TEMPER_TEST_FLOAT_EQUAL_M( Result.x, -2.f,  "Vector2D_Sub function is broken" );
	TEMPER_TEST_FLOAT_EQUAL_M( Result.y, -2.f,  "Vector2D_Sub function is broken" );
}

TEMPER_SUITE_TEST( VectorOperators, GivenTwoVectors_WhenMultipliedTogether_ThenMultiplyCorrectly, TEMPER_TEST_FLAG_SHOULD_SKIP ){
	vector2d A = { 2.f,4.f };
	vector2d B = { 4.f,6.f };
	vector2d Result = Vector2D_Mul( A, B );
	TEMPER_TEST_FLOAT_EQUAL_M( Result.x, 8.f, "Vector2D_Mul function is broken" );
	TEMPER_TEST_FLOAT_EQUAL_M( Result.y, 99.f, "Vector2D_Mul function is broken" ); // expecting this to fail - to test temper's internal system
}

TEMPER_SUITE_TEST( VectorOperators, GivenTwoVectors_WhenDividedTogether_ThenDivideCorrectly, TEMPER_TEST_FLAG_SHOULD_SKIP ) {
	vector2d A = { 2.f,4.f };
	vector2d B = { 4.f,6.f };
	vector2d Result = Vector2D_Div( A, B );
	TEMPER_TEST_ALMOST_EQUAL_M( Result.x, 99.f, 0.2f, "Vector2D_Div function is broken" ); // expecting this to fail - to test temper's internal system
	TEMPER_TEST_ALMOST_EQUAL_M( Result.y, 0.5f, 0.2f, "Vector2D_Div function is broken" );
}

TEMPER_TEST( GivenAVectors_WhenGetLengthIsCalled_ThenTrueLengthFound, TEMPER_TEST_FLAG_SHOULD_RUN ){
	vector2d vector = { 0.f,7.5f };
	float vectorLength = Vector2D_GetLength( vector );
	TEMPER_TEST_ALMOST_EQUAL_M( vectorLength, 7.5f, 0.1f, "Expected a vector of length 7.5 to be found" );
}

TEMPER_DECLARE_PARAMETRIC_SUITE_TEST( AdditionSuite, AdditionPowerSet, TEMPER_TEST_FLAG_SHOULD_RUN, float left, float right, float expected )
{
	float result = left + right;
	TEMPER_TEST_FLOAT_EQUAL_M( result, expected, "Addition function is broken" );
}

TEMPER_INVOKE_PARAMETRIC_TEST( AdditionPowerSet, 5, 15.f, 20.f );
TEMPER_INVOKE_PARAMETRIC_TEST( AdditionPowerSet, 7, 3.f, 10.f );
//TEMPER_INVOKE_PARAMETRIC_TEST( AdditionPowerSet, -9.1f, 14.6f, 7.5f ); // expecting this to fail
TEMPER_INVOKE_PARAMETRIC_TEST( AdditionPowerSet, -63.f, 2.f, -61.f );

TEMPER_DECLARE_PARAMETRIC_TEST( SubtractionPowerSet, TEMPER_TEST_FLAG_DEPRECATED, float left, float right, float expected )
{
	float result = left - right;
	TEMPER_TEST_FLOAT_EQUAL_M( result, expected, "Subtraction function is broken" );
}

TEMPER_INVOKE_PARAMETRIC_TEST( SubtractionPowerSet, 4, 4.f, 0.f );
TEMPER_INVOKE_PARAMETRIC_TEST( SubtractionPowerSet, 4, 2.f, 2.f );
TEMPER_INVOKE_PARAMETRIC_TEST( SubtractionPowerSet, -9.1f, 14.6f, -23.7f );

static void TestAbortTestCase( float a, float b, const char* message )
{
	TEMPER_TEST_FLOAT_EQUAL_OR_ABORT_M( a, b, message );
}

TEMPER_SUITE_TEST( AbortTesting, TestEqualOrAbortUsed_ValuesAreEqual_ThreadNotAborted, TEMPER_TEST_FLAG_SHOULD_RUN )
{
	TestAbortTestCase( 5.f, 5.f, "Expected these two values to be equal" );
	TEMPER_TEST_TRUE_M( true, "We expect this to execute" );
}

TEMPER_SUITE_TEST( AbortTesting, TestEqualOrAbortUsed_ValuesAreNotEqual_ThreadAbortedBeforeTestConcludes, TEMPER_TEST_FLAG_SHOULD_SKIP )
{
	TestAbortTestCase( 5.f, 7.f, "Expected these two values to be equal" );
	TEMPER_TEST_TRUE_M( false, "The test should have been aborted and this test never executed" );
}
