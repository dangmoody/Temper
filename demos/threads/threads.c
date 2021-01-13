#include "../../temper.h"

static void CheckIntDoesNotEqual( const uint32_t a, const uint32_t b ) {
	TEMPER_TEST_FALSE_OR_ABORT_M( a == b, "A is equal to B now!" );
}

TEMPER_TEST( DanTest0, TEMPER_TEST_FLAG_SHOULD_RUN ) {
	for ( uint32_t i = 0; i < 10; i++ ) {
		//printf( "%d\n", i );
		CheckIntDoesNotEqual( i, 5 );
	}
}

TEMPER_TEST( DanTest1, TEMPER_TEST_FLAG_SHOULD_RUN ) {
	for ( uint32_t i = 0; i < 10; i++ ) {
		TEMPER_TEST_EQUAL_M( i, i, "NO" );
	}
}

TEMPER_TEST( DanTest2, TEMPER_TEST_FLAG_SHOULD_RUN ) {
	for ( uint32_t i = 0; i < 10; i++ ) {
		TEMPER_TEST_NOT_EQUAL_M( i, i + 1, "NO2" );
	}
}


int main( int argc, char** argv ) {
	TEMPER_SETUP();
	return TEMPER_RUN_ALL_TESTS_WITH_ARGS( argc, argv );
}