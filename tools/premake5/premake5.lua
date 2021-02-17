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

	platforms { "win64-clang", "win64-clang++", "win64-gcc", "win64-g++", "win64-msvc" }
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

function set_binaries_and_build_commands( demo_name, language_file_ext, compiler, compiler_define )
	if ( compiler ~= "clang" ) and ( compiler ~= "clang++" ) and ( compiler ~= "gcc" ) and ( compiler ~= "g++" ) and ( compiler ~= "msvc" ) then
		print( "ERROR: Compiler \"" .. compiler .. "\" is not a valid compiler name to generate a project for.  Please use one of the correct ones.\n" )
		return
	end

	kind( "MakeFile" )

	if ( compiler == "msvc" ) then
		filter ( "platforms:win64-msvc" )
			buildcommands (
				"..\\" .. g_folder_scripts .. "build_msvc.bat --output " .. demo_name .. ".exe" .. " --config %{cfg.buildcfg} --source " .. g_folder_demos .. demo_name .. "\\" .. demo_name .. "." .. language_file_ext
			)

			rebuildcommands (
				"..\\" .. g_folder_scripts .. "build_msvc.bat --output " .. demo_name .. ".exe" .. " --config %{cfg.buildcfg} --source " .. g_folder_demos .. demo_name .. "\\" .. demo_name .. "." .. language_file_ext
			)

			cleancommands (
				"..\\" .. g_folder_scripts .. "clean.bat"
			)

			defines {
			}

			-- required because VS will create these folders if they don't exist
			targetdir( "..\\..\\bin\\win64\\" .. compiler .. "\\%{cfg.buildcfg}\\" .. g_folder_demos )
			objdir( "!..\\..\\bin\\win64\\" .. compiler .. "\\%{cfg.buildcfg}\\" .. g_folder_demos .. "intermediate" )

			debugcommand( "..\\..\\bin\\win64\\" .. compiler .. "\\%{cfg.buildcfg}\\" .. g_folder_demos .. demo_name .. ".exe" )
		filter {}
	else
		filter ( "platforms:win64-" .. compiler )
			buildcommands (
				"..\\" .. g_folder_scripts .. "build_clang_gcc.bat --output " .. demo_name .. ".exe" .. " --compiler " .. compiler .. " --config %{cfg.buildcfg} --source " .. g_folder_demos .. demo_name .. "\\" .. demo_name .. "." .. language_file_ext
			)

			rebuildcommands (
				"..\\" .. g_folder_scripts .. "build_clang_gcc.bat --output " .. demo_name .. ".exe" .. " --compiler " .. compiler .. " --config %{cfg.buildcfg} --source " .. g_folder_demos .. demo_name .. "\\" .. demo_name .. "." .. language_file_ext
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
end

function make_demo_project( demo_name )
	project( demo_name )
	location( g_generated_project_files_root )

	files {
		"..\\..\\" .. g_folder_demos .. demo_name .. "\\**.c",
		"..\\..\\" .. g_folder_demos .. demo_name .. "\\**.h",
		"..\\..\\" .. g_folder_demos .. demo_name .. "\\**.cpp",
		"..\\..\\" .. g_folder_demos .. demo_name .. "\\**.inl"
	}

	defines {
	}

	sysincludedirs {
	}

	syslibdirs {
	}

	debugdir( "$(SolutionDir)..\\" )

	set_binaries_and_build_commands( demo_name, "c",   "clang",   "__clang__" )
    set_binaries_and_build_commands( demo_name, "cpp", "clang++", "__clang__" )

    set_binaries_and_build_commands( demo_name, "c",   "gcc",     "__GNUC__" )
    set_binaries_and_build_commands( demo_name, "cpp", "g++",     "__GNUC__" )

    set_binaries_and_build_commands( demo_name, "c",   "msvc",    "" )
    set_binaries_and_build_commands( demo_name, "cpp", "msvc",    "" )

	filter "configurations:debug"
		defines {
			"_DEBUG"
		}

	filter "configurations:release"
		defines {
			"NDEBUG"
		}
	filter {}
end


g_demos_names = {
	"automation_c",
	"automation_cpp",
	"scale_test_c",
	"no_counter"
}

group( "demos" )
g_demos_names_length = array_length( g_demos_names )
for i = 1, g_demos_names_length do
	make_demo_project( g_demos_names[i] )
end