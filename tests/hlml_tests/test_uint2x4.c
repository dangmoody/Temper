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

TEMPER_PARAMETRIC( Test_uint2x4_less_than, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const bool2x4* expectedAnswer )
{
	bool2x4 actualResult = uint2x4_less_than( lhs, rhs );
	TEMPER_CHECK_TRUE( bool2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_less_than,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(bool2x4)
	{
		false, false, false, false,
		false, false, false, false
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_less_than,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(bool2x4)
	{
		true, true, true, true,
		true, true, true, true
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_less_than,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(bool2x4)
	{
		false, false, false, false,
		false, false, false, false
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_less_than,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(bool2x4)
	{
		false, false, false, false,
		false, false, false, false
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_less_than_equal, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const bool2x4* expectedAnswer )
{
	bool2x4 actualResult = uint2x4_less_than_equal( lhs, rhs );
	TEMPER_CHECK_TRUE( bool2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_less_than_equal,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(bool2x4)
	{
		true, true, true, true,
		true, true, true, true
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_less_than_equal,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(bool2x4)
	{
		true, true, true, true,
		true, true, true, true
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_less_than_equal,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(bool2x4)
	{
		true, true, true, true,
		true, true, true, true
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_less_than_equal,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(bool2x4)
	{
		false, false, false, false,
		false, false, false, false
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_greater_than, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const bool2x4* expectedAnswer )
{
	bool2x4 actualResult = uint2x4_greater_than( lhs, rhs );
	TEMPER_CHECK_TRUE( bool2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_greater_than,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(bool2x4)
	{
		false, false, false, false,
		false, false, false, false
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_greater_than,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(bool2x4)
	{
		false, false, false, false,
		false, false, false, false
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_greater_than,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(bool2x4)
	{
		false, false, false, false,
		false, false, false, false
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_greater_than,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(bool2x4)
	{
		true, true, true, true,
		true, true, true, true
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_greater_than_equal, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const bool2x4* expectedAnswer )
{
	bool2x4 actualResult = uint2x4_greater_than_equal( lhs, rhs );
	TEMPER_CHECK_TRUE( bool2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_greater_than_equal,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(bool2x4)
	{
		true, true, true, true,
		true, true, true, true
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_greater_than_equal,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(bool2x4)
	{
		false, false, false, false,
		false, false, false, false
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_greater_than_equal,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(bool2x4)
	{
		true, true, true, true,
		true, true, true, true
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_greater_than_equal,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(bool2x4)
	{
		true, true, true, true,
		true, true, true, true
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_cadds, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint32_t rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cadds( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cadds,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	1U,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cadds,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	2U,
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cadds,
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	},
	2U,
	&(uint2x4)
	{
		6U, 6U, 6U, 6U,
		6U, 6U, 6U, 6U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cadds,
	&(uint2x4)
	{
		8U, 8U, 8U, 8U,
		8U, 8U, 8U, 8U
	},
	4U,
	&(uint2x4)
	{
		12U, 12U, 12U, 12U,
		12U, 12U, 12U, 12U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_csubs, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint32_t rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_csubs( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_csubs,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	1U,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_csubs,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	2U,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_csubs,
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	},
	2U,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_csubs,
	&(uint2x4)
	{
		8U, 8U, 8U, 8U,
		8U, 8U, 8U, 8U
	},
	4U,
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_cmuls, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint32_t rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cmuls( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cmuls,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	1U,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cmuls,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	2U,
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cmuls,
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	},
	2U,
	&(uint2x4)
	{
		8U, 8U, 8U, 8U,
		8U, 8U, 8U, 8U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cmuls,
	&(uint2x4)
	{
		8U, 8U, 8U, 8U,
		8U, 8U, 8U, 8U
	},
	4U,
	&(uint2x4)
	{
		32U, 32U, 32U, 32U,
		32U, 32U, 32U, 32U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_cdivs, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint32_t rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cdivs( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cdivs,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	1U,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cdivs,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	2U,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cdivs,
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	},
	2U,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cdivs,
	&(uint2x4)
	{
		8U, 8U, 8U, 8U,
		8U, 8U, 8U, 8U
	},
	4U,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_caddm, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_caddm( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_caddm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_caddm,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_caddm,
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		6U, 6U, 6U, 6U,
		6U, 6U, 6U, 6U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_caddm,
	&(uint2x4)
	{
		8U, 8U, 8U, 8U,
		8U, 8U, 8U, 8U
	},
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	},
	&(uint2x4)
	{
		12U, 12U, 12U, 12U,
		12U, 12U, 12U, 12U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_csubm, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_csubm( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_csubm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_csubm,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_csubm,
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_csubm,
	&(uint2x4)
	{
		8U, 8U, 8U, 8U,
		8U, 8U, 8U, 8U
	},
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	},
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_cmulm, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cmulm( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cmulm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cmulm,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cmulm,
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		8U, 8U, 8U, 8U,
		8U, 8U, 8U, 8U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cmulm,
	&(uint2x4)
	{
		8U, 8U, 8U, 8U,
		8U, 8U, 8U, 8U
	},
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	},
	&(uint2x4)
	{
		32U, 32U, 32U, 32U,
		32U, 32U, 32U, 32U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_cdivm, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cdivm( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cdivm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cdivm,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cdivm,
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cdivm,
	&(uint2x4)
	{
		8U, 8U, 8U, 8U,
		8U, 8U, 8U, 8U
	},
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	}
);

#if defined( __GNUC__ ) || defined( __clang__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif
TEMPER_PARAMETRIC( Test_uint2x4_unary_prefix, TEMPER_FLAG_SHOULD_RUN, const uint2x4* x, const uint2x4* expectedAnswer )
{
	// make local copy of x and use that because we cant do increment or decrement operations on a const reference
	// and MSVC throws warnings if we just make the parameter a non-const reference
	uint2x4* xlocal = (uint2x4*) x;
	uint2x4 actualAnswer = uint2x4_unary( xlocal );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualAnswer, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_unary_prefix,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		4294967294U, 4294967294U, 4294967294U, 4294967294U,
		4294967294U, 4294967294U, 4294967294U, 4294967294U
	}
);

#if defined( __GNUC__ ) || defined( __clang__ )
#pragma GCC diagnostic pop
#endif

TEMPER_PARAMETRIC( Test_uint2x4_cands, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint32_t rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cands( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cands,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	0U,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cands,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	1U,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cands,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	0U,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cands,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	1U,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_cors, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint32_t rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cors( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cors,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	0U,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cors,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	1U,
	&(uint2x4)
	{
		3U, 3U, 3U, 3U,
		3U, 3U, 3U, 3U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cors,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	0U,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cors,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	1U,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_cxors, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint32_t rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cxors( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cxors,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	0U,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cxors,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	1U,
	&(uint2x4)
	{
		3U, 3U, 3U, 3U,
		3U, 3U, 3U, 3U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cxors,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	0U,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cxors,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	1U,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_cshift_lefts, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint32_t rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cshift_lefts( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_lefts,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	0U,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_lefts,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	1U,
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_lefts,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	0U,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_lefts,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	1U,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_cshift_rights, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint32_t rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cshift_rights( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_rights,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	0U,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_rights,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	1U,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_rights,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	0U,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_rights,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	1U,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_candm, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_candm( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_candm,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_candm,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_candm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_candm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_corm, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_corm( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_corm,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_corm,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		3U, 3U, 3U, 3U,
		3U, 3U, 3U, 3U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_corm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_corm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_cxorm, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cxorm( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cxorm,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cxorm,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		3U, 3U, 3U, 3U,
		3U, 3U, 3U, 3U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cxorm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cxorm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_cshift_leftm, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cshift_leftm( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_leftm,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_leftm,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		4U, 4U, 4U, 4U,
		4U, 4U, 4U, 4U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_leftm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_leftm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_cshift_rightm, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_cshift_rightm( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_rightm,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_rightm,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_rightm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_cshift_rightm,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_min, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_min( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_min,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_min,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_max, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint2x4* rhs, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_max( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_max,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_max,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_saturate, TEMPER_FLAG_SHOULD_RUN, const uint2x4* x, const uint2x4* expectedAnswer )
{
	uint2x4 actualResult = uint2x4_saturate( x );
	TEMPER_CHECK_TRUE( uint2x4_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_saturate,
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	},
	&(uint2x4)
	{
		0U, 0U, 0U, 0U,
		0U, 0U, 0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_saturate,
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_saturate,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_saturate,
	&(uint2x4)
	{
		3U, 3U, 3U, 3U,
		3U, 3U, 3U, 3U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_saturate,
	&(uint2x4)
	{
		10U, 10U, 10U, 10U,
		10U, 10U, 10U, 10U
	},
	&(uint2x4)
	{
		1U, 1U, 1U, 1U,
		1U, 1U, 1U, 1U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_identity, TEMPER_FLAG_SHOULD_RUN, const uint2x4* matrix, const bool expectedAnswer )
{
	uint2x4 identityMat;
	uint2x4_identity( &identityMat );
	bool isMatrixIdentity = uint2x4_equals( &identityMat, matrix );
	TEMPER_CHECK_TRUE( isMatrixIdentity == expectedAnswer );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_identity,
	&(uint2x4)
	{
		1U, 0U, 0U, 0U,
		0U, 1U, 0U, 0U
	},
	true
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_identity,
	&(uint2x4)
	{
		1U, 1U, 0U, 0U,
		0U, 1U, 0U, 0U
	},
	false
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_identity,
	&(uint2x4)
	{
		1U, 0U, 0U, 0U,
		1U, 1U, 0U, 0U
	},
	false
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_identity,
	&(uint2x4)
	{
		1U, 1U, 0U, 0U,
		1U, 1U, 0U, 0U
	},
	false
);

TEMPER_PARAMETRIC( Test_uint2x4_transpose, TEMPER_FLAG_SHOULD_RUN, const uint2x4* matrix, const uint4x2* expectedAnswer )
{
	uint4x2 actualResult = uint2x4_transpose( matrix );
	TEMPER_CHECK_TRUE( uint4x2_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_transpose,
	&(uint2x4)
	{
		1U, 0U, 0U, 0U,
		0U, 1U, 0U, 0U
	},
	&(uint4x2)
	{
		1U, 0U,
		0U, 1U,
		0U, 0U,
		0U, 0U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_transpose,
	&(uint2x4)
	{
		0U, 1U, 2U, 3U,
		4U, 5U, 6U, 7U
	},
	&(uint4x2)
	{
		0U, 4U,
		1U, 5U,
		2U, 6U,
		3U, 7U
	}
);

TEMPER_PARAMETRIC( Test_uint2x4_mulm, TEMPER_FLAG_SHOULD_RUN, const uint2x4* lhs, const uint4x2* rhs, const uint2x2* expectedAnswer )
{
	uint2x2 actualResult = uint2x4_mulm( lhs, rhs );
	TEMPER_CHECK_TRUE( uint2x2_equals( &actualResult, expectedAnswer ) );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_mulm,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint4x2)
	{
		4U, 4U,
		4U, 4U,
		4U, 4U,
		4U, 4U
	},
	&(uint2x2)
	{
		32U, 32U,
		32U, 32U
	}
);

TEMPER_INVOKE_PARAMETRIC_TEST( Test_uint2x4_mulm,
	&(uint2x4)
	{
		2U, 2U, 2U, 2U,
		2U, 2U, 2U, 2U
	},
	&(uint4x2)
	{
		1U, 0U,
		0U, 1U,
		0U, 0U,
		0U, 0U
	},
	&(uint2x2)
	{
		2U, 2U,
		2U, 2U
	}
);

