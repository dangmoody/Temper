#define TEMPER_IMPLEMENTATION
#include "../../temper.h"

#ifdef __clang__
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#pragma clang diagnostic ignored "-Wc++98-compat"
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

//----------------------------------------------------------

struct TestingStruct {
public:
	TestingStruct( int newA, int newB )
		: a( newA )
		, b( newB ) {
	}

	int a, b;
};

//----------------------------------------------------------

template<typename T>
struct TestingTemplateStruct {
public:
	TestingTemplateStruct( T newA, T newB )
		: a( newA )
		, b( newB ) {
	}

	T DoSomeMath() {
		return a * b;
	}

	T a, b;
};

//----------------------------------------------------------

class TestingClassA {
public:
	TestingClassA( int newA, int newB )
		: a( newA )
		, b( newB )
		, result( 0 ) {
	}

	virtual void DoSomeMath() {
		result = a * b;
	}

	int a, b, result;
};

//----------------------------------------------------------

class TestingClassB : public TestingClassA {
public:
	TestingClassB( int newA, int newB )
		: TestingClassA( newA, newB ) {
	}

	virtual void DoSomeMath() override {
		result = a + ( b * 2 );
	}
};

typedef int( *TestingLambda )( const int a, const int b );

//----------------------------------------------------------

TEMPER_PARAMETRIC( ParsingStructs, TEMPER_FLAG_SHOULD_RUN, const TestingStruct& theStruct, const int expectedA, const int expectedB ) {
	TEMPER_CHECK_TRUE_M( theStruct.a == expectedA && theStruct.b == expectedB, "parsing structs in parametrics is broken." );
}

//----------------------------------------------------------

TEMPER_INVOKE_PARAMETRIC_TEST( ParsingStructs, TestingStruct( 4, 7 ), 4, 7 );
TEMPER_INVOKE_PARAMETRIC_TEST( ParsingStructs, TestingStruct( 2, 18 ), 2, 18 );

//----------------------------------------------------------

TEMPER_PARAMETRIC( ParsingSimpleClasses, TEMPER_FLAG_SHOULD_RUN, TestingClassA theClass, const int expectedResult ) {
	theClass.DoSomeMath();
	TEMPER_CHECK_EQUAL_M( theClass.result, expectedResult, "parsing classes in parametrics is broken." );
}

//----------------------------------------------------------

TEMPER_INVOKE_PARAMETRIC_TEST( ParsingSimpleClasses, TestingClassA( 2, 4 ), 8 );
TEMPER_INVOKE_PARAMETRIC_TEST( ParsingSimpleClasses, TestingClassA( 5, 10 ), 50 );

//----------------------------------------------------------

TEMPER_PARAMETRIC( ParsingComplexClasses, TEMPER_FLAG_SHOULD_RUN, TestingClassB theClass, const int expectedResult ) {
	theClass.DoSomeMath();
	TEMPER_CHECK_EQUAL_M( theClass.result, expectedResult, "parsing complex classes in parametrics is broken." );
}

//----------------------------------------------------------

TEMPER_INVOKE_PARAMETRIC_TEST( ParsingComplexClasses, TestingClassB( 5, 5 ), 15 );
TEMPER_INVOKE_PARAMETRIC_TEST( ParsingComplexClasses, TestingClassB( 21, 2 ), 25 );

//----------------------------------------------------------

TEMPER_PARAMETRIC( ParsingLambdas, TEMPER_FLAG_SHOULD_RUN, const TestingLambda theLambda, const int a, const int b, const int expectedResult ) {
	const int result = theLambda( a, b );
	TEMPER_CHECK_EQUAL_M( result, expectedResult, "parsing lambdas in parametrics is broken." );
}

//----------------------------------------------------------

TEMPER_INVOKE_PARAMETRIC_TEST( ParsingLambdas, []( const int a, const int b ) {return a + b; }, 5, 2, 7 );
TEMPER_INVOKE_PARAMETRIC_TEST( ParsingLambdas, []( const int a, const int b ) {return a - b; }, 5, 2, 3 );
TEMPER_INVOKE_PARAMETRIC_TEST( ParsingLambdas, []( const int a, const int b ) {return a * b; }, 5, 2, 10 );

//----------------------------------------------------------

TEMPER_PARAMETRIC( ParsingIntTemplates, TEMPER_FLAG_SHOULD_RUN, TestingTemplateStruct<int> theStruct, const int expectedResult ) {
	int result = theStruct.DoSomeMath();
	TEMPER_CHECK_EQUAL_M( result, expectedResult, "parsing lambdas in parametrics is broken." );
}

TEMPER_PARAMETRIC( ParsingFloatTemplates, TEMPER_FLAG_SHOULD_RUN, TestingTemplateStruct<float> theStruct, const float expectedResult ) {
	float result = theStruct.DoSomeMath();
	TEMPER_CHECK_FLOAT_EQUAL_M( result, expectedResult, "parsing lambdas in parametrics is broken." );
}

//----------------------------------------------------------

TEMPER_INVOKE_PARAMETRIC_TEST( ParsingIntTemplates, TestingTemplateStruct<int>( 2, 5 ), 10 );
TEMPER_INVOKE_PARAMETRIC_TEST( ParsingFloatTemplates, TestingTemplateStruct<float>( 1.0f, 0.5f ), 0.5f );

//----------------------------------------------------------

int main( int argc, char** argv ) {
	TEMPER_RUN( argc, argv );
	int exitCode = TEMPER_GET_EXIT_CODE();
	printf( "\nAutomation returned: %d.\n", exitCode );
	return exitCode;
}

//----------------------------------------------------------
