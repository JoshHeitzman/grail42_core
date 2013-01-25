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

#include "g42core/test/detail/test_part_registry.hpp"

#include <list>
#include <boost/range/iterator_range.hpp>

struct mock_registrar
{
    typedef int test_part;
    typedef std::list<test_part> sequence_type;
    typedef boost::iterator_range<sequence_type::iterator> range_type;
    static mock_registrar& get()
    {
        return instance;
    }
    static void add(const test_part& toAdd)
    {
        sequence.push_back(toAdd);
    }
    static range_type range()
    {
        return range_type(sequence);
    }
private:
    static sequence_type sequence;
    static mock_registrar instance;
};

mock_registrar mock_registrar::instance;
mock_registrar::sequence_type mock_registrar::sequence;

typedef G42CORE_TEST_NS detail::test_part_registry<G42CORE_TEST_NS detail::test_part_registry_policy<mock_registrar> > mocked_registry;

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
