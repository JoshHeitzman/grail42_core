/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "stdafx.h"

#include <g42core/test/test.hpp>
#include <g42core/test/short_defines.hpp>

#include "g42core/test/detail/test_execution.hpp"

#include "test_part_mock.hpp"

BEGIN_TESTS()

DEFINE_TEST()
{
    std::list<test_part_mock_with_id*> test_part_sequence1;
    test_part_mock_with_id testPart1("test_part_1");
    unsigned int passed = 0;
    unsigned int failed = 0;
    {
    std::stringstream ss;
    G42CORE_TEST_NS detail::test_executor::execute(G42CORE_TEST_NS detail::reporter_with_ostream(ss), test_part_sequence1, passed, failed);
    std::string s = ss.str();
    VERIFY(s == std::string());
    }
}

END_TESTS()
