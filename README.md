<img align="left" src="https://github.com/dangmoody/Tantrum/blob/master/doc/DarkTheme.png" width=128>

# Temper

![CI](https://github.com/dangmoody/Tantrum/workflows/CI/badge.svg)

The new and improved C99, single-header-only, unit testing framework.

Distributed under the MIT license.  See [LICENSE](https://github.com/dangmoody/Tantrum/blob/master/LICENSE) file for details.

___
## Features:

- Automatic test registration at compile time, simply write your test and it will get called for you.
- Parametric tests that don't suck.
- Low friction, easily overridable functions and constants to help hook Temper into your codebase.
- Unintrusive STB style source to keep big operating system includes out of your header files.
- Support for Clang, GCC, and MSVC across Windows, Mac OS, and Linux on x64 (support for ARM in progress).

___
## Installation

Download the latest release from the [releases](https://github.com/dangmoody/Tantrum/releases/latest) tab.

Include `temper.h` and define `TEMPER_IMPLEMENTATION` in one source file (just like the [stb libraries](https://github.com/nothings/stb)).

#### Quick start guide:

```c
#define TEMPER_IMPLEMENTATION // Creates the source definitions for temper
#include <temper.h>

// Write some tests

int main( int argc, char** argv )
{
	TEMPER_RUN( argc, argv ); // Runs all your tests - parse 0 and NULL as parameters if you don't use start Args
	return TEMPER_GET_EXIT_CODE(); // Fetches your return code
}
```
___
#### Compiling

On Windows and Mac OS you shouldn't need to do anything extra on your part to get Temper to compile correctly.  There should be no other dependencies that are required.  If you find that there are, please submit a [bug report](https://github.com/dangmoody/Tantrum/issues).

If you are compiling Temper on Linux and you are NOT overriding the default internal functions then you will need to make sure you pass the following arguments to your compiler/linker:
- `-ldl` - required if you're not overriding the `LoadEXEHandle()` and `UnloadEXEHandle()` functions.
- `-lpthread` - required if you're not overriding the `RunTestThread()` function.
- `--export-dynamic` - or some other equivalent, required to allow the compiler to export the test functions so they can be called dynamically by Temper at runtime.

When compiled, this will then produce an executable that will run all tests you have defined and return `TEMPDERDEV__EXIT_SUCCESS` (overridable) if there were no errors.  If there were errors then the program will return `TEMPDERDEV__EXIT_FAILURE` (overridable).

___
## Defining tests

A test can be defined either as a part of or not a part of a suite and with or without parameters. You can even mute it so it will be skipped when it comes time for Temper to run it by just changing the `TEMPER_FLAG` parameter.

#### Writing tests

```c
// Define a simple test with a Name only
TEMPER_TEST( TestName, TEMPER_FLAG_SHOULD_RUN )
{
	TEMPER_CHECK_TRUE( 69 == 105 );
}

// Define a test as a part of a suite
TEMPER_SUITE_TEST( SuiteName, TestName2, TEMPER_FLAG_SHOULD_RUN )
{
	TEMPER_CHECK_TRUE( 69 == 420 );
}

// Define a parametric test (can take whatever parameters you like)
TEMPER_PARAMETRIC( TestName3, TEMPER_FLAG_SHOULD_RUN, int param1, int param2 )
{
	TEMPER_CHECK_EQUAL( param1, param2 );
}

// Declare invokations to the parametric test. Must have matching arguments filled out.
TEMPER_INVOKE_PARAMETRIC_TEST( TestName3, 5, 5 ); // will work
TEMPER_INVOKE_PARAMETRIC_TEST( TestName3, 5, 6 ); // will fail
TEMPER_INVOKE_PARAMETRIC_TEST( TestName3, 7, 7 ); // will work

// Define a parametric test as a part of a suite
TEMPER_PARAMETRIC_SUITE( SuiteName, TestName4, TEMPER_FLAG_SHOULD_RUN, int param1, int param2 )
{
	TEMPER_CHECK_EQUAL( param1, param2 );
}

// You invoke a suite parametric test in the same way you would a non-suite parametric test.
TEMPER_INVOKE_PARAMETRIC_TEST( TestName4, 5, 5 ); // will work
TEMPER_INVOKE_PARAMETRIC_TEST( TestName4, 5, 6 ); // will fail
TEMPER_INVOKE_PARAMETRIC_TEST( TestName4, 7, 7 ); // will work

// If you add _C to the end of any of the test definition macros you
// can also feed in an optional OnBeforeTest and OnAfterTest callback
// function - useful for setting up and tearing down a common environment
// for multiple tests.
```

___
#### Test execution flags

There are 3 different flags you can apply to your tests:
- TEMPER_FLAG_SHOULD_RUN
  - This marks the test to Temper as something it should run.
- TEMPER_FLAG_SHOULD_SKIP
  - Intended for usage in hotfixes when you just need your build to go green.
- TEMPER_FLAG_DEPRECATED
  - Functionally identical to the above flag but not intended for hotfixes and more a statement about the nature of this feature you've a test for.

___
#### Test cases / Conditional macros

|                        Name                         |                                               Description                                                |
| --------------------------------------------------- | -------------------------------------------------------------------------------------------------------- |
| `TEMPER_CHECK_TRUE( 5 == 5 )`                       | Passes if the condition is true, otherwise it'll log an error                                            |
| `TEMPER_CHECK_FALSE( 5 == 6 )`                      | Passes if the condition is false, otheriwse it'll log an error                                           |
| `TEMPER_CHECK_EQUAL( 5, 5 )`                        | Passes if the two parameters are the same, otheriwse it'll log an error                                  |
| `TEMPER_CHECK_NOT_EQUAL( 5, 6 )`                    | Passes if two parameters are NOT the same, otheriwse it'll log an error                                  |
| `TEMPER_CHECK_FLOAT_EQUAL( 5.5f, 5.5f )`            | Passes if the two parameters are the same or within a predefined tolerance, otheriwse it'll log an error |
| `TEMPER_CHECK_ALMOST_EQUAL( 5.5f, 6.7f, 2.0f )`     | Passes if the two parameters are the same or within a specified tolerance, otheriwse it'll log an error  |
| `TEMPER_CHECK_NOT_ALMOST_EQUAL( 5.5f, 6.7f, 1.0f )` | Passes if the two parameters are different beyond a specified tolerance, otheriwse it'll log an error    |

It's worth pointing out that all of these conditions have optional suffixes which you can apply for more options:

___
#### Suffixes for test macros

|    Suffix     |                                                        Description                                                         |
| ------------- | -------------------------------------------------------------------------------------------------------------------------- |
| `_M`          | Allows you to append a string parameter that will be output if the condition fails.                                        |
| `_A`          | If this condition fails the whole test will exit early                                                                     |
| `_AM`         | Allows you to append a string parameter that will be output if the condition fails, it will also have the test exit early. |

#### Examples of Suffixes:

```c
TEMPER_CHECK_TRUE( 5 == 6 ); // When this fails will log an error showing the condition on the file and line where if failed.
TEMPER_CHECK_TRUE_M( 5 == 6, "Maths is broken." ); // When this fails will log an error showing the condition on the file and line where it failed, along with the error message "Maths is broken".
TEMPER_CHECK_TRUE_A( 5 == 6 ); // Same as the TEMPER_CHECK_TRUE example, except it will also abort the test on failure.
TEMPER_CHECK_TRUE_AM( 5 == 6, "Maths is broken." ); // Same as the example above, except it will log the error message "Maths is broken" along with the condition on the file and line where it failed.
```

___
## Overriding internal functions

Temper has a number of user-overridable macros (E.G.: `TEMPERDEV_GET_PROC_ADDRESS`) which you can use to help hook Temper into your own codebase.

If you are running on a platform that **ISN'T** Windows, Mac OS, or Linux then you will definitely want to override these functions as some of Temper's internal functions make calls to their respective OS-level API.

___
## Command line arguments

Temper supports the following command line arguments:

```
[-h|--help]
	Shows this help and then exits.

-t <test>
	Only run the test with the given name.

-s <suite>
	Only run tests in the suite with the given name.

-p
	Enable partial filtering, which will only run tests and suites that contain the text specified in the filters.

--time-unit [seconds|ms|us|ns|clocks]
	Set the units to measure test times in.
	The default is microseconds.
```

___
## Contributing

Yes!

If you want to submit an idea/bug then use the [GitHub issue tracker](https://github.com/dangmoody/Tantrum/issues).

If you want to submit code then we are open to pull requests.  See [contributing.md](https://github.com/dangmoody/Tantrum/blob/master/doc/how_to_contribute.md) for details.

___
## Credits

* Dan Moody
* Mike Young

#### Special thanks to:

* [Danny Grezel](https://linktr.ee/dannygrzlart) - logo!
* Zack Dutton - Bug reports and testing.