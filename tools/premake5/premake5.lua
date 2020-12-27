generated_project_files_root = "..\\..\\vs2019-gen"
folder_demos = "demos\\"
folder_3rdparty = "3rdparty\\"
folder_tools = "tools\\"
folder_scripts = "scripts\\"

-- get length of array
-- DM: lua doesnt define this!?
function array_length( array )
	array_length = 0

	for i in pairs( array ) do
		array_length = array_length + 1
	end

	return array_length
end


workspace( "Tantrum" )
	location( generated_project_files_root )

	platforms { "win64" }
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
function make_demo_project( demo_name )
	project( demo_name )
	location( generated_project_files_root )

	files {
		"..\\..\\" .. folder_demos .. "**.h",
		"..\\..\\" .. folder_demos .. "**.c",
		"..\\..\\" .. folder_demos .. "**.cpp",
		"..\\..\\" .. folder_demos .. "**.h",
		"..\\..\\" .. folder_demos .. "**.inl"
	}

	defines {
	}

	sysincludedirs {
	}

	syslibdirs {
	}

	-- required because VS will create these folders if they don't exist
	targetdir( "..\\..\\bin\\%{cfg.platform}\\%{cfg.buildcfg}\\" .. folder_demos )
	objdir( "..\\..\\bin\\%{cfg.platform}\\%{cfg.buildcfg}\\" .. folder_demos .. "intermediate" )

	debugdir( "$(SolutionDir)..\\" )

	debugcommand( "..\\..\\bin\\%{cfg.platform}\\%{cfg.buildcfg}\\" .. folder_demos .. demo_name .. ".exe" )

	filter "platforms:win64"
		kind( "MakeFile" )

		buildcommands (
			"..\\" .. folder_scripts .. "\\build_demo.bat " .. demo_name .. " %{cfg.buildcfg}"
		)

		rebuildcommands (
			"..\\" .. folder_scripts .. "\\build_demo.bat " .. demo_name .. " %{cfg.buildcfg}"
		)

		cleancommands (
			"..\\" .. folder_scripts .. "\\clean.bat"
		)

		defines {
			"__clang__"	-- required, build system wont generate this for you
		}
	filter {}

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

demos_names = {
	"basic_c"
}

group( "demos" )
demos_names_length = array_length( demos_names )
for i = 1, demos_names_length do
	make_demo_project( demos_names[i] )
end