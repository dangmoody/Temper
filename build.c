#define BUILDER_IMPLEMENTATION
#include "builder/builder.h"

#define BUILDER_VISUAL_STUDIO_IMPLEMENTATION
#include "builder/builder_visual_studio.h"

#define ARG_GCC					"--gcc"
#define ARG_MSVC				"--msvc"
#define ARG_RELEASE				"--release"
#define ARG_SLN					"--sln"

#define COMPILER_NAME_CLANG		"clang"
#define COMPILER_NAME_GCC		"gcc"
#define COMPILER_NAME_MSVC		"msvc"

#define COMPILER_PATH_GCC		"gcc"
#define COMPILER_PATH_MSVC		"cl"

#define COMPILER_VERSION_GCC	"15.2.0"
#define COMPILER_VERSION_MSVC	"14.44.35207"

#define CONFIG_FOLDER_DEBUG		"debug"
#define CONFIG_FOLDER_RELEASE	"release"

#ifdef _WIN32
#define EXE_EXTENSION			".exe"
#else
#define EXE_EXTENSION			""
#endif

enum {
	PROJECT_AUTOMATION_C	= 0,
	PROJECT_AUTOMATION_CPP,
	PROJECT_SCALE_TEST_C,

	PROJECT_COUNT
};

enum {
	VS_CONFIG_DEBUG	= 0,
	VS_CONFIG_RELEASE,

	VS_CONFIG_COUNT
};

int main( int argc, char **argv ) {
	BuilderOptions options = { 0 };
	options.intermediateFolder = "bin/intermediate";

	bool gcc = HasCommandLineArg( argc, argv, ARG_GCC );
	bool msvc = HasCommandLineArg( argc, argv, ARG_MSVC );
	bool clang = !gcc && !msvc;

	bool release = HasCommandLineArg( argc, argv, ARG_RELEASE );

	const char *compilerName = COMPILER_NAME_CLANG;
	const char *configFolder = release ? CONFIG_FOLDER_RELEASE : CONFIG_FOLDER_DEBUG;
	const char *configDefine = release ? "NDEBUG" : "_DEBUG";

	// compiler
	{
		if ( gcc ) {
			options.compilerPath = COMPILER_PATH_GCC;
			options.compilerVersion = COMPILER_VERSION_GCC;

			compilerName = COMPILER_NAME_GCC;
		} else if ( msvc ) {
			options.compilerPath = COMPILER_PATH_MSVC;
			options.compilerVersion = COMPILER_VERSION_MSVC;

			compilerName = COMPILER_NAME_MSVC;
		}
	}

	// self rebuild
	{
		options.selfRebuildConfig = CreateBuildConfig( &options );
		*options.selfRebuildConfig = (BuildConfig) {
			.name			= "build",
			.binaryName		= "build",
			.sourceFiles	= MakeStringList( "build.c" ),
		};

#ifdef __linux__
		AddLibs( options.selfRebuildConfig, "libuuid" );
#endif
	}

	BuildConfig *automationC = CreateBuildConfig( &options );
	*automationC = (BuildConfig) {
		.name				= "automation-c",
		.binaryName			= Config_FormatString( "automation_c_%s", compilerName ),
		.binaryFolder		= Config_FormatString( "bin/%s", configFolder ),
		.sourceFiles		= MakeStringList( "tests/automation_c/automation_c.c" ),
		.defines			= MakeStringList( "_CRT_SECURE_NO_WARNINGS", configDefine ),
		.languageVersion	= LANGUAGE_VERSION_C99,
	};

	BuildConfig *automationCPP = CreateBuildConfig( &options );
	*automationCPP = (BuildConfig) {
		.name				= "automation-cpp",
		.binaryName			= Config_FormatString( "automation_cpp_%s", compilerName ),
		.binaryFolder		= Config_FormatString( "bin/%s", configFolder ),
		.sourceFiles		= MakeStringList( "tests/automation_cpp/automation_cpp.cpp" ),
		.defines			= MakeStringList( "_CRT_SECURE_NO_WARNINGS", configDefine ),
	};

#ifdef __linux__
	if ( clang ) {
		AddLibs( automationCPP, "libstdc++" );
	} else if ( gcc ) {
		AddLibs( automationCPP, "libstdc++" );
		AddLinkerArguments( automationCPP, "-static", "-static-libstdc++", "-static-libgcc" );
	}
#endif

	BuildConfig *scaleTestC = CreateBuildConfig( &options );
	*scaleTestC = (BuildConfig) {
		.name				= "scale-test-c",
		.binaryName			= Config_FormatString( "scale_test_c_%s", compilerName ),
		.binaryFolder		= Config_FormatString( "bin/%s", configFolder ),
		.sourceFiles		= MakeStringList( "tests/scale_test_c/scale_test_c.c" ),
		.defines			= MakeStringList( "_CRT_SECURE_NO_WARNINGS", configDefine ),
		.languageVersion	= LANGUAGE_VERSION_C99,
	};

#ifdef __linux__
	AddLibs( scaleTestC, "libm" );
#endif

	// visual studio solution
	if ( HasCommandLineArg( argc, argv, ARG_SLN ) ) {
		BuildConfig *projectConfigs[PROJECT_COUNT] = {
			[PROJECT_AUTOMATION_C]		= automationC,
			[PROJECT_AUTOMATION_CPP]	= automationCPP,
			[PROJECT_SCALE_TEST_C]		= scaleTestC,
		};

		const char *projectNames[PROJECT_COUNT] = {
			[PROJECT_AUTOMATION_C]		= "automation_c",
			[PROJECT_AUTOMATION_CPP]	= "automation_cpp",
			[PROJECT_SCALE_TEST_C]		= "scale_test_c",
		};

		VisualStudioConfig vsConfigs[PROJECT_COUNT][VS_CONFIG_COUNT];
		VisualStudioProject vsProjects[PROJECT_COUNT];

		for ( uint32_t projectIndex = 0; projectIndex < PROJECT_COUNT; projectIndex++ ) {
			BuildConfig *config = projectConfigs[projectIndex];

			// one BuildConfig backs both vs configs so the output path has to be spelled out per config
			vsConfigs[projectIndex][VS_CONFIG_DEBUG] = (VisualStudioConfig) {
				.name			= "debug",
				.config			= config,
				.nmakeOutput	= Config_FormatString( "bin/%s/%s%s", CONFIG_FOLDER_DEBUG, config->binaryName, EXE_EXTENSION ),
			};

			vsConfigs[projectIndex][VS_CONFIG_RELEASE] = (VisualStudioConfig) {
				.name					= "release",
				.config					= config,
				.nmakeOutput			= Config_FormatString( "bin/%s/%s%s", CONFIG_FOLDER_RELEASE, config->binaryName, EXE_EXTENSION ),
				.additionalBuildArgs	= MakeStringList( ARG_RELEASE ),
			};

			vsProjects[projectIndex] = (VisualStudioProject) {
				.configs		= vsConfigs[projectIndex],
				.configsCount	= VS_CONFIG_COUNT,
				.name			= projectNames[projectIndex],
			};
		}

		VisualStudioSolution solution = {
			.projects		= vsProjects,
			.projectsCount	= PROJECT_COUNT,
			.platforms		= MakeStringList( "x64" ),
			.name			= "Temper",
			.path			= "visual_studio",
		};

		return Builder_GenerateVisualStudioSolution( &options, &solution, argc, argv ) ? 0 : 1;
	}

	return Build( &options, argc, argv );
}
