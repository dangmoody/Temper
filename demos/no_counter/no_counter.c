#ifdef _WIN32
#include <Windows.h>
//#include <winnt.h>
#endif

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#if defined( _WIN32 )
#define NC_API			__declspec( dllexport )
#elif defined( __APPLE__ ) || defined( __linux__ )
#define NC_API			__attribute__( ( visibility( "default" ) ) )
#else
#error Uncrecognised platform.  It appears Temper does not support it.  If you think this is a bug, please submit an issue at https://github.com/dangmoody/Temper/issues
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-align"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wincompatible-pointer-types"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wsign-compare"

void NC_API DoSomething( void );
void DoSomething( void ) {
	printf( "hi" );
}

int main( int argc, char** argv ) {
	( (void) argc );
	( (void) argv );

	char programName[4096];

	DWORD fullExePathLength = GetModuleFileName( NULL, programName, 4096 );
	if ( fullExePathLength == 0 ) {
		printf( "ERROR: WinAPI call GetModuleFileName() failed: 0x%lX\n", GetLastError() );
		return 1;
	}

	HANDLE exeHandle = CreateFile( programName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL );
	assert( exeHandle != INVALID_HANDLE_VALUE );

	HANDLE exeMap = CreateFileMapping( exeHandle, NULL, PAGE_READONLY|SEC_IMAGE, 0, 0, "KernelMap" );
	assert( exeMap != INVALID_HANDLE_VALUE );

	LPVOID exeImage = MapViewOfFile( exeMap, FILE_MAP_READ, 0, 0, 0 );
	assert( exeImage != 0 );

	char* image = (char*) exeImage;

	PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER) image;
	assert( dosHeader->e_magic == IMAGE_DOS_SIGNATURE );

	PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS) ( image + dosHeader->e_lfanew );
	assert( ntHeader->Signature == IMAGE_NT_SIGNATURE );
	assert( ntHeader->OptionalHeader.NumberOfRvaAndSizes > 0 );

	IMAGE_OPTIONAL_HEADER optionalHeader = ntHeader->OptionalHeader;
	IMAGE_DATA_DIRECTORY dataDir = optionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
	PIMAGE_EXPORT_DIRECTORY exportDir = (PIMAGE_EXPORT_DIRECTORY) ( image + dataDir.VirtualAddress );

	DWORD* nameTable = (DWORD*) ( image + exportDir->AddressOfNames );

	for ( int i = 0; i < exportDir->NumberOfNames; i++ ) {
		char* funcName = (char*) ( image + nameTable[i] );

		printf( "Exported function: %s\n", funcName );
	}

	return 0;
}

#pragma clang diagnostic pop