# Contributing

## House Rules
1. We track bugs etc. via the GitHub issue tracker, so use that.
2. Always assign a PR reviewer and wait for them to green-light your PR before merging.


## Building The Project

#### Pre-requisites
* [Builder](https://github.com/dangmoody/Builder)
* If on Windows and using Clang or GCC: make sure the compiler is added to your `PATH`.

#### Instructions
1. Clone the git repo.
2. To build and run all tests:
	* On Windows: run `.\scripts\build_and_test_all.bat`
	* On MacOS/Linux: run `./scripts/build_and_test_all.sh`
3. To build a specific config: `~/builder/bin/builder build.cpp --config=<config>` where `<config>` is one of the configs listed in `build.cpp`.  Append `--release` for a release build, `--gcc` for GCC, or `--msvc` for MSVC (Windows only). Clang is the default compiler.
4. To generate a Visual Studio solution: `~/builder/bin/builder build.cpp --sln`


## Pull Requests
Your PR has a higher chance of being accepted if it fulfills at least one of the following criteria:
* It fixes a bug listed in the [issue tracker](https://github.com/dangmoody/Tantrum/issues).
* You have fixed an un-named `TODO` for us in the code somewhere.
* It does something completely awesome that will definitely help Temper in some way.

If your change doesn't do any of these things then it doesn't mean it won't get accepted, it just means your PR stands less of a chance of being accepted.

We don't bite and we're open to ideas.

## Recommended Reading
For Temper we like to follow the [Handmade Network's excellent written piece](https://handmade.network/wiki/7138-how_to_write_better_game_libraries) on how to write better game libraries for guiding principles.  We don't follow it super strictly, but we do refer to it often.