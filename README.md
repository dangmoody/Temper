# Temper V2

The new and improved C99, single-header-only, unit testing framework that looks and behaves like a modern test framework.
<Build status goes here>

![CI](https://github.com/dangmoody/Tantrum/workflows/CI/badge.svg)

## New features:
- Automatic test registration at compile time, no more manually registering tests.
- Parametric tests.
- Early exits for tests & a bunch of new condition macros.
- Handling errors from your program's log output (requires a bit of extra work on your part).
- A new output interface more accomodating of production applications and test filtering startup arguments.

It's not a new feature but worth stressing. It's still just the one header file. No .libs or .dlls to link against. Drop it into your project, tell it to run all tests somewhere in code and you're good to go! And once again; it's all written in C99 compliant code.

## Quick start guide:
___
To use TemperV2 we recommend the following layout. Add a compiler build definition for TEMPER_TESTS_ENABLED (or anyother macro of your choosing) and then write this main function:

##### Example Main function
___
```c
//#ifdef TEMPER_TESTS_ENABLED
int main( int argc, char** argv ) {
	TEMPER_SETUP(); // You MUST call this first for TemperV2 to set itself up correctly.
	return TEMPER_RUN_ALL_TESTS_WITH_ARGS( argc, argv ); // This actually executes the tests.
}
//#else
//int main( int argc, char** argv ){
//  Your production code goes here
//}
//#endif //TEMPER_TESTS_ENABLED
```

This will then produce an executable that will run all tests you have defined and return 0 if there were no errors. Following on from that we need to add some tests.

#### Defining tests
___
A test can be defined either as a part of or not a part of a suite, which is just a way of grouping tests in the output and also allows you to search for a bunch of tests by suite name as opposed to just test name.

```c
// Define a simple test with a Name only
TEMPER_TEST( TestName, TEMPER_TEST_FLAG_SHOULD_RUN )
{
	TEMPER_TEST_TRUE( 5 == 5 );
}

// Define a test as a part of a suite
TEMPER_SUITE_TEST( SuiteName, TestName2, TEMPER_TEST_FLAG_SHOULD_RUN )
{
	TEMPER_TEST_TRUE( 5 == 5 );
}

// Define a parametric test (can take whatever parameters you like)
TEMPER_DECLARE_PARAMETRIC_TEST( TestName3, TEMPER_TEST_FLAG_SHOULD_RUN, int param1, int param2 )
{
	TEMPER_TEST_EQUAL( param1, param2 );
}

// Declare invokations to the parametric test. Must have matching arguments filled out.
TEMPER_INVOKE_PARAMETRIC_TEST(TestName3, Check5And5, 5, 5); // will work
TEMPER_INVOKE_PARAMETRIC_TEST(TestName3, Check5And6, 5, 6); // will fail
TEMPER_INVOKE_PARAMETRIC_TEST(TestName3, Check7And7, 7, 7); // will work

// Define a parametric test as a part of a suite
TEMPER_DECLARE_PARAMETRIC_SUITE_TEST( SuiteName, TestName4, TEMPER_TEST_FLAG_SHOULD_RUN, int param1, int param2 )
{
	TEMPER_TEST_EQUAL( param1, param2 );
}

// You invoke a suite parametric test in the same way you would a non-suite parametric test.
TEMPER_INVOKE_PARAMETRIC_TEST( TestName4, Check5And5, 5, 5 ); // will work
TEMPER_INVOKE_PARAMETRIC_TEST( TestName4, Check5And6, 5, 6 ); // will fail
TEMPER_INVOKE_PARAMETRIC_TEST( TestName4, Check7And7, 7, 7 ); // will work
```

#### Test cases / Conditional macros
___
|Name|Description|
| -- | --------- |
|TEST_TRUE( 5 == 5 )|Passes if the condition is true, otherwise it'll log an error|
|TEMPER_TEST_FALSE( 5 == 6 )| Passes if the condition is false, otheriwse it'll log an error|
|TEMPER_TEST_EQUAL( 5, 5 )| Passes if the two parameters are the same, otheriwse it'll log an error|
|TEMPER_TEST_NOT_EQUAL( 5, 6 )| Passes if two parameters are NOT the same, otheriwse it'll log an error|
|TEMPER_TEST_FLOAT_EQUAL( 5.5f, 5.5f )| Passes if the two parameters are the same or within a predefined tolerance, otheriwse it'll log an error|
|TEMPER_TEST_ALMOST_EQUAL( 5.5f, 6.7f, 2.0f )| Passes if the two parameters are the same or within a specified tolerance, otheriwse it'll log an error|
|TEMPER_TEST_NOT_ALMOST_EQUAL( 5.5f, 6.7f, 1.0f )| Passes if the two parameters are different beyond a specified tolerance, otheriwse it'll log an error|

It's worth pointing out that all of these conditions have optional suffixes which you can apply for more options:

#### Suffixes for test macros
|Suffix|Description|
| ---- | --------- |
|_M|Allows you to append a string parameter that will be output if the condition fails.|
|_OR_ABORT|If this condition fails the whole test will exit early|
|_OR_ABORT_M|Allows you to append a string parameter that will be output if the condition fails, it will also have the test exit early.|

#### Examples of Suffixes:
```c
- TEMPER_TEST_TRUE(5 == 6); // Will just log a standard error when it fails
- TEMPER_TEST_TRUE_M(5 == 6, "Maths is broken."); // Will print your message as well when it fails.
- TEMPER_TEST_TRUE_OR_ABORT(5 == 6); // Will just log a standard error and make the test exit early when it fails.
- TEMPER_TEST_TRUE_OR_ABORT_M(5 == 6, "Maths is broken."); // Will make your test exit early and print your messsage.
```

#### Contributing code and making the Temper2 header more useful to yourself and the world?
Yes!