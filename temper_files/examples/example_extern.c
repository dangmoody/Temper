#include "../temper.h"

#include <stdio.h>

TEMPER_SUITE_EXTERN( TheSuite );
TEMPER_TEST_EXTERN( XShouldEqual0 );

TEMPER_DEFS();

int main( int argc, char** argv ) {
	( (void) argc );
	( (void) argv );

	TEMPER_RUN_SUITE( TheSuite );
	TEMPER_RUN_TEST( XShouldEqual0 );

	TEMPER_SHOW_STATS();

	return TEMPER_EXIT_CODE();
}
