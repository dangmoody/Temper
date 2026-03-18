#ifdef BUILDER_DOING_USER_CONFIG_BUILD

#include <builder.h>

#include "build_configs.cpp"

BUILDER_CALLBACK void SetBuilderOptions( BuilderOptions *options ) {
#if defined( _WIN32 )
	options->compilerPath = "C:/mingw64/bin/gcc";
#else
	options->compilerPath = "gcc";
#endif

	GetBuildConfigs( options, COMPILER_GCC );
}

#endif // BUILDER_IS_DOING_USER_CONFIG_BUILD