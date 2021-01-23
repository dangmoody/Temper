#include "../../temper.h"

/*
DM: you need to run this demo with command line arguments to see filtering working:

	-s <suite name> to only run suites with that name
	-t <test name> to only run tests with that name

you can also combine both of them to only run a specific test in a specific suite

this is also the best I can do for unifying TEMPER_TEST() and TEMPER_SUITE_TEST() right now

I'm not so sure I like the unification of tests and "suite tests" because the NULL suite name string has added a lot of extra branching
*/

TEMPER_TEST( OrderingBeer, TEMPER_FLAG_SHOULD_RUN ) {
}

TEMPER_TEST( ReOrderingBeer, TEMPER_FLAG_SHOULD_RUN ) {
	TEMPER_CHECK_EQUAL( 5, 5 );
	TEMPER_CHECK_NOT_EQUAL( 5, 9 );
}

TEMPER_TEST( ReReOrderingBeer, TEMPER_FLAG_DEPRECATED ) {
}

TEMPER_TEST( TableFlippingForBeer, TEMPER_FLAG_SHOULD_SKIP ) {
}

TEMPER_SUITE_TEST( MySuite, DansSuiteTest, TEMPER_FLAG_SHOULD_RUN ) {
}

TEMPER_SUITE_TEST( MySuite, DansSuiteTest2, TEMPER_FLAG_SHOULD_RUN ) {
}

int main( int argc, char** argv ){
	TEMPER_SETUP();
	return TEMPER_RUN_ALL_TESTS_WITH_ARGS( argc, argv );
}