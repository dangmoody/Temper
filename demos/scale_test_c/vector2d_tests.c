#include "tantrum_scale_test.h"
#include "vector2d.h"
#include "vector2d.c"

TANTRUM_SUITE_TEST( VectorOperators, GivenTwoVectors_WhenAddedTogether_ThenAddedCorrectly, TANTRUM_TEST_SHOULD_RUN ){
	vector2d A = { 2.f,4.f };
	vector2d B = { 4.f,6.f };
	vector2d Result = Vector2D_Add( A, B );
	TANTRUM_TEST_EQUAL( Result.x, 6.f, "Vector2D_Add function is broken" );
	TANTRUM_TEST_EQUAL( Result.y, 10.f, "Vector2D_Add function is broken" );
}

TANTRUM_SUITE_TEST( VectorOperators, GivenTwoVectors_WhenSubtractedTogether_ThenSubtractCorrectly, TANTRUM_TEST_SHOULD_RUN ){
	vector2d A = { 2.f,4.f };
	vector2d B = { 4.f,6.f };
	vector2d Result = Vector2D_Sub( A, B );
	TANTRUM_TEST_EQUAL( Result.x, -2.f, "Vector2D_Sub function is broken" );
	TANTRUM_TEST_EQUAL( Result.y, -2.f, "Vector2D_Sub function is broken" );
}

TANTRUM_SUITE_TEST( VectorOperators, GivenTwoVectors_WhenMultipliedTogether_ThenMultiplyCorrectly, TANTRUM_TEST_SHOULD_RUN ){
	vector2d A = { 2.f,4.f };
	vector2d B = { 4.f,6.f };
	vector2d Result = Vector2D_Mul( A, B );
	TANTRUM_TEST_EQUAL( Result.x, 8.f, "Vector2D_Mul function is broken" );
	TANTRUM_TEST_EQUAL( Result.y, 24.f, "Vector2D_Mul function is broken" );
}

TANTRUM_SUITE_TEST( VectorOperators, GivenTwoVectors_WhenDividedTogether_ThenDivideCorrectly, TANTRUM_TEST_SHOULD_RUN ){
	vector2d A = { 2.f,4.f };
	vector2d B = { 4.f,6.f };
	vector2d Result = Vector2D_Div( A, B );
	TANTRUM_TEST_ALMOST_EQUAL( Result.x, 0.5f, 0.2f, "Vector2D_Div function is broken" );
	TANTRUM_TEST_ALMOST_EQUAL( Result.y, 0.5f, 0.2f, "Vector2D_Div function is broken" );
}

TANTRUM_TEST( GivenAVectors_WhenGetLengthIsCalled_ThenTrueLengthFound, TANTRUM_TEST_SHOULD_RUN ){
	vector2d vector = { 0.f,7.5f };
	float vectorLength = Vector2D_GetLength( vector );
	TANTRUM_TEST_ALMOST_EQUAL( vectorLength, 7.5f, 0.1f, "Expected a vector of length 7.5 to be found" );
}