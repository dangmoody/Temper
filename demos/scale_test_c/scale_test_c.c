#include "tantrum_scale_test.h"
#include "vector2d.h"
#include "vector2d_tests.c"

//#ifdef TANTRUM_TESTS_ENABLED

// DM: I've also got this exact entry point in my filtering demo
// would it be worth making a TANTRUM_MAIN() so that if people just want to get a quick test application running then they can type that instead of all of this?
// the only fear I have with that is people then might think trying to get more manual control over their entry points could be more difficult and they could be scared off
// but I think documentation would solve that
// what do we think? good idea? bad?
int main( int argc, char** argv ){
	TANTRUM_SETUP();
	return TANTRUM_RUN_ALL_TESTS_WITH_ARGS( argc, argv );
}

//#else

//int main( int argc, char** argv ){
//	// Your production code goes here
//}
//#endif //TANTRUM_TESTS_ENABLED