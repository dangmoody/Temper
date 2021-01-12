#include "../../tantrum.h"

/*
DM: you need to run this demo with command line arguments to see filtering working:

	-s <suite name> to only run suites with that name
	-t <test name> to only run tests with that name

you can also combine both of them to only run a specific test in a specific suite

this is also the best I can do for unifying TANTRUM_TEST() and TANTRUM_SUITE_TEST() right now

I'm not so sure I like the unification of tests and "suite tests" because the NULL suite name string has added a lot of extra branching
*/

TANTRUM_TEST( OrderingBeer, TANTRUM_TEST_FLAG_SHOULD_RUN ) {
}

TANTRUM_TEST( ReOrderingBeer, TANTRUM_TEST_FLAG_SHOULD_RUN ) {
	TANTRUM_TEST_EQUAL( 5.0f, 9.0f, "DOESN'T WORK" );
}

TANTRUM_TEST( ReReOrderingBeer, TANTRUM_TEST_FLAG_DEPRECATED ) {
}

TANTRUM_TEST( TableFlippingForBeer, TANTRUM_TEST_FLAG_SHOULD_SKIP ) {
}

TANTRUM_SUITE_TEST( MySuite, DansSuiteTest, TANTRUM_TEST_FLAG_SHOULD_RUN ) {
}

TANTRUM_SUITE_TEST( MySuite, DansSuiteTest2, TANTRUM_TEST_FLAG_SHOULD_RUN ) {
}

int main( int argc, char** argv ){
	TANTRUM_SETUP();
	return TANTRUM_RUN_ALL_TESTS_WITH_ARGS( argc, argv );
}