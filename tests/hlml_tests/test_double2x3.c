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

TEMPER_PARAMETRIC( Test_double2x3_less_than, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double2x3* rhs, const bool2x3* expectedAnswer )
{
	bool2x3 actualResult = double2x3_less_than( lhs, rhs );
	TEMPER_CHECK_TRUE( bool2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_less_than,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(bool2x3)
	{
		false, false, false,
		false, false, false
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_less_than,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(bool2x3)
	{
		true, true, true,
		true, true, true
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_less_than,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(bool2x3)
	{
		false, false, false,
		false, false, false
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_less_than,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(bool2x3)
	{
		false, false, false,
		false, false, false
	}
);

TEMPER_PARAMETRIC( Test_double2x3_less_than_equal, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double2x3* rhs, const bool2x3* expectedAnswer )
{
	bool2x3 actualResult = double2x3_less_than_equal( lhs, rhs );
	TEMPER_CHECK_TRUE( bool2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_less_than_equal,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(bool2x3)
	{
		true, true, true,
		true, true, true
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_less_than_equal,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(bool2x3)
	{
		true, true, true,
		true, true, true
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_less_than_equal,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(bool2x3)
	{
		true, true, true,
		true, true, true
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_less_than_equal,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(bool2x3)
	{
		false, false, false,
		false, false, false
	}
);

TEMPER_PARAMETRIC( Test_double2x3_greater_than, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double2x3* rhs, const bool2x3* expectedAnswer )
{
	bool2x3 actualResult = double2x3_greater_than( lhs, rhs );
	TEMPER_CHECK_TRUE( bool2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_greater_than,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(bool2x3)
	{
		false, false, false,
		false, false, false
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_greater_than,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(bool2x3)
	{
		false, false, false,
		false, false, false
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_greater_than,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(bool2x3)
	{
		false, false, false,
		false, false, false
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_greater_than,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(bool2x3)
	{
		true, true, true,
		true, true, true
	}
);

TEMPER_PARAMETRIC( Test_double2x3_greater_than_equal, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double2x3* rhs, const bool2x3* expectedAnswer )
{
	bool2x3 actualResult = double2x3_greater_than_equal( lhs, rhs );
	TEMPER_CHECK_TRUE( bool2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_greater_than_equal,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(bool2x3)
	{
		true, true, true,
		true, true, true
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_greater_than_equal,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(bool2x3)
	{
		false, false, false,
		false, false, false
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_greater_than_equal,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(bool2x3)
	{
		true, true, true,
		true, true, true
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_greater_than_equal,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(bool2x3)
	{
		true, true, true,
		true, true, true
	}
);

TEMPER_PARAMETRIC( Test_double2x3_cadds, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double rhs, const double2x3* expectedAnswer )
{
	double2x3 actualResult = double2x3_cadds( lhs, rhs );
	TEMPER_CHECK_TRUE( double2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cadds,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	1.000000f,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cadds,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	2.000000f,
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cadds,
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	},
	2.000000f,
	&(double2x3)
	{
		6.000000f, 6.000000f, 6.000000f,
		6.000000f, 6.000000f, 6.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cadds,
	&(double2x3)
	{
		8.000000f, 8.000000f, 8.000000f,
		8.000000f, 8.000000f, 8.000000f
	},
	4.000000f,
	&(double2x3)
	{
		12.000000f, 12.000000f, 12.000000f,
		12.000000f, 12.000000f, 12.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_csubs, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double rhs, const double2x3* expectedAnswer )
{
	double2x3 actualResult = double2x3_csubs( lhs, rhs );
	TEMPER_CHECK_TRUE( double2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_csubs,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	1.000000f,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_csubs,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	2.000000f,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_csubs,
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	},
	2.000000f,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_csubs,
	&(double2x3)
	{
		8.000000f, 8.000000f, 8.000000f,
		8.000000f, 8.000000f, 8.000000f
	},
	4.000000f,
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_cmuls, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double rhs, const double2x3* expectedAnswer )
{
	double2x3 actualResult = double2x3_cmuls( lhs, rhs );
	TEMPER_CHECK_TRUE( double2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cmuls,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	1.000000f,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cmuls,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	2.000000f,
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cmuls,
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	},
	2.000000f,
	&(double2x3)
	{
		8.000000f, 8.000000f, 8.000000f,
		8.000000f, 8.000000f, 8.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cmuls,
	&(double2x3)
	{
		8.000000f, 8.000000f, 8.000000f,
		8.000000f, 8.000000f, 8.000000f
	},
	4.000000f,
	&(double2x3)
	{
		32.000000f, 32.000000f, 32.000000f,
		32.000000f, 32.000000f, 32.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_cdivs, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double rhs, const double2x3* expectedAnswer )
{
	double2x3 actualResult = double2x3_cdivs( lhs, rhs );
	TEMPER_CHECK_TRUE( double2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cdivs,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	1.000000f,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cdivs,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	2.000000f,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cdivs,
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	},
	2.000000f,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cdivs,
	&(double2x3)
	{
		8.000000f, 8.000000f, 8.000000f,
		8.000000f, 8.000000f, 8.000000f
	},
	4.000000f,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_caddm, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double2x3* rhs, const double2x3* expectedAnswer )
{
	double2x3 actualResult = double2x3_caddm( lhs, rhs );
	TEMPER_CHECK_TRUE( double2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_caddm,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_caddm,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_caddm,
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		6.000000f, 6.000000f, 6.000000f,
		6.000000f, 6.000000f, 6.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_caddm,
	&(double2x3)
	{
		8.000000f, 8.000000f, 8.000000f,
		8.000000f, 8.000000f, 8.000000f
	},
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	},
	&(double2x3)
	{
		12.000000f, 12.000000f, 12.000000f,
		12.000000f, 12.000000f, 12.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_csubm, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double2x3* rhs, const double2x3* expectedAnswer )
{
	double2x3 actualResult = double2x3_csubm( lhs, rhs );
	TEMPER_CHECK_TRUE( double2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_csubm,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_csubm,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_csubm,
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_csubm,
	&(double2x3)
	{
		8.000000f, 8.000000f, 8.000000f,
		8.000000f, 8.000000f, 8.000000f
	},
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	},
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_cmulm, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double2x3* rhs, const double2x3* expectedAnswer )
{
	double2x3 actualResult = double2x3_cmulm( lhs, rhs );
	TEMPER_CHECK_TRUE( double2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cmulm,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cmulm,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cmulm,
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		8.000000f, 8.000000f, 8.000000f,
		8.000000f, 8.000000f, 8.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cmulm,
	&(double2x3)
	{
		8.000000f, 8.000000f, 8.000000f,
		8.000000f, 8.000000f, 8.000000f
	},
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	},
	&(double2x3)
	{
		32.000000f, 32.000000f, 32.000000f,
		32.000000f, 32.000000f, 32.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_cdivm, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double2x3* rhs, const double2x3* expectedAnswer )
{
	double2x3 actualResult = double2x3_cdivm( lhs, rhs );
	TEMPER_CHECK_TRUE( double2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cdivm,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cdivm,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cdivm,
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_cdivm,
	&(double2x3)
	{
		8.000000f, 8.000000f, 8.000000f,
		8.000000f, 8.000000f, 8.000000f
	},
	&(double2x3)
	{
		4.000000f, 4.000000f, 4.000000f,
		4.000000f, 4.000000f, 4.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_min, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double2x3* rhs, const double2x3* expectedAnswer )
{
	double2x3 actualResult = double2x3_min( lhs, rhs );
	TEMPER_CHECK_TRUE( double2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_min,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_min,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_max, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double2x3* rhs, const double2x3* expectedAnswer )
{
	double2x3 actualResult = double2x3_max( lhs, rhs );
	TEMPER_CHECK_TRUE( double2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_max,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_max,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_saturate, TEMPER_FLAG_SHOULD_RUN, const double2x3* x, const double2x3* expectedAnswer )
{
	double2x3 actualResult = double2x3_saturate( x );
	TEMPER_CHECK_TRUE( double2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_saturate,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_saturate,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_saturate,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_saturate,
	&(double2x3)
	{
		3.000000f, 3.000000f, 3.000000f,
		3.000000f, 3.000000f, 3.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_saturate,
	&(double2x3)
	{
		10.000000f, 10.000000f, 10.000000f,
		10.000000f, 10.000000f, 10.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_sign, TEMPER_FLAG_SHOULD_RUN, const double2x3* x, const int2x3* expectedAnswer )
{
	int2x3 actualResult = double2x3_sign( x );
	TEMPER_CHECK_TRUE( int2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_sign,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(int2x3)
	{
		0, 0, 0,
		0, 0, 0
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_sign,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(int2x3)
	{
		1, 1, 1,
		1, 1, 1
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_sign,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(int2x3)
	{
		1, 1, 1,
		1, 1, 1
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_sign,
	&(double2x3)
	{
		3.000000f, 3.000000f, 3.000000f,
		3.000000f, 3.000000f, 3.000000f
	},
	&(int2x3)
	{
		1, 1, 1,
		1, 1, 1
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_sign,
	&(double2x3)
	{
		-1.000000f, -1.000000f, -1.000000f,
		-1.000000f, -1.000000f, -1.000000f
	},
	&(int2x3)
	{
		-1, -1, -1,
		-1, -1, -1
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_sign,
	&(double2x3)
	{
		-2.000000f, -2.000000f, -2.000000f,
		-2.000000f, -2.000000f, -2.000000f
	},
	&(int2x3)
	{
		-1, -1, -1,
		-1, -1, -1
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_sign,
	&(double2x3)
	{
		-3.000000f, -3.000000f, -3.000000f,
		-3.000000f, -3.000000f, -3.000000f
	},
	&(int2x3)
	{
		-1, -1, -1,
		-1, -1, -1
	}
);

TEMPER_PARAMETRIC( Test_double2x3_lerp, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double2x3* rhs, const double t, const double2x3* expectedAnswer )
{
	double2x3 actualResult = double2x3_lerp( lhs, rhs, t );
	TEMPER_CHECK_TRUE( double2x3_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_lerp,
	&(double2x3)
	{
		0.000000f, 0.000000f, 0.000000f,
		0.000000f, 0.000000f, 0.000000f
	},
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	0.500000f,
	&(double2x3)
	{
		0.500000f, 0.500000f, 0.500000f,
		0.500000f, 0.500000f, 0.500000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_lerp,
	&(double2x3)
	{
		1.000000f, 1.000000f, 1.000000f,
		1.000000f, 1.000000f, 1.000000f
	},
	&(double2x3)
	{
		3.000000f, 3.000000f, 3.000000f,
		3.000000f, 3.000000f, 3.000000f
	},
	0.500000f,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_identity, TEMPER_FLAG_SHOULD_RUN, const double2x3* matrix, const bool expectedAnswer )
{
	double2x3 identityMat;
	double2x3_identity( &identityMat );
	bool isMatrixIdentity = double2x3_equals( &identityMat, matrix );
	TEMPER_CHECK_TRUE( isMatrixIdentity == expectedAnswer );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_identity,
	&(double2x3)
	{
		1.000000f, 0.000000f, 0.000000f,
		0.000000f, 1.000000f, 0.000000f
	},
	true
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_identity,
	&(double2x3)
	{
		1.000000f, 1.000000f, 0.000000f,
		0.000000f, 1.000000f, 0.000000f
	},
	false
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_identity,
	&(double2x3)
	{
		1.000000f, 0.000000f, 0.000000f,
		1.000000f, 1.000000f, 0.000000f
	},
	false
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_identity,
	&(double2x3)
	{
		1.000000f, 1.000000f, 0.000000f,
		1.000000f, 1.000000f, 0.000000f
	},
	false
);

TEMPER_PARAMETRIC( Test_double2x3_transpose, TEMPER_FLAG_SHOULD_RUN, const double2x3* matrix, const double3x2* expectedAnswer )
{
	double3x2 actualResult = double2x3_transpose( matrix );
	TEMPER_CHECK_TRUE( double3x2_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_transpose,
	&(double2x3)
	{
		1.000000f, 0.000000f, 0.000000f,
		0.000000f, 1.000000f, 0.000000f
	},
	&(double3x2)
	{
		1.000000f, 0.000000f,
		0.000000f, 1.000000f,
		0.000000f, 0.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_transpose,
	&(double2x3)
	{
		0.000000f, 1.000000f, 2.000000f,
		4.000000f, 5.000000f, 6.000000f
	},
	&(double3x2)
	{
		0.000000f, 4.000000f,
		1.000000f, 5.000000f,
		2.000000f, 6.000000f
	}
);

TEMPER_PARAMETRIC( Test_double2x3_mulm, TEMPER_FLAG_SHOULD_RUN, const double2x3* lhs, const double3x2* rhs, const double2x2* expectedAnswer )
{
	double2x2 actualResult = double2x3_mulm( lhs, rhs );
	TEMPER_CHECK_TRUE( double2x2_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_mulm,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double3x2)
	{
		4.000000f, 4.000000f,
		4.000000f, 4.000000f,
		4.000000f, 4.000000f
	},
	&(double2x2)
	{
		24.000000f, 24.000000f,
		24.000000f, 24.000000f
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_double2x3_mulm,
	&(double2x3)
	{
		2.000000f, 2.000000f, 2.000000f,
		2.000000f, 2.000000f, 2.000000f
	},
	&(double3x2)
	{
		1.000000f, 0.000000f,
		0.000000f, 1.000000f,
		0.000000f, 0.000000f
	},
	&(double2x2)
	{
		2.000000f, 2.000000f,
		2.000000f, 2.000000f
	}
);

