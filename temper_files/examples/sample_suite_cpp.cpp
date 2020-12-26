#include "../temper.h"

#include <math.h>

static bool floateq( const float x, const float y ) {
	return fabsf( x - y ) < 1e-5f;
}

TEMPER_TEST( XShouldEqual0 ) {
	float x = 0.0f;
	TEMPER_EXPECT_TRUE( floateq( x, 0.0f ) );

	TEMPER_PASS();
}

TEMPER_TEST( XShouldEqual1 ) {
	// DM: changed from 0.0f 
	// used to be 0.0f for testing if tests failed as expected
	float x = 1.0f;
	TEMPER_EXPECT_TRUE( floateq( x, 1.0f ) );

	TEMPER_PASS();
}

TEMPER_TEST( XShouldEqual2 ) {
	float x = 2.0f;
	TEMPER_EXPECT_TRUE( floateq( x, 2.0f ) );

	TEMPER_PASS();
}

TEMPER_TEST( XShouldEqual3 ) {
	float x = 2.0f;
	TEMPER_EXPECT_TRUE( floateq( x, 2.0f ) );

	TEMPER_PASS();
}

TEMPER_SUITE( TheSuite ) {
	TEMPER_RUN_TEST( XShouldEqual0 );
	TEMPER_RUN_TEST( XShouldEqual1 );
	TEMPER_RUN_TEST( XShouldEqual2 );
	TEMPER_SKIP_TEST( XShouldEqual3, "This is a \"skipping test\" test." );
}
