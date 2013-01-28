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

#include "../registry_mock.hpp"

#include "atomic_trivial_test.hpp"

BEGIN_TESTS()

DEFINE_TEST()
{
    atomicTrivialTest.ExecuteOnEachThread();

    {
        VERIFY(boost::distance(mocked_registry::range()) == 0);
        mocked_registry::add(0);
        VERIFY(boost::distance(mocked_registry::range()) == 1);
        mocked_registry::add(1);
        VERIFY(boost::distance(mocked_registry::range()) == 2);
        mocked_registry::add(2);
        VERIFY(boost::distance(mocked_registry::range()) == 3);
    }
}

END_TESTS()
