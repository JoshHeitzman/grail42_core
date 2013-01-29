/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_6EA1DA4970794402A68718EEF5DD33F6
#define G42CORE_HG_6EA1DA4970794402A68718EEF5DD33F6

#ifndef G42CORE_HG_977EE3D68FC449FDB779CEF0955C0194
#include "../../metacode/classes.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

#ifndef G42CORE_HG_05CD3AFAF8B945B189E6C8E5E3133D27
#include "../../concurrency/atomic.hpp"
#endif

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

struct test_validator_noop
{
    template <class TestPartSequences>
    bool validate(const TestPartSequences&)
    {
        return true;
    }
};

struct test_sieve_noop
{
    template <typename TestPartSequences>
    unsigned int filter(TestPartSequences&)
    {
        return 0;
    }
};

struct test_executor
{
    template <class Reporter, class TestPartSequence>
    static void execute(Reporter&& reporter, TestPartSequence& test_part_sequence, unsigned int &passed, unsigned int &failed)
    {
        (void)reporter;
        (void)passed;
        (void)failed;
        typedef typename std::remove_reference< decltype(*(test_part_sequence.begin())) >::type test_part_type;
        std::list<test_part_type> ordered_parts;
        std::list<test_part_type> nonprimary_parts;
        std::list<test_part_type> anythread_parts;
        typename std::remove_const<test_part_type>::type primary = (test_part_type)0;
        for(auto test_part = test_part_sequence.begin(); 
            test_part != test_part_sequence.end(); 
            ++test_part)
        {
            auto logicalTID = (*test_part)->logical_process_and_thread().thread_id();
            if(logicalTID == logical_process_and_thread_holder::special_thread_ids::primary)
            {
                primary = (*test_part);
            }
            else if(logicalTID == logical_process_and_thread_holder::special_thread_ids::nonprimary)
            {
                nonprimary_parts.push_back(*test_part);
            }
            else if(logicalTID == logical_process_and_thread_holder::special_thread_ids::any)
            {
                anythread_parts.push_back(*test_part);
            }
            else
            {
                ordered_parts.push_back(*test_part);
            }
        }
        if(ordered_parts.size() > 0)
        {
            ordered_parts.sort(test_executor::compare_parts<typename std::list<test_part_type>::value_type>);
        }

        (void)primary;

        /* TODO
        1 Create the number of threads necessary to run the parts to be run on other
            threads.
        2 Execute the part to be run on the primary thread, if any, catching any infrastructure 
            exceptions.
        3 join all of the nonprimary threads
        4 Check the stringstream for each thread and output if it has contents
        */
    }
private:
    template <class TestPart>
    static bool compare_parts(TestPart test_part_lhs, TestPart test_part_rhs)
    {
        return test_part_lhs->logical_process_and_thread().thread_id() < test_part_rhs->logical_process_and_thread().thread_id();
    }
};

template <class TestExecutor>
struct tests_executor
{
    typedef TestExecutor test_executor;
    template <class Reporter, class TestPartSequences>
    static int execute(Reporter&& reporter, const TestPartSequences& test_part_sequences, unsigned int ignored)
    {
        reporter.on_tests_starting();

        unsigned int passed = 0;
        unsigned int failed = 0;

        for(auto test_part_sequence = test_part_sequences.begin(); 
            test_part_sequence != test_part_sequences.end(); 
            ++test_part_sequence)
        {
            test_executor::execute(reporter, *test_part_sequence, passed, failed);
        }

        reporter.on_tests_complete(passed, failed, ignored);

        return failed ? 1 : 0;
    }
};

template <class Registry, class Combiner, class Executor, class Validator = test_validator_noop, class Sieve = test_sieve_noop>
struct test_execution_policy
{
    typedef Registry registry;
    typedef Combiner combiner;
    typedef Executor executor;
    typedef Validator validator;
    typedef Sieve sieve;
};

// TODO

/*
Filter out:
    * tests that have a part that must be run in a nonprimary process
    * tests that have multiple parts that must be run on a primary thread
Accmulate count of number of filtered out tests.
*/

template <class Policy>
struct test_execution
{
    typedef typename Policy::registry registry;
    typedef typename Policy::combiner combiner;
    typedef typename Policy::executor executor;
    typedef typename Policy::validator validator;
    typedef typename Policy::sieve sieve;

    template <class Reporter>
    static int run(Reporter& reporter)
    {
        auto test_part_sequences(combiner::combine(registry::range()));

        if(!validator::validate(test_part_sequences))
        {
            return 1;
        }

        return executor::execute(reporter, test_part_sequences, sieve::filter(test_part_sequences));
    };
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_6EA1DA4970794402A68718EEF5DD33F6