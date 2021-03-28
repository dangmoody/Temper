g_generated_project_files_root = "..\\..\\vs2019-gen"
g_folder_demos = "demos\\"
g_folder_3rdparty = "3rdparty\\"
g_folder_tools = "tools\\"
g_folder_scripts = "scripts\\"

-- get length of array
-- DM: lua doesnt define this!?
function array_length( array )
	array_length = 0

	for i in pairs( array ) do
		array_length = array_length + 1
	end

	return array_length
end


workspace( "Temper" )
	location( g_generated_project_files_root )

	platforms { "win64-clang", "win64-gcc", "win64-msvc" }
	configurations { "debug", "release" }

	startproject( "demos" )

	architecture( "x64" )


--[[
88888888ba,                                                            
88      `"8b                                                           
88        `8b                                                          
88         88   ,adPPYba,  88,dPYba,,adPYba,    ,adPPYba,   ,adPPYba,  
88         88  a8P_____88  88P'   "88"    "8a  a8"     "8a  I8[    ""  
88         8P  8PP"""""""  88      88      88  8b       d8   `"Y8ba,   
88      .a8P   "8b,   ,aa  88      88      88  "8a,   ,a8"  aa    ]8I  
88888888Y"'     `"Ybbd8"'  88      88      88   `"YbbdP"'   `"YbbdP"'  
]]

function set_platform_settings( platform, demo_name, language_file_ext, compiler, compiler_define )
	build_command = "..\\" .. g_folder_scripts .. "build_" .. compiler .. ".bat --output " .. demo_name .. ".exe" .. " --config %{cfg.buildcfg} --source " .. g_folder_demos .. demo_name .. "\\" .. demo_name .. "." .. language_file_ext

	filter ( "platforms:" .. platform )
		buildcommands (
			build_command
		)

		rebuildcommands (
			build_command
		)

		cleancommands (
			"..\\" .. g_folder_scripts .. "clean.bat"
		)

		defines {
			compiler_define
		}

		-- required because VS will create these folders if they don't exist
		targetdir( "..\\..\\bin\\win64\\" .. compiler .. "\\%{cfg.buildcfg}\\" .. g_folder_demos )
		objdir( "!..\\..\\bin\\win64\\" .. compiler .. "\\%{cfg.buildcfg}\\" .. g_folder_demos .. "intermediate" )

		debugcommand( "..\\..\\bin\\win64\\" .. compiler .. "\\%{cfg.buildcfg}\\" .. g_folder_demos .. demo_name .. ".exe" )
	filter {}
end

project( "automation_c" )
	location( g_generated_project_files_root )

	files {
		"..\\..\\" .. g_folder_demos .. "automation_c\\**.c",
		"..\\..\\" .. g_folder_demos .. "automation_c\\**.h",
		"..\\..\\" .. g_folder_demos .. "automation_c\\**.cpp",
		"..\\..\\" .. g_folder_demos .. "automation_c\\**.inl"
	}

	defines {
	}

	sysincludedirs {
	}

	syslibdirs {
	}

	debugdir( "$(SolutionDir)..\\" )

	kind( "MakeFile" )

	set_platform_settings( "win64-clang", "automation_c", "c", "clang", "__clang__" )
	set_platform_settings( "win64-gcc",   "automation_c", "c", "gcc",   "__GNUC__" )
	set_platform_settings( "win64-msvc",  "automation_c", "c", "msvc",  "" )

	filter "configurations:debug"
		defines {
			"_DEBUG"
		}

	filter "configurations:release"
		defines {
			"NDEBUG"
		}
	filter {}

project( "automation_cpp" )
	location( g_generated_project_files_root )

	files {
		"..\\..\\" .. g_folder_demos .. "automation_cpp\\**.c",
		"..\\..\\" .. g_folder_demos .. "automation_cpp\\**.h",
		"..\\..\\" .. g_folder_demos .. "automation_cpp\\**.cpp",
		"..\\..\\" .. g_folder_demos .. "automation_cpp\\**.inl"
	}

	defines {
	}

	sysincludedirs {
	}

	syslibdirs {
	}

	debugdir( "$(SolutionDir)..\\" )

	kind( "MakeFile" )

	set_platform_settings( "win64-clang", "automation_cpp", "cpp", "clang++", "__clang__" )
	set_platform_settings( "win64-gcc",   "automation_cpp", "cpp", "g++",   "__GNUC__" )
	set_platform_settings( "win64-msvc",  "automation_cpp", "cpp", "msvc",  "" )

	filter "configurations:debug"
		defines {
			"_DEBUG"
		}

	filter "configurations:release"
		defines {
			"NDEBUG"
		}
	filter {}

project( "scale_test_c" )
	location( g_generated_project_files_root )

	files {
		"..\\..\\" .. g_folder_demos .. "scale_test_c\\**.c",
		"..\\..\\" .. g_folder_demos .. "scale_test_c\\**.h",
		"..\\..\\" .. g_folder_demos .. "scale_test_c\\**.cpp",
		"..\\..\\" .. g_folder_demos .. "scale_test_c\\**.inl"
	}

	defines {
	}

	sysincludedirs {
	}

	syslibdirs {
	}

	debugdir( "$(SolutionDir)..\\" )

	kind( "MakeFile" )

	set_platform_settings( "win64-clang", "scale_test_c", "c", "clang", "__clang__" )
	set_platform_settings( "win64-gcc",   "scale_test_c", "c", "gcc",   "__GNUC__" )
	set_platform_settings( "win64-msvc",  "scale_test_c", "c", "msvc",  "" )

	filter "configurations:debug"
		defines {
			"_DEBUG"
		}

	filter "configurations:release"
		defines {
			"NDEBUG"
		}
	filter {}