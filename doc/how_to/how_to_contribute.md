# Contributing

House Rules
-----------
1. Work off master branch only.  Do not make separate branches.
2. Always assign a PR reviewer and wait for them to green-light your PR before merging.

Building The Project
--------------------
1. Clone the git repo.
2. If on Windows:
	* If you want to use Visual Studio run `.\scripts\generate_vs2019.bat`
	* If you don't want to use Visual Studio then open your text editor at the project root folder.
	* If not using Visual Studio, run `.\scripts\build_demo.bat demos\<demo name> debug` (for example) to build a demo.


How To Add A Demo
-----------------
1. Make your demo folder inside `demos/`.
2. Go to `tools/premake5/premake5.lua` and add the demo name (also the folder name) to the `demos_names` array at the bottom of the file.
3. You should now be able to build the demo like you can all the others.