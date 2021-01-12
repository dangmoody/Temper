#include "../../tantrum.h"

static void CheckIntDoesNotEqual( const uint32_t a, const uint32_t b ) {
	TANTRUM_TEST_FALSE_OR_ABORT_M( a == b, "A is equal to B now!" );
}

TANTRUM_TEST( DanTest0, TANTRUM_TEST_FLAG_SHOULD_RUN ) {
	for ( uint32_t i = 0; i < 10; i++ ) {
		CheckIntDoesNotEqual( i, 5 );
	}
}

TANTRUM_TEST( DanTest1, TANTRUM_TEST_FLAG_SHOULD_RUN ) {
	for ( uint32_t i = 0; i < 10; i++ ) {
		TANTRUM_TEST_EQUAL_M( i, i, "NO" );
	}
}

TANTRUM_TEST( DanTest2, TANTRUM_TEST_FLAG_SHOULD_RUN ) {
	for ( uint32_t i = 0; i < 10; i++ ) {
		TANTRUM_TEST_NOT_EQUAL_M( i, i + 1, "NO2" );
	}
}


int main( int argc, char** argv ) {
	TANTRUM_SETUP();
	return TANTRUM_RUN_ALL_TESTS_WITH_ARGS( argc, argv );
}