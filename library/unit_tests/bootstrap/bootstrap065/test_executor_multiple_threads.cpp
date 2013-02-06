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

template <class TestPartsSequence, class TestPart>
void single_test_part_passed(TestPartsSequence& test_part_sequence, TestPart& testPart)
{
    testPart.run_should_throw(false);
    auto orig_run_call_count = testPart.run_call_count();
    unsigned int passed = 0;
    unsigned int failed = 0;
    std::stringstream ss;
    G42CORE_TEST_NS detail::test_executor_multiple_threads::execute(G42CORE_TEST_NS detail::reporter_with_ostream(ss), test_part_sequence, passed, failed);
    VERIFY(testPart.run_call_count() == orig_run_call_count+1);
    VERIFY(passed == 1);
    VERIFY(failed == 0);
    std::string s = ss.str();
    VERIFY(s == std::string());
}

template <class TestPartsSequence, class TestPart>
void single_test_part_failed(TestPartsSequence& test_part_sequence, TestPart& testPart)
{
    testPart.run_should_throw(true);
    auto orig_run_call_count = testPart.run_call_count();
    unsigned int passed = 0;
    unsigned int failed = 0;
    std::stringstream ss;
    G42CORE_TEST_NS detail::test_executor_multiple_threads::execute(G42CORE_TEST_NS detail::reporter_with_ostream(ss), test_part_sequence, passed, failed);
    VERIFY(testPart.run_call_count() == orig_run_call_count+1);
    VERIFY(passed == 0);
    VERIFY(failed == 1);
    std::string s = ss.str();
    VERIFY(s == std::string("mockfile(55): mockexp\n"));
}

BEGIN_TESTS()

DEFINE_TEST()
{
    std::list<test_part_mock_with_id*> test_part_sequence1;
    test_part_mock_with_id testPart1("test_part_1");
    {
    unsigned int passed = 0;
    unsigned int failed = 0;
    std::stringstream ss;
    G42CORE_TEST_NS detail::test_executor_multiple_threads::execute(G42CORE_TEST_NS detail::reporter_with_ostream(ss), test_part_sequence1, passed, failed);
    VERIFY(passed == 0);
    VERIFY(failed == 0);
    std::string s = ss.str();
    VERIFY(s == std::string());
    }
    test_part_sequence1.push_back(&testPart1);
    single_test_part_passed(test_part_sequence1, testPart1);
    single_test_part_failed(test_part_sequence1, testPart1);

    testPart1.run_should_throw(false);
    test_part_mock_with_id testPart2("test_part_2");
    test_part_sequence1.push_back(&testPart2);
    {
    unsigned int passed = 0;
    unsigned int failed = 0;
    std::stringstream ss;
    G42CORE_TEST_NS detail::test_executor_multiple_threads::execute(G42CORE_TEST_NS detail::reporter_with_ostream(ss), test_part_sequence1, passed, failed);
    VERIFY(testPart1.run_call_count() == 3);
    VERIFY(testPart2.run_call_count() == 1);
    VERIFY(passed == 1);
    VERIFY(failed == 0);
    std::string s = ss.str();
    VERIFY(s == std::string());
    }
    testPart1.run_should_throw(true);
    test_part_mock_with_id testPart3("test_part_3");
    test_part_sequence1.push_back(&testPart3);
    {
    unsigned int passed = 0;
    unsigned int failed = 0;
    std::stringstream ss;
    G42CORE_TEST_NS detail::test_executor_multiple_threads::execute(G42CORE_TEST_NS detail::reporter_with_ostream(ss), test_part_sequence1, passed, failed);
    VERIFY(testPart1.run_call_count() == 4);
    VERIFY(testPart2.run_call_count() == 2);
    VERIFY(testPart3.run_call_count() == 1);
    VERIFY(passed == 0);
    VERIFY(failed == 1);
    std::string s = ss.str();
    VERIFY(s == std::string("mockfile(55): mockexp\n"));
    }
}

DEFINE_TEST()
{
    std::list<test_part_mock_with_id*> test_part_sequence1;
    test_part_mock_with_id testPart1("test_part_1", G42CORE_TEST_NS detail::logical_process_and_thread_holder::special_thread_ids::primary);
    test_part_sequence1.push_back(&testPart1);
    single_test_part_passed(test_part_sequence1, testPart1);
    single_test_part_failed(test_part_sequence1, testPart1);
}

END_TESTS()
