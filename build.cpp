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

	return std::string();
}

#pragma clang diagnostic pop

BUILDER_CALLBACK void SetBuilderOptions( BuilderOptions *options, CommandLineArgs *args ) {
	std::string compilerName;

	bool gcc = HasCommandLineArg( args, "--gcc" );
	bool msvc = HasCommandLineArg( args, "--msvc" );
	bool clang = !gcc && !msvc;

	if ( gcc ) {
		options->compilerPath = "gcc";
		options->compilerVersion = "15.2.0";

		compilerName = "gcc";
	} else if ( msvc ) {
		options->compilerPath = "cl";
		options->compilerVersion = "14.44.35207";

		compilerName = "msvc";
	} else {
		compilerName = "clang";
	}

	bool release = HasCommandLineArg( args, "--release" );

	BuildConfig automationC = {
		.name				= "automation-c",
		.binaryFolder		= "bin/",
		.binaryName			= "automation_c_" + compilerName,
		.languageVersion	= LANGUAGE_VERSION_C99,
		.sourceFiles		= { "tests/automation_c/automation_c.c" },
		.defines			= { "_CRT_SECURE_NO_WARNINGS" },
	};

	if ( release ) {
		automationC.binaryFolder += "release";
		automationC.defines.push_back( "NDEBUG" );
	} else {
		automationC.binaryFolder += "debug";
		automationC.defines.push_back( "_DEBUG" );
	}

	AddBuildConfig( options, &automationC );

	BuildConfig automationCPP = {
		.name				= "automation-cpp",
		.binaryFolder		= "bin/",
		.binaryName			= "automation_cpp_" + compilerName,
		.sourceFiles		= { "tests/automation_cpp/automation_cpp.cpp" },
		.defines			= { "_CRT_SECURE_NO_WARNINGS" },
	};

	if ( release ) {
		automationCPP.binaryFolder += "release";
		automationCPP.defines.push_back( "NDEBUG" );
	} else {
		automationCPP.binaryFolder += "debug";
		automationCPP.defines.push_back( "_DEBUG" );
	}

	if ( clang ) {
		automationCPP.additionalLibs.push_back( "stdc++" );
	} else if ( gcc ) {
		automationCPP.additionalLibs.push_back( "stdc++" );
		automationCPP.additionalLinkerArguments.push_back( "-static" );
		automationCPP.additionalLinkerArguments.push_back( "-static-libstdc++" );
		automationCPP.additionalLinkerArguments.push_back( "-static-libgcc" );
	}

	AddBuildConfig( options, &automationCPP );

	BuildConfig scaleTestC = {
		.name				= "scale-test-c",
		.binaryFolder		= "bin/",
		.binaryName			= "scale_test_c_" + compilerName,
		.languageVersion	= LANGUAGE_VERSION_C99,
		.sourceFiles		= { "tests/scale_test_c/scale_test_c.c" },
		.defines			= { "_CRT_SECURE_NO_WARNINGS" },
#ifdef __linux__
		.additionalLibs		= { "m" },
#endif
	};

	if ( release ) {
		scaleTestC.binaryFolder += "release";
		scaleTestC.defines.push_back( "NDEBUG" );
	} else {
		scaleTestC.binaryFolder += "debug";
		scaleTestC.defines.push_back( "_DEBUG" );
	}

	AddBuildConfig( options, &scaleTestC );

	options->solution = {
		.name = "Temper",
		.path = "visual_studio",
		.platforms = { "x64" },
		.projects = {
			{
				.name = "automation_c",
				.configs = {
					{ "debug",   automationC, {             }, { /* debugger arguments */ } },
					{ "release", automationC, { "--release" }, { /* debugger arguments */ } },
				},
			},

			{
				.name = "automation_cpp",
				.configs = {
					{ "debug",   automationCPP, {             }, { /* debugger arguments */ } },
					{ "release", automationCPP, { "--release" }, { /* debugger arguments */ } },
				},
			},

			{
				.name = "scale_test_c",
				.configs = {
					{ "debug",   scaleTestC, {             }, { /* debugger arguments */ } },
					{ "release", scaleTestC, { "--release" }, { /* debugger arguments */ } },
				},
			},
		},
	};

	if ( HasCommandLineArg( args, "--sln" ) ) {
		options->generateSolution = true;
	}
}

#endif // BUILDER_DOING_USER_CONFIG_BUILD