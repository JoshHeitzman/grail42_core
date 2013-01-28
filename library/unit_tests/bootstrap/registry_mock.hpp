/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

// NOTE this should only be included once per test project due to the static instances

#include "g42core/test/detail/test_part_registry.hpp"

#include <list>
#include <boost/range/iterator_range.hpp>

template <class TestPart>
struct mock_registrar
{
    typedef TestPart test_part;
    typedef std::list<test_part> sequence_type;
    typedef boost::iterator_range<typename sequence_type::iterator> range_type;

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

template <class TestPart>
mock_registrar<TestPart> mock_registrar<TestPart>::instance;
template <class TestPart>
typename mock_registrar<TestPart>::sequence_type mock_registrar<TestPart>::sequence;

typedef G42CORE_TEST_NS detail::test_part_registry<G42CORE_TEST_NS detail::test_part_registry_policy<mock_registrar<int> > > mocked_registry;
