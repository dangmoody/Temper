//#include "../../tantrum.h"

//static void CheckIntDoesNotEqual( const uint32_t a, const uint32_t b ) {
//	TANTRUM_TEST_FALSE_OR_ABORT( a == b, "A is equal to B now!" );
//}

//TANTRUM_TEST( DanTest0, TANTRUM_TEST_FLAG_SHOULD_RUN ) {
//	for ( uint32_t i = 0; i < 10; i++ ) {
//		CheckIntDoesNotEqual( i, 5 );
//	}
//}

//TANTRUM_TEST( DanTest1, TANTRUM_TEST_FLAG_SHOULD_RUN ) {
//	for ( uint32_t i = 0; i < 10; i++ ) {
//		TANTRUM_TEST_EQUAL( i, i, "NO" );
//	}
//}

//TANTRUM_TEST( DanTest2, TANTRUM_TEST_FLAG_SHOULD_RUN ) {
//	for ( uint32_t i = 0; i < 10; i++ ) {
//		TANTRUM_TEST_NOT_EQUAL( i, i + 1, "NO2" );
//	}
//}


//int main( int argc, char** argv ) {
//	TANTRUM_SETUP();
//	return TANTRUM_RUN_ALL_TESTS_WITH_ARGS( argc, argv );
//}

#include <Windows.h>

#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#define CONCAT_( a, b )	a ## b
#define CONCAT( a, b )	CONCAT_( a, b )

#define TEST_API		__declspec( dllexport )

#define TEST_FUNC_INTERNAL( counter ) \
	void TEST_API CONCAT( func_, counter )( void ); \
	void CONCAT( func_, counter )( void )

#define TEST_FUNC()		TEST_FUNC_INTERNAL( __COUNTER__ )

TEST_FUNC() {
	printf( "Hi there.\n" );
}

TEST_FUNC() {
	printf( "We have another one.\n" );
}

TEST_FUNC() {
	printf( "Aaaand another one!\n" );
}

TEST_FUNC() {
	printf( "Oh baby here we go!\n" );
}

static void TestNumbers( const uint32_t a, const uint32_t b ) {
	if ( a == b ) {
		printf( "TEST FAILED.  EXITING...\n" );
		ExitThread( 1 );	// TANTRUM_EXIT_TEST()
	}

	printf( "We passed! %d, %d\n", a, b );
}

TEST_FUNC() {
	for ( uint32_t i = 0; i < 10; i++ ) {
		TestNumbers( i, 5 );
	}
}


typedef void ( *testFunc_t )( void );

typedef struct threadData_t {
	HANDLE		handle;
	const char*	funcName;
} threadData_t;

static unsigned long ThreadProc( void* data ) {
	threadData_t* threadData = (threadData_t*) data;

	testFunc_t testFunc = (testFunc_t) GetProcAddress( threadData->handle, threadData->funcName );
	assert( testFunc );

	testFunc();

	return 0;
}

int main( int argc, char** argv ) {
	( (void) argc );
	( (void) argv );

	char fullExePath[MAX_PATH];
	DWORD fullExePathLength = GetModuleFileName( NULL, fullExePath, MAX_PATH );
	if ( fullExePathLength == 0 ) {
		printf( "ERROR: WinAPI call GetModuleFileName() failed: 0x%lX\n", GetLastError() );
		return 1;
	}

	const char* programName = fullExePath;

	HMODULE handle = LoadLibrary( programName );
	assert( handle );

	// for each function found bla bla bla
	for ( uint32_t i = 0; i < __COUNTER__; i++ ) {
		char testFuncName[1024];
		snprintf( testFuncName, 1024, "func_%d", i );
		//printf( "RUNNING TEST: %s.\n", testFuncName );

		threadData_t threadData;
		threadData.handle = handle;
		threadData.funcName = testFuncName;

		HANDLE testThread = CreateThread( NULL, 0, ThreadProc, &threadData, 0, NULL );
		assert( testThread );

		DWORD result = WaitForMultipleObjects( 1, &testThread, TRUE, UINT32_MAX );
		assert( result == WAIT_OBJECT_0 );

		CloseHandle( testThread );
		testThread = NULL;
	}

	FreeLibrary( (HMODULE) handle );
	handle = NULL;

	return 0;
}