generated_project_files_root = "..\\..\\vs2019-gen"
folder_code = "code\\"
folder_3rdparty = "3rdparty\\"
folder_tools = "tools\\"
folder_scripts = "scripts\\"


workspace( "sperm-racer" )
	location( generated_project_files_root )

	platforms { "win64" }
	configurations { "debug", "release" }

	startproject( "sperm-racer" )

	architecture( "x64" )


--[[
  ,ad8888ba,                                        
 d8"'    `"8b                                       
d8'                                                 
88              ,adPPYba,   8b,dPPYba,   ,adPPYba,  
88             a8"     "8a  88P'   "Y8  a8P_____88  
Y8,            8b       d8  88          8PP"""""""  
 Y8a.    .a8P  "8a,   ,a8"  88          "8b,   ,aa  
  `"Y8888Y"'    `"YbbdP"'   88           `"Ybbd8"'  
]]
project( "core" )
	location( generated_project_files_root )

	files {
		"..\\..\\" .. folder_code .. "core\\**.h",
		"..\\..\\" .. folder_code .. "core\\**.c"
	}

	defines {
		"SR_USE_XXHASH"
	}

	sysincludedirs {
		"..\\" .. folder_code .. "3rdparty\\include"
	}

	syslibdirs { "..\\" .. folder_code .. "3rdparty\\lib" }

	-- required because VS will create these folders if they don't exist
	targetdir( "..\\..\\bin\\%{cfg.platform}\\%{cfg.buildcfg}" )
	objdir( "..\\..\\bin\\%{cfg.platform}\\%{cfg.buildcfg}\\intermediate\\core" )

	filter "platforms:win64"
		kind( "MakeFile" )

		buildcommands (
			"..\\" .. folder_scripts .. "\\build_core.bat %{cfg.buildcfg}"
		)

		rebuildcommands (
			"..\\" .. folder_scripts .. "\\build_core.bat %{cfg.buildcfg}"
		)

		cleancommands (
			"..\\" .. folder_scripts .. "\\clean.bat"
		)

		defines {
			"__clang__"
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


--[[
  ,ad8888ba,                                                  88888888ba,    88           88           
 d8"'    `"8b                                                 88      `"8b   88           88           
d8'                                                           88        `8b  88           88           
88             ,adPPYYba,  88,dPYba,,adPYba,    ,adPPYba,     88         88  88           88           
88      88888  ""     `Y8  88P'   "88"    "8a  a8P_____88     88         88  88           88           
Y8,        88  ,adPPPPP88  88      88      88  8PP"""""""     88         8P  88           88           
 Y8a.    .a88  88,    ,88  88      88      88  "8b,   ,aa     88      .a8P   88           88           
  `"Y88888P"   `"8bbdP"Y8  88      88      88   `"Ybbd8"'     88888888Y"'    88888888888  88888888888  
]]
project( "game-dll" )
	location( generated_project_files_root )

	files {
		"..\\..\\" .. folder_code .. "game-dll\\**.h",
		"..\\..\\" .. folder_code .. "game-dll\\**.c",
		"..\\..\\" .. folder_code .. "game-dll\\**.cpp",
		"..\\..\\" .. folder_code .. "game-dll\\**.h",
		"..\\..\\" .. folder_code .. "game-dll\\**.inl"
	}

	defines {
		"SR_USE_VULKAN",
		"SR_USE_CGLTF",
		"SR_USE_STB_IMAGE",
		"SR_USE_JSMN",
		"SR_USE_CIMGUI"
	}

	sysincludedirs {
		"..\\..\\" .. folder_code .. "core",
		"..\\..\\" .. folder_3rdparty .. "include",
		"$(VULKAN_SDK)\\Include\\vulkan"
	}

	syslibdirs {
		"..\\..\\" .. folder_3rdparty .. "\\lib"
	}

	-- required because VS will create these folders if they don't exist
	targetdir( "..\\..\\bin\\%{cfg.platform}\\%{cfg.buildcfg}" )
	objdir( "..\\..\\bin\\%{cfg.platform}\\%{cfg.buildcfg}\\intermediate\\game-dll" )

	debugcommand( "..\\..\\" .. "bin\\%{cfg.platform}\\%{cfg.buildcfg}\\sperm-racer-dll.dll" )

	filter "platforms:win64"
		kind( "MakeFile" )

		buildcommands (
			"..\\" .. folder_scripts .. "\\build_game_dll.bat %{cfg.buildcfg}"
		)

		rebuildcommands (
			"..\\" .. folder_scripts .. "\\build_game_dll.bat %{cfg.buildcfg}"
		)

		cleancommands (
			"..\\" .. folder_scripts .. "\\clean.bat"
		)

		defines {
			"__clang__"
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


--[[
  ,ad8888ba,                                                  88888888888  8b        d8  88888888888  
 d8"'    `"8b                                                 88            Y8,    ,8P   88           
d8'                                                           88             `8b  d8'    88           
88             ,adPPYYba,  88,dPYba,,adPYba,    ,adPPYba,     88aaaaa          Y88P      88aaaaa      
88      88888  ""     `Y8  88P'   "88"    "8a  a8P_____88     88"""""          d88b      88"""""      
Y8,        88  ,adPPPPP88  88      88      88  8PP"""""""     88             ,8P  Y8,    88           
 Y8a.    .a88  88,    ,88  88      88      88  "8b,   ,aa     88            d8'    `8b   88           
  `"Y88888P"   `"8bbdP"Y8  88      88      88   `"Ybbd8"'     88888888888  8P        Y8  88888888888  
]]
project( "sperm-racer" )
	location( generated_project_files_root )

	files {
		"..\\..\\" .. folder_code .. "game-exe\\**.h",
		"..\\..\\" .. folder_code .. "game-exe\\**.c",
		"..\\..\\" .. folder_code .. "game-exe\\**.cpp",
		"..\\..\\" .. folder_code .. "game-exe\\**.h",
		"..\\..\\" .. folder_code .. "game-exe\\**.inl"
	}

	defines {
	}

	sysincludedirs {
		"..\\..\\" .. folder_code .. "core\\"
	}

	syslibdirs {
	}

	-- required because VS will create these folders if they don't exist
	targetdir( "..\\..\\bin\\%{cfg.platform}\\%{cfg.buildcfg}" )
	objdir( "..\\..\\bin\\%{cfg.platform}\\%{cfg.buildcfg}\\intermediate\\sperm-racer" )

	debugdir( "$(SolutionDir)..\\" )

	debugcommand( "..\\..\\bin\\%{cfg.platform}\\%{cfg.buildcfg}\\sperm-racer.exe" )

	filter "platforms:win64"
		kind( "MakeFile" )

		buildcommands (
			"..\\" .. folder_scripts .. "\\build_game_exe.bat %{cfg.buildcfg}"
		)

		rebuildcommands (
			"..\\" .. folder_scripts .. "\\build_game_exe.bat %{cfg.buildcfg}"
		)

		cleancommands (
			"..\\" .. folder_scripts .. "\\clean.bat"
		)

		defines {
			"__clang__"
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


--[[
888888888888                       88             
     88                            88             
     88                            88             
     88   ,adPPYba,    ,adPPYba,   88  ,adPPYba,  
     88  a8"     "8a  a8"     "8a  88  I8[    ""  
     88  8b       d8  8b       d8  88   `"Y8ba,   
     88  "8a,   ,a8"  "8a,   ,a8"  88  aa    ]8I  
     88   `"YbbdP"'    `"YbbdP"'   88  `"YbbdP"'  
]]
group( "tools" )
	dofile "..\\hash\\hash.premake.lua"
	dofile "..\\shader_compiler\\shader_compiler.premake.lua"