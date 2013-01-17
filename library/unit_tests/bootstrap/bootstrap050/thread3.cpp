/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "stdafx.h"

#define G42CORE_TEST_FRAMEWORK_CPPUTEST
#include <g42core/test/test.hpp>
#include <g42core/test/short_defines.hpp>

#include "atomic_trivial_test.hpp"

BEGIN_TESTS()

DEFINE_TEST()
{
    atomicTrivialTest.ExecuteOnEachThread();
}

END_TESTS()
