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

#include "../registry_mock.hpp"

#include <g42core/test/detail/test_part_common.hpp>

#include "test_part_mock.hpp"

#include <g42core/test/detail/test_part_combiner.hpp>

template <class Registrar>
void verify_test_part_sequences(size_t expectedSequences)
{
    typedef Registrar registrar;
    auto test_part_sequences(G42CORE_TEST_NS detail::test_parts_combiner::combine(registrar::range()));
    VERIFY(expectedSequences == test_part_sequences.size());
    for(auto i = test_part_sequences.begin(); i != test_part_sequences.end(); ++i)
    {
        size_t expected_size = atoi((*i).first);
        VERIFY(expected_size == (*i).second.size());
        for(auto j = (*i).second.begin(); j != (*i).second.end(); ++j)
        {
            VERIFY(std::string((*i).first) == std::string((*j)->test_id()));
        }
    }
}

BEGIN_TESTS()

DEFINE_TEST()
{
    const char* two = "2";
    typedef mock_registrar<const G42CORE_TEST_NS detail::test_part_base_common*> registrar;
    test_part_mock_with_id t1(two);
    registrar::add(&t1);
    {
    auto test_part_sequences(G42CORE_TEST_NS detail::test_parts_combiner::combine(registrar::range()));
    VERIFY(1 == test_part_sequences.size());
    auto i = test_part_sequences.begin();
    VERIFY(std::string((*i).first) == std::string((*((*i).second.begin()))->test_id()));
    }
    test_part_mock_with_id t2("1");
    registrar::add(&t2);
    {
    auto test_part_sequences(G42CORE_TEST_NS detail::test_parts_combiner::combine(registrar::range()));
    VERIFY(2 == test_part_sequences.size());
    for(auto i = test_part_sequences.begin(); i != test_part_sequences.end(); ++i)
    {
        VERIFY((*i).second.size() == 1);
        VERIFY(std::string((*i).first) == std::string((*((*i).second.begin()))->test_id()));
    }
    }
    test_part_mock_with_id t3(two);
    registrar::add(&t3);
    verify_test_part_sequences<registrar>(2);
    const char* three = "3";
    test_part_mock_with_id t3a(three);
    registrar::add(&t3a);
    test_part_mock_with_id t3b(three);
    registrar::add(&t3b);
    test_part_mock_with_id t3c(three);
    registrar::add(&t3c);
    verify_test_part_sequences<registrar>(3);
}

END_TESTS()
