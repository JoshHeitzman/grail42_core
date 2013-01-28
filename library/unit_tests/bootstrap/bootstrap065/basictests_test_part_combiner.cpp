/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "stdafx.h"

/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "stdafx.h"

#include "g42core/test/test.hpp"
#include <g42core/test/short_defines.hpp>

#include "../registry_mock.hpp"
#include <g42core/test/detail/test_part_common.hpp>

#include <g42core/test/detail/test_part_combiner.hpp>

class test1 : public G42CORE_TEST_NS detail::test_part_base_common
{
G42CORE_MC_NOT_COPYABLE(test1)
public:
    test1(const char* id):
        test_part_base_common(
            id,
            G42CORE_TEST_NS detail::logical_process_and_thread_holder(0, 0), 
            G42CORE_TEST_NS detail::basic_source_code_info_holder("", 0))
    {}

    ~test1() {}

    virtual void run() const
    {
    }
};

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
    typedef mock_registrar<const G42CORE_TEST_NS detail::test_part_base_common*> registrar;
    test1 t1("2");
    registrar::add(&t1);
    {
    auto test_part_sequences(G42CORE_TEST_NS detail::test_parts_combiner::combine(registrar::range()));
    VERIFY(1 == test_part_sequences.size());
    auto i = test_part_sequences.begin();
    VERIFY(std::string((*i).first) == std::string((*((*i).second.begin()))->test_id()));
    }
    test1 t2("1");
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
    test1 t3("2");
    registrar::add(&t3);
    verify_test_part_sequences<registrar>(2);
    test1 t3a("3");
    registrar::add(&t3a);
    test1 t3b("3");
    registrar::add(&t3b);
    test1 t3c("3");
    registrar::add(&t3c);
    verify_test_part_sequences<registrar>(3);
}

END_TESTS()
