/*
===========================================================================

HLML.

MIT License

Copyright (c) 2019 Dan Moody

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

===========================================================================
*/

// THIS FILE WAS AUTOMATICALLY GENERATED BY A TOOL.
// EDITING THIS FILE MAY CAUSE SIDE EFFECTS.
// DO SO AT YOUR OWN RISK.

TEMPER_PARAMETRIC( Test_bool3_bool3_all, TEMPER_FLAG_SHOULD_RUN, const bool3* x, const bool32_t expectedAnswer )
{
	bool32_t actualResult = bool3_bool3_all( x );
	TEMPER_CHECK_TRUE( actualResult == expectedAnswer );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_bool3_all,
	&(bool3) { true, true, true },
	true
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_bool3_all,
	&(bool3) { true, false, false },
	false
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_bool3_all,
	&(bool3) { false, true, true },
	false
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_bool3_all,
	&(bool3) { false, true, false },
	false
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_bool3_all,
	&(bool3) { false, false, false },
	false
);

TEMPER_PARAMETRIC( Test_bool3_bool3_any, TEMPER_FLAG_SHOULD_RUN, const bool3* x, const bool32_t expectedAnswer )
{
	bool32_t actualResult = bool3_bool3_any( x );
	TEMPER_CHECK_TRUE( actualResult == expectedAnswer );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_bool3_any,
	&(bool3) { true, true, true },
	true
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_bool3_any,
	&(bool3) { true, false, false },
	true
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_bool3_any,
	&(bool3) { false, true, true },
	true
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_bool3_any,
	&(bool3) { false, true, false },
	true
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_bool3_any,
	&(bool3) { false, false, false },
	false
);

TEMPER_PARAMETRIC( Test_bool3_lengthsq, TEMPER_FLAG_SHOULD_RUN, const bool3* vec, const float expectedAnswer )
{
	float actualResult = bool3_lengthsq( vec );
	TEMPER_CHECK_TRUE( floateq( actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_lengthsq,
	&(bool3) { false, false, false },
	0.000000f
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_lengthsq,
	&(bool3) { true, true, true },
	3.000000f
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_lengthsq,
	&(bool3) { true, true, true },
	12.000000f
);

TEMPER_PARAMETRIC( Test_bool3_length, TEMPER_FLAG_SHOULD_RUN, const bool3* vec, const float expectedAnswer )
{
	float actualResult = bool3_length( vec );
	TEMPER_CHECK_TRUE( floateq( actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_length,
	&(bool3) { false, false, false },
	0.000000f
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_length,
	&(bool3) { true, true, true },
	1.732051f
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_length,
	&(bool3) { true, true, true },
	3.464102f
);

TEMPER_PARAMETRIC( Test_bool3_dot, TEMPER_FLAG_SHOULD_RUN, const bool3* lhs, const bool3* rhs, const bool32_t expectedAnswer )
{
	bool32_t actualResult = bool3_dot( lhs, rhs );
	TEMPER_CHECK_TRUE( actualResult == expectedAnswer );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_dot,
	&(bool3) { false, false, false },
	&(bool3) { true, true, true },
	false
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_dot,
	&(bool3) { true, true, true },
	&(bool3) { true, true, true },
	true
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_bool3_dot,
	&(bool3) { true, true, true },
	&(bool3) { true, true, true },
	true
);

