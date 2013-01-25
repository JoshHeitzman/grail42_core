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

class test3 : public G42CORE_TEST_NS detail::test_part_base_with_policy<test_part_base_policy_mock_registry>
{
public:
    test3(bool fail = false):
        G42CORE_TEST_NS detail::test_part_base_with_policy<test_part_base_policy_mock_registry>(
            "",
            G42CORE_TEST_NS detail::logical_process_and_thread_holder(0, 0), 
            G42CORE_TEST_NS detail::basic_source_code_info_holder("", 0)),
        fail(fail)
    {}
    virtual void run() const
    {
        if(fail)
        {
            throw G42CORE_TEST_NS detail::verification_failure();
        }
    }
private:
    bool fail;
};

test3 t1;
test3 t2(true);
test3 t3;
test3 t4(true);

#include <list>

typedef std::list<const G42CORE_TEST_NS detail::test_part_base_common*> sequence_type;
typedef boost::iterator_range<sequence_type::iterator> range_type;

struct mock_registryA
{
    static range_type range()
    {
        static sequence_type s;
        if(!s.size())
        {
            s.push_back(&t1);
        }
        return range_type(s);
    }
};

typedef G42CORE_TEST_NS detail::test_executor_single_thread_without_test_part_validation<mock_registryA> executorA;

struct mock_registryB
{
    static range_type range()
    {
        static sequence_type s;
        if(!s.size())
        {
            s.push_back(&t2);
        }
        return range_type(s);
    }
};

typedef G42CORE_TEST_NS detail::test_executor_single_thread_without_test_part_validation<mock_registryB> executorB;

struct mock_registry2
{
    static range_type range()
    {
        static sequence_type s;
        if(!s.size())
        {
            s.push_back(&t1);
            s.push_back(&t2);
            s.push_back(&t3);
            s.push_back(&t4);
        }
        return range_type(s);
    }
};

typedef G42CORE_TEST_NS detail::test_executor_single_thread_without_test_part_validation<mock_registry2> executor;

struct mock_registry3
{
    static range_type range()
    {
        static sequence_type s;
        if(!s.size())
        {
            s.push_back(&t2);
            s.push_back(&t4);
            s.push_back(&t1);
        }
        return range_type(s);
    }
};

typedef G42CORE_TEST_NS detail::test_executor_single_thread_without_test_part_validation<mock_registry3> executor2;

#include "g42core/test/main.hpp"

#include "atomic_trivial_test.hpp"

BEGIN_TESTS()

DEFINE_TEST()
{
    atomicTrivialTest.ExecuteOnEachThread();

    {
    std::stringstream ss;
    executorA::run<>(G42CORE_TEST_NS detail::reporter_with_ostream(ss));
    std::string s = ss.str();
    VERIFY(s == std::string("*** Tests started  ***\n*** Tests complete: 1 passed, 0 failed, 0 skipped ***\n"));
    }
    {
    std::stringstream ss;
    executorB::run<>(G42CORE_TEST_NS detail::reporter_with_ostream(ss));
    std::string s = ss.str();
    VERIFY(s == std::string("*** Tests started  ***\n*** Tests complete: 0 passed, 1 failed, 0 skipped ***\n"));
    }
    {
    std::stringstream ss;
    executor::run<>(G42CORE_TEST_NS detail::reporter_with_ostream(ss));
    std::string s = ss.str();
    VERIFY(s == std::string("*** Tests started  ***\n*** Tests complete: 2 passed, 2 failed, 0 skipped ***\n"));
    }
    {
    std::stringstream ss;
    executor2::run<>(G42CORE_TEST_NS detail::reporter_with_ostream(ss));
    std::string s = ss.str();
    VERIFY(s == std::string("*** Tests started  ***\n*** Tests complete: 1 passed, 2 failed, 0 skipped ***\n"));
    }
}

END_TESTS()
