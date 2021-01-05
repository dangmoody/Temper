# Contributing

House Rules
-----------
1. Work off master branch only.  Do not make separate branches.
2. Always assign a PR reviewer and wait for them to green-light your PR before merging.
3. We track bugs etc. via the GitHub issue tracker.


Building The Project
--------------------
1. Clone the git repo.
2. If on Windows:
	* If you want to use Visual Studio:
		* Make sure you have Visual Studio 2019 installed.
		* Run `.\scripts\generate_vs2019.bat`.
	* If you do NOT want to use Visual Studio: 
		* Run `.\scripts\build_clang_gcc.bat` to build a demo for Clang/GCC.
		* Run `.\scripts\build_msvc.bat` to build a demo for MSVC.
3. If on MacOS/Linux:
	* Run `.\scripts\build_clang_gcc.sh` to build a demo for Clang/GCC.


How To Add A Demo
-----------------
1. Make your demo folder inside `demos/`.
2. Go to `tools/premake5/premake5.lua` and add the demo name (also the folder name) to the `demos_names` array at the bottom of the file.
3. You should now be able to build the demo like you can all the others.