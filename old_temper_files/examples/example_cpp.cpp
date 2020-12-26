#include "../temper.h"

#include <stdio.h>
#include <math.h>

TEMPER_DEFS();

TEMPER_SUITE_EXTERN( TheSuite );

int main( int argc, char** argv ) {
	( (void) argc );
	( (void) argv );

	TEMPER_RUN_SUITE( TheSuite );

	TEMPER_SHOW_STATS();

	return TEMPER_EXIT_CODE();
}
