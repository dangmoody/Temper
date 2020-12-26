# Temper

[![Build Status](https://travis-ci.com/dangmoody/temper.svg?branch=master)](https://travis-ci.com/dangmoody/temper)

A Single-header-only test framework, written in C99.

Based on [greatest](https://github.com/silentbicycle/greatest).

Go and show the author of greatest some love - I would probably have
never written this library without seeing greatest or how it works.

Distributed under MIT License.  See LICENSE file for details.

Documentation is covered in this README and in the main comment at the top of the header.

Temper is compiled with all the following flags turned on (GCC/clang):
```
-Wall -Wextra -Werror -Wpedantic -Weverything
```

So you shouldn't need to disable any warnings etc. in order to plug Temper into your project.  It should 'just work' out of the box.


Another testing framework?
--------------------------
I like greatest, but there were just a couple of things that slightly bothered me.  So I decided to make one for me that fits my needs and I can maintain at my own free will.

I've always had pain trying to install GTest and make it work on projects and I don't particularly love the output it gives.  It's nice enough when you get it working, but rather cumbersome IMO.

I like to open-source most of the things I make in the hope it will be useful to someone else too.


Installation
------------
Download `temper.h` and include it in your project.  Done!


Code Usage
----------
Temper requires only one call to setup "defs".  These must be in the same
file as main().  Temper also tracks the return code:

```C
TEMPER_DEFS();

int main( int argc, char** argv ) {
	// do your tests, suites, whatever

	TEMPER_SHOW_STATS();

	return TEMPER_EXIT_CODE();
}
```

```TEMPER_SHOW_STATS();``` prints the stats on passed, failed, and skipped
tests.

To create a test:
```C
TEMPER_TEST( XShouldEqual0 ) {
	float x = 0.0f;
	TEMPER_EXPECT_TRUE( x == 0.0f );

	TEMPER_PASS();
}
```

To then run that test:
```C
TEMPER_RUN_TEST( XShouldEqual0 );
```

The following assert-style macros are given; they do what you'd expect:
* ```TEMPER_EXPECT_TRUE( condition );```
* ```TEMPER_EXPECT_FALSE( condition );```

The following macros are given for return results of a test; they do what
you'd expect:
* ```TEMPER_PASS();```
* ```TEMPER_FAIL();```

In order to make a test suite that runs a series of tests:
```C
TEMPER_SUITE( TheSuite ) {
	TEMPER_RUN_TEST( XShouldEqual0 );
	TEMPER_RUN_TEST( SomeOtherTest );
	TEMPER_RUN_TEST( SomeOtherOtherTest );
}
```

Tests can be run in and outside a test-suite, just like greatest.

You can also forward declare tests and suites:
```C
// forward declare a suite
TEMPER_SUITE_EXTERN( TheSuite );

// forward declare a test
TEMPER_TEST_EXTERN( XShouldEqual0 );
```

If you want to skip a test:
```C
TEMPER_SKIP_TEST( XShouldEqual0, "TeamCity doesn't like this test for some reason..." );
```

Temper will then mark the test as skipped and display the reason
message in the console, for example:
```C
SKIPPED: XShouldEqual0: "TeamCity doesn't like this test for some reason...".
```

You can also specify callbacks to run before and after each test and suite
is run:
```C
// per suite
TEMPER_SET_SUITE_START_CALLBACK( OnSuiteStarting, userdata );
TEMPER_SET_SUITE_END_CALLBACK( OnSuiteEnded, userdata );

// per test
TEMPER_SET_TEST_START_CALLBAK( OnTestStarting, userdata );
TEMPER_SET_TEST_END_CALLBAK( OnTestEnded, userdata );
```

The start callback gets called before just the test/suite runs and the end
callback gets called just as the test/suite has finished running, before the
console output.  Both callbacks return void and take `void*` as arguments so
you may pass through them whatever you like.

Any functions with "Internal" in the name means you probably shouldn't go
touching it.

Command Line Usage
------------------
Temper supports a few command line options:

```
-h
--help
	Shows this help and exits the program.

-t <name>
	Only run the test with the given name.

-s <suite>
	Only run the suite with the given name.

-a
	Abort immediately on test failure.

-c
	Enable colored output.

--time-unit=<unit>
	Set the timer unit of measurement.
	Can be either: clocks, ns, us, ms, or seconds.
```

If you don't want to set these options via command line and instead do it
via code, you can do that.  Temper has flags that you can set (```temperFlags_t```):
```C
TEMPER_TURN_FLAG_ON( flag );
TEMPER_TURN_FLAG_OFF( flag );
```

And to filter tests without command line args:
```C
// tell Temper that you only want to run this suite
// you will still need to manually run it
TEMPER_FILTER_SUITE( TheSuite );

// tell Temper that you only want to run this test
// you will still need to manually run it
TEMPER_FILTER_TEST( XShouldEqual0 );
```

To set the time unit, you'll need to set the `temperTimeUnit_t` enum via (for example):

```C
// sets the unit of measurement for how long tests take to run to microseconds
TEMPER_SET_TIME_UNIT( TEMPER_TIME_UNIT_US );
```


Special Thanks To:
------------------
* Zack Dutton	-	bug reports and testing
