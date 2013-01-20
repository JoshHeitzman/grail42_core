/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "stdafx.h"

#define G42CORE_TEST_FRAMEWORK_GTEST
#include "g42core/test/test.hpp"
#include "g42core/test/short_defines.hpp"

#include "g42core/metacode/classes.hpp"

#include "g42core/test/detail/test_part.hpp"

#include "g42core/test/detail/test_executor_single_thread.hpp"

#include <boost/range/iterator_range.hpp>

struct mock_registry1
{
    static void add(const G42CORE_TEST_NS detail::test_part_base_common*)
    {
    }
};

typedef G42CORE_TEST_NS detail::test_part_base_policy<mock_registry1> test_part_base_policy_mock_registry;

class test2 : public G42CORE_TEST_NS detail::test_part_base_with_policy<test_part_base_policy_mock_registry>
{
public:
    test2(const char* id, int threadId, int processId, const char* filename, int line):
        G42CORE_TEST_NS detail::test_part_base_with_policy<test_part_base_policy_mock_registry>(
            id,
            G42CORE_TEST_NS detail::logical_process_and_thread_holder(threadId, processId), 
            G42CORE_TEST_NS detail::basic_source_code_info_holder(filename, line))
    {}
    virtual void run() const
    {
    }
};

test2 t1("", 0, 0, "", 0);
test2 t2("", 0, 0, "", 0);

#include <list>

struct mock_registry
{
    typedef std::list<const G42CORE_TEST_NS detail::test_part_base_common*> sequence_type;
    typedef boost::iterator_range<sequence_type::iterator> range_type;
    static range_type range()
    {
        static sequence_type s;
        if(!s.size())
        {
            s.push_back(&t1);
            s.push_back(&t2);
        }
        return range_type(s);
    }
};

typedef G42CORE_TEST_NS detail::test_executor_single_thread_without_test_part_validation<mock_registry> executor;

#include "g42core/test/main.hpp"

#include "atomic_trivial_test.hpp"

BEGIN_TESTS()

DEFINE_TEST()
{
    atomicTrivialTest.ExecuteOnEachThread();

    std::stringstream ss;
    executor::run<>(reporter_with_ostream(ss));
    std::string s = ss.str();
    VERIFY(s == std::string("*** Tests started  ***\n*** Tests complete: 2 passed, 0 failed, 0 skipped ***\n"));
}

END_TESTS()
