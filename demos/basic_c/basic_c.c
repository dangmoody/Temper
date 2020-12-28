#include <Windows.h>

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/*
DM: this file just contains me hacking something together that solves our primary problem: test auto-registration
everything in this demo file right now is just to show how it _might_ work
there are no guarantees it will look anything like this when I start moving code into tantrum.h for others to play around with
but so far I'm somewhat happy with what I've got here
*/

#if defined( __GNUC__ ) || defined( __clang__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#endif

typedef void ( *testFunc_t )( void );

#define TEMPER_CONCAT_INTERNAL_( a, b )	a ## b
#define TEMPER_CONCAT_INTERNAL( a, b )	TEMPER_CONCAT_INTERNAL_( a, b )

#define TANTRUM_TEST( test_name ) \
	void ( test_name )( void );\
	__declspec( dllexport ) void TEMPER_CONCAT_INTERNAL( tantrum_test_invoker_, __COUNTER__ )( void )\
	{\
		/*Here we can declare a test name and that it's running then starting a timer*/\
		( test_name )();\
		/*Here we can stop the timer and print the total execution time and if it failed etc*/\
	}\
	void ( test_name )( void )

TANTRUM_TEST( OrderingBeer )
{
	printf( "Beer...\n" );
	printf( "\n" );
}

TANTRUM_TEST( ReOrderingBeer )
{
	printf( "Another one for me please barman...\n" );
	printf( "\n" );
}

TANTRUM_TEST(TableFlippingForBeer)
{
	printf( "I SAID ANOTHER!\n" );
	printf( "\n" );
}

int main( int argc, char** argv ) {
	( (void) argc );

	HANDLE handle = LoadLibrary( argv[0] );
	assert( handle );

	{
		// DM: yeah yeah yeah, I know: fixed-length string arrays bad
		// I'll write a tprintf at some point
		char testFuncNames[1024];
		testFunc_t testFunc = NULL;

		for ( uint32_t i = 0; i < __COUNTER__; i++ ) {
			snprintf( testFuncNames, 1024, "tantrum_test_invoker_%d", i );
			printf( "tantrum_test_invoker_%d\t\t", i );
			testFunc = (testFunc_t) GetProcAddress( handle, testFuncNames );
			assert( testFunc );

			testFunc();
		}
	}

	FreeLibrary( handle );
	handle = NULL;
	return 0;
}

#if defined( __GNUC__ ) || defined( __clang__ )
#pragma GCC diagnostic pop
#endif