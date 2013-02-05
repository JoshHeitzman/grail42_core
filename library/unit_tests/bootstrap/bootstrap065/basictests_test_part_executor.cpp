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
#include "g42core/test/detail/verification_failure.hpp"

#include "test_part_mock.hpp"

typedef G42CORE_TEST_NS detail::test_part_executor<std::ostream, test_part_mock_with_id> test_part_executor_under_test;

BEGIN_TESTS()

DEFINE_TEST()
{
    std::stringstream ss;
    test_part_mock_with_id testPartA("test_part_A");
    test_part_executor_under_test tpe1(ss, testPartA);
    void* pRet = test_part_executor_under_test::thread_func(NULL);
    VERIFY(pRet == NULL);
    bool exceptionThrown = false;
    try
    {
        tpe1.result();
    }
    catch(test_part_executor_under_test::result_is_unknown&)
    {
        exceptionThrown = true;
    }
    VERIFY(exceptionThrown);
    pRet = test_part_executor_under_test::thread_func(&tpe1);
    VERIFY(pRet == NULL);
    VERIFY(testPartA.run_call_count() == 1);
    VERIFY(test_part_executor_under_test::result_passed == tpe1.result());
    VERIFY(ss.str() == std::string());
}

DEFINE_TEST()
{
    std::stringstream ss;
    test_part_mock_with_id testPartA("test_part_A");
    testPartA.run_should_throw(true);
    test_part_executor_under_test tpe1(ss, testPartA);
    void* pRet = test_part_executor_under_test::thread_func(&tpe1);
    VERIFY(pRet == NULL);
    VERIFY(testPartA.run_call_count() == 1);
    VERIFY(test_part_executor_under_test::result_failed == tpe1.result());
    VERIFY(ss.str() == std::string("mockfile(55): mockexp"));
}

END_TESTS()
