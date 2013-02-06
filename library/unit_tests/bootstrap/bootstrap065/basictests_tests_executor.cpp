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

G42CORE_MC_WARNING_PUSH

G42CORE_MC_MSVC_PRAGMA(warning(disable:4127)) // conditional expression is constant

template <bool Passed = true>
struct test_executor_mock_pass_or_fail
{
    template <class Reporter, class TestPartSequence>
    static void execute(Reporter&&, const TestPartSequence&, unsigned int &passed, unsigned int &failed)
    {
        if(Passed)
        {
            ++passed;
        }
        else
        {
            ++failed;
        }
    }
};

struct test_executor_mock_alternate
{
    template <class Reporter, class TestPartSequence>
    static void execute(Reporter&&, const TestPartSequence&, unsigned int &passed, unsigned int &failed)
    {
        if(passed == failed)
        {
            ++passed;
        }
        else
        {
            ++failed;
        }
    }
};

G42CORE_MC_WARNING_POP

BEGIN_TESTS()

DEFINE_TEST()
{
    std::list<std::pair<int, std::list<test_part_mock_with_id*> > > test_part_sequences;
    {
    std::stringstream ss;
    G42CORE_TEST_NS detail::tests_executor<test_executor_mock_pass_or_fail<> >::execute(G42CORE_TEST_NS detail::reporter_with_ostream(ss), test_part_sequences, 0);
    std::string s = ss.str();
    VERIFY(s == std::string("*** Tests started  ***\n*** Tests complete: 0 passed, 0 failed, 0 skipped ***\n"));
    }
    std::list<test_part_mock_with_id*> test_part_sequence1;
    test_part_mock_with_id testPart1("test_part_1");
    test_part_sequence1.push_back(&testPart1);
    test_part_sequences.push_back(std::make_pair(0, test_part_sequence1));
    {
    std::stringstream ss;
    G42CORE_TEST_NS detail::tests_executor<test_executor_mock_pass_or_fail<true> >::execute(G42CORE_TEST_NS detail::reporter_with_ostream(ss), test_part_sequences, 0);
    std::string s = ss.str();
    VERIFY(s == std::string("*** Tests started  ***\n*** Tests complete: 1 passed, 0 failed, 0 skipped ***\n"));
    }
    {
    std::stringstream ss;
    G42CORE_TEST_NS detail::tests_executor<test_executor_mock_pass_or_fail<false> >::execute(G42CORE_TEST_NS detail::reporter_with_ostream(ss), test_part_sequences, 0);
    std::string s = ss.str();
    VERIFY(s == std::string("*** Tests started  ***\n*** Tests complete: 0 passed, 1 failed, 0 skipped ***\n"));
    }
    std::list<test_part_mock_with_id*> test_part_sequence2;
    test_part_mock_with_id testPart2("test_part_2");
    test_part_sequence2.push_back(&testPart2);
    test_part_sequences.push_back(std::make_pair(0, test_part_sequence2));
    {
    std::stringstream ss;
    G42CORE_TEST_NS detail::tests_executor<test_executor_mock_pass_or_fail<true> >::execute(G42CORE_TEST_NS detail::reporter_with_ostream(ss), test_part_sequences, 1);
    std::string s = ss.str();
    VERIFY(s == std::string("*** Tests started  ***\n*** Tests complete: 2 passed, 0 failed, 1 skipped ***\n"));
    }
    {
    std::stringstream ss;
    G42CORE_TEST_NS detail::tests_executor<test_executor_mock_pass_or_fail<false> >::execute(G42CORE_TEST_NS detail::reporter_with_ostream(ss), test_part_sequences, 2);
    std::string s = ss.str();
    VERIFY(s == std::string("*** Tests started  ***\n*** Tests complete: 0 passed, 2 failed, 2 skipped ***\n"));
    }
    std::list<test_part_mock_with_id*> test_part_sequence3;
    test_part_mock_with_id testPart3("test_part_3");
    test_part_sequence3.push_back(&testPart3);
    test_part_sequences.push_back(std::make_pair(0, test_part_sequence3));
    {
    std::stringstream ss;
    G42CORE_TEST_NS detail::tests_executor<test_executor_mock_alternate>::execute(G42CORE_TEST_NS detail::reporter_with_ostream(ss), test_part_sequences, 10);
    std::string s = ss.str();
    VERIFY(s == std::string("*** Tests started  ***\n*** Tests complete: 2 passed, 1 failed, 10 skipped ***\n"));
    }
}

END_TESTS()
