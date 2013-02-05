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

#include "framework_thread.hpp"

#include <memory>
#include <type_traits>

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

template <class OutStream, class TestPart>
class test_part_executor : public framework_thread_base<OutStream>
{
G42CORE_MC_NOT_COPYABLE(test_part_executor)
public:
    typedef test_part_executor<OutStream, TestPart> type;

    test_part_executor(OutStream& outStream, const TestPart& test_part):
        framework_thread_base<OutStream>(outStream),
        test_part(test_part)
    {}

    static void* thread_func(void* p)
    {
        if(p == NULL)
        {
            return NULL;
        }
        type* this_ = reinterpret_cast<type*>(p);
        try
        {
            this_->test_part.run();
            this_->result_ = type::result_passed;
        }
        catch(const verification_failure& ex)
        {
            auto sci = ex.source_code_info();
            this_->outStream << sci.filename();
            this_->outStream << '(' << sci.line() << "): ";
            this_->outStream << sci.expression();
            this_->result_ = type::result_failed;
        }
        return NULL;
    }
private:
    const TestPart& test_part;
};

struct test_executor_multiple_threads
{
    template <class Reporter, class TestPartSequence>
    static void execute(Reporter&& reporter, TestPartSequence& test_part_sequence, unsigned int &passed, unsigned int &failed)
    {
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
            ordered_parts.sort(test_executor_multiple_threads::compare_parts<typename std::list<test_part_type>::value_type>);
        }


        typedef test_part_executor<std::ostream, typename std::remove_pointer<test_part_type>::type > test_part_executor_ostream;
        std::list<std::pair<std::shared_ptr<std::stringstream>, std::shared_ptr<test_part_executor_ostream> > > pairs;
        std::list<std::shared_ptr<G42CORE_CONCURRENCY_NS thread> > threads;

        // NOTE only the execution of this type of thread part is current unit tested
        start_threads(anythread_parts, pairs, threads);

        { // BEGIN TODO unit test executing these types of test parts
        start_threads(ordered_parts, pairs, threads);
        start_threads(nonprimary_parts, pairs, threads);
        if(primary)
        {
            auto pExecutor = create_and_push_pair(*primary, pairs);
            test_part_executor_ostream::thread_func(pExecutor.get());
        }
        } // END TODO unit test executing these types of test parts

        for(auto i = threads.begin(); i != threads.end(); ++i)
        {
            (*i)->join();
        }

        bool anyFailed = false;
        bool anyPassed = false;

        for(auto i = pairs.begin(); i != pairs.end(); ++i)
        {
            auto result = (*i).second->result();
            if(result == test_part_executor_ostream::result_failed)
            {
                anyFailed = true;
            }
            if(result == test_part_executor_ostream::result_passed)
            {
                anyPassed = true;
            }

            // REVIEW while only one message (at most) will be included per thread
            // for if_not_report type verification, other verfication types are
            // contemplated and if_not_report_only could result in multiple messages.
            auto s = ((*i).first)->str();
            if(s.size() > 0)
            {
                reporter.on_complete_message(s);
            }
        }

        if(anyFailed)
        {
            ++failed;
        }
        else if(anyPassed)
        {
            ++passed;
        }
    }
private:
    template <class TestPart>
    static bool compare_parts(TestPart test_part_lhs, TestPart test_part_rhs)
    {
        return test_part_lhs->logical_process_and_thread().thread_id() < test_part_rhs->logical_process_and_thread().thread_id();
    }

    template <class TestPart, class Pairs>
    static typename Pairs::value_type::second_type create_and_push_pair(const TestPart& test_part, Pairs& pairs)
    {
        typename Pairs::value_type::first_type first(new typename Pairs::value_type::first_type::element_type());
        typename Pairs::value_type::second_type second(new typename Pairs::value_type::second_type::element_type(*first, test_part));
        pairs.push_back(typename Pairs::value_type(first, second));
        return second;
    }

    template <class TestParts, class Pairs, class Threads>
    static void start_threads(const TestParts& test_parts, Pairs& pairs, Threads& threads)
    {
        for(auto i = test_parts.begin(); i != test_parts.end(); ++i)
        {
            typename Pairs::value_type::first_type first(new typename Pairs::value_type::first_type::element_type());
            typename Pairs::value_type::second_type second(new typename Pairs::value_type::second_type::element_type(*first, **i));
            pairs.push_back(typename Pairs::value_type(first, second));
            threads.push_back(typename Threads::value_type(new typename Threads::value_type::element_type(&Pairs::value_type::second_type::element_type::thread_func, second.get())));
        }
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
            // The reason for passing in passed and failed by reference is to allow them to be incremented
            // more than once by an executor that runs the test more than once.  For example the executor
            // runs the order agnostic parts started in different orders.
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
