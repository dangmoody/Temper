#pragma clang diagnostic ignored "-Wreserved-id-macro"

#if defined( _WIN32 )
#include <Windows.h>
#elif defined( __APPLE__ ) || defined( __linux__ )
//#define _POSIX_C_SOURCE 200112L
#include <link.h>
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

#ifdef __cplusplus
#define NC_EXTERN_C		extern "C"
#else
#define NC_EXTERN_C
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-align"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wincompatible-pointer-types"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wsign-compare"

NC_EXTERN_C void NC_API DoSomething( void );
void DoSomething( void ) {
	printf( "hi" );
}

#if defined( __APPLE__ ) || defined( __linux__ )
static int IterateSymbolsInternal( struct dl_phdr_info* info, size_t size, void* data ) {
	( (void) size );
	( (void) data );

	ElfW( Dyn* ) dyn;
	ElfW( Sym* ) symbol;
	ElfW( Word* ) hash;

	char* stringTable = NULL;
	ElfW( Word ) numSymbols = 0;

	printf( "Found: \"%s\" (%d segments).\n", info->dlpi_name, info->dlpi_phnum );

	for ( int i = 0; i < info->dlpi_phnum; i++ ) {
		if ( info->dlpi_phdr[i].p_type == PT_DYNAMIC ) {
			dyn = (ElfW( Dyn* )) ( info->dlpi_addr + info->dlpi_phdr[i].p_vaddr );

			while ( dyn ) {
				switch ( dyn->d_tag ) {
					case DT_HASH:
						hash = (ElfW( Word* )) dyn->d_un.d_ptr;

						numSymbols = hash[1];
						break;

					case DT_STRTAB:
						stringTable = (char*) dyn->d_un.d_ptr;
						break;

					case DT_SYMTAB:
						symbol = (ElfW( Sym* )) dyn->d_un.d_ptr;

						for ( ElfW( Word ) symbolIndex = 0; symbolIndex < numSymbols; symbolIndex++ ) {
							char* symbolName = &stringTable[symbol[symbolIndex].st_name];

							printf( "FOUND SYMBOL: %s.\n", symbolName );
						}
						break;

					default:
						// skip
						break;
				}

				dyn++;
			}
		}
	}

	return 0;
}
#endif

int main( int argc, char** argv ) {
	( (void) argc );
	( (void) argv );

#if defined( _WIN32 )
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
#elif defined( __APPLE__ ) || defined( __linux__ )
	dl_iterate_phdr( IterateSymbolsInternal, NULL );
#endif

	return 0;
}

#pragma clang diagnostic pop