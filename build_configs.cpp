#ifdef BUILDER_DOING_USER_CONFIG_BUILD

#include <builder.h>

enum config_t {
	CONFIG_DEBUG	= 0,
	CONFIG_RELEASE,

	CONFIG_COUNT
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"

static std::string GetConfigName( const config_t config ) {
	switch ( config ) {
		case CONFIG_DEBUG:		return "debug";
		case CONFIG_RELEASE:	return "release";
	}

	printf( "ERROR: Bad config_t passed.\n" );

	return NULL;
}

static std::string GetDebugDefine( const config_t config ) {
	switch ( config ) {
		case CONFIG_DEBUG:		return "_DEBUG";
		case CONFIG_RELEASE:	return "NDEBUG";
	}

	printf( "ERROR: Bad config_t passed.\n" );

	return NULL;
}

#pragma clang diagnostic pop

static void GetBuildConfigs( BuilderOptions *options, const std::string &compilerName ) {
	for ( int configIndex = 0; configIndex < CONFIG_COUNT; configIndex++ ) {
		const config_t config = (config_t) configIndex;

		const std::string &configName = GetConfigName( config );

		BuildConfig automationC = {
			.name				= "automation-c-" + configName,
			.binaryFolder		= "bin/" + configName + "/" + compilerName,
			.binaryName			= "automation_c_" + compilerName,
			.languageVersion	= LANGUAGE_VERSION_C99,
			.sourceFiles		= { "tests/automation_c/automation_c.c" },
			.defines			= { "_CRT_SECURE_NO_WARNINGS", GetDebugDefine( config ) },
		};
		AddBuildConfig( options, &automationC );

		BuildConfig automationCPP = {
			.name				= "automation-cpp-" + configName,
			.binaryFolder		= "bin/" + configName + "/" + compilerName,
			.binaryName			= "automation_cpp_" + compilerName,
			.sourceFiles		= { "tests/automation_cpp/automation_cpp.cpp" },
			.defines			= { "_CRT_SECURE_NO_WARNINGS", GetDebugDefine( config ) },
		};

		if ( compilerName == "gcc" ) {
			automationCPP.additionalLibs = { "stdc++" };

			automationCPP.additionalLinkerArguments.push_back( "-static" );
			automationCPP.additionalLinkerArguments.push_back( "-static-libstdc++" );
			automationCPP.additionalLinkerArguments.push_back( "-static-libgcc" );
		}

		AddBuildConfig( options, &automationCPP );

		BuildConfig scaleTestC = {
			.name				= "scale-test-c-" + configName,
			.binaryFolder		= "bin/" + configName + "/" + compilerName,
			.binaryName			= "scale_test_c_" + compilerName,
			.languageVersion	= LANGUAGE_VERSION_C99,
			.sourceFiles		= { "tests/scale_test_c/scale_test_c.c" },
			.defines			= { "_CRT_SECURE_NO_WARNINGS", GetDebugDefine( config ) },
		};
		AddBuildConfig( options, &scaleTestC );
	}

	//options->generateSolution = true;
	//options->solution = {
	//	.name = "Temper",
	//	.path = "visual_studio",
	//	.platforms = { "x64" },
	//	.projects = {
	//		{
	//			.name = "automation_c",
	//			.configs = {
	//				{ "debug",   automationCDebug,   /* debugger arguments */ },
	//				{ "release", automationCRelease, /* debugger arguments */ },
	//			},
	//		},
	//
	//		{
	//			.name = "automation_cpp",
	//			.configs = {
	//				{ "debug",   automationCDebug,   /* debugger arguments */ },
	//				{ "release", automationCRelease, /* debugger arguments */ },
	//			},
	//		},
	//
	//		{
	//			.name = "scale_test_c",
	//			.configs = {
	//				{ "debug",   automationCDebug,   /* debugger arguments */ },
	//				{ "release", automationCRelease, /* debugger arguments */ },
	//			},
	//		},
	//	},
	//};
}

#endif // BUILDER_DOING_USER_CONFIG_BUILD