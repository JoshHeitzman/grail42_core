/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_D05BDCC8B8D74E43A9DEF963F4BDD1B5
#define G42CORE_HG_D05BDCC8B8D74E43A9DEF963F4BDD1B5

G42CORE_MC_PRAGMA_ONCE

#ifndef G42CORE_HG_05CD3AFAF8B945B189E6C8E5E3133D27
#include "../../concurrency/atomic.hpp"
#endif

#ifndef G42CORE_HG_9C17FE3D4D104BF6A331E62CD2C6AECB
#include "../../concurrency/thread.hpp"
#endif

#include <list>
#include <boost/range/iterator_range.hpp>
#include <memory>

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

template <
    typename TestPart, 
    class TestPartSequence = std::list<const TestPart*>, 
    template <typename> class IteratorRange = boost::iterator_range
>
struct test_part_registrar_policy
{
    typedef TestPart test_part;
    typedef TestPartSequence sequence_type;
    typedef IteratorRange<typename sequence_type::iterator> range_type;
};

#if defined(HWC_PLATFORM_ANDROID) && 0
#define G42CORE_TEST_REGISTRAR_ONE_STATIC
#endif

class acquire_stdout
{
public:
    acquire_stdout()
    {
        acquire();
    }
    ~acquire_stdout()
    {
        release();
    }
    void acquire()
    {
#if defined(HWC_PLATFORM_ANDROID) && __GNUC_MINOR__ == 6
        flockfile(stdout);
#endif
    }
    void release()
    {
#if defined(HWC_PLATFORM_ANDROID) && __GNUC_MINOR__ == 6
        funlockfile(stdout);
#endif
    }
};

template <class Policy>
class test_part_registrar
{
G42CORE_MC_NOT_COPYABLE(test_part_registrar)
public:
    typedef typename Policy::range_type range_type;
    typedef typename Policy::test_part test_part;

    void add(const test_part& testPart)
    {
        acquire_stdout acquire;
        // TOOD validate current thread id against id of thread that constructed this instance,
        // but first this requires providing this_thread::get_id in G42CORE_CONCURRENCY_NS, and
        // then the unit test will need to be expanded as well.
        if(!registrationOpen.load())
        {
#if 0
            printf("add throw; tid %u\n", gettid());
            fflush(stdout);
#endif
            throw std::exception(); // TODO better exception
        }
#if 0
        printf("add before push_back\n");
        fflush(stdout);
#endif
        test_parts.push_back(&testPart);
#if 0
        printf("add calling test_parts.end(); tid %u\n", gettid());
        fflush(stdout);
        test_parts.end();
        printf("add calling test_parts.begin(); tid %u\n", gettid());
        fflush(stdout);
        auto start = test_parts.begin();
        printf("add comparing start and end; tid %u\n", gettid());
        fflush(stdout);
        if(start != test_parts.end())
        {
            printf("add strart != end; tid %u\n", gettid());
        }
        else
        {
            printf("add strart == end; tid %u\n", gettid());
        }
        fflush(stdout);
        if(start == test_parts.end())
        {
            printf("add strart == end; tid %u\n", gettid());
        }
        else
        {
            printf("add strart != end; tid %u\n", gettid());
        }
        fflush(stdout);
        printf("add *start; tid %u\n", gettid());
        fflush(stdout);
        *start;
        printf("add calling ++start; tid %u\n", gettid());
        fflush(stdout);
        ++start;
        printf("add comparing start and end; tid %u\n", gettid());
        fflush(stdout);
        if(start != test_parts.end())
        {
            printf("add strart != end; tid %u\n", gettid());
        }
        else
        {
            printf("add strart == end; tid %u\n", gettid());
        }
        fflush(stdout);
        if(start == test_parts.end())
        {
            printf("add strart == end; tid %u\n", gettid());
        }
        else
        {
            printf("add strart != end; tid %u\n", gettid());
        }
        fflush(stdout);
        printf("add *start; tid %u\n", gettid());
        fflush(stdout);
        *start;
        printf("add calling ++start; tid %u\n", gettid());
        fflush(stdout);
        ++start;
        printf("add calling test_parts.end(); tid %u\n", gettid());
        fflush(stdout);
        test_parts.end();
        printf("add comparing start and end; tid %u\n", gettid());
        fflush(stdout);
        if(start != test_parts.end())
        {
            printf("add strart != end; tid %u\n", gettid());
        }
        else
        {
            printf("add strart == end; tid %u\n", gettid());
        }
        fflush(stdout);
        if(start == test_parts.end())
        {
            printf("add strart == end; tid %u\n", gettid());
        }
        else
        {
            printf("add strart != end; tid %u\n", gettid());
        }
        fflush(stdout);
        printf("add *start; tid %u\n", gettid());
        fflush(stdout);
        *start;
        printf("add calling calculating size; tid %u\n", gettid());
        fflush(stdout);
        int size = 0; //std::distance(test_parts.begin(), test_parts.end());
        //int size = test_parts.size();
        for(auto i = test_parts.begin(); i != test_parts.end(); ++i)
        {
            ++size;
        }
        printf("add test_parts.size() %i; tid %u\n", size, gettid());
        fflush(stdout);
#endif
    }

    range_type range()
    {
        acquire_stdout lock;
#if 0
        printf("range start this=%p; tid %u\n", this, gettid());
        fflush(stdout);
#endif

#if 0
        registrationOpen.store(false);
#else
        if(registrationOpen.load())
        {
#if 0
            printf("range registrationOpen still true; tid %u\n", gettid());
            fflush(stdout);
#endif
            bool expected = true;
            if(registrationOpen.compare_exchange_strong(expected, false))
            {
#if 0
                printf("range registrationOpen set to false; tid %u\n", gettid());
                fflush(stdout);
#endif
                lock.release();
#ifdef __GNUC__
                sleep(3);
#endif
                lock.acquire();
            }
        }
#endif

#if 0
        printf("range after registrationOpen check &test_parts=%p; tid %u\n", &test_parts, gettid());
        fflush(stdout);
#endif

#if 0
        int size = test_parts.size();
        printf("range test_parts.size() %i; tid %u\n", size, gettid());
        fflush(stdout);
#endif
        return range_type(test_parts);
    }

#if defined(G42CORE_TEST_REGISTRAR_ONE_STATIC)
private:
    static test_part_registrar registrar;
public:
    static test_part_registrar& get()
    {
        static test_part_registrar registrar2;
        return registrar2;
    }
#else
    static test_part_registrar& get()
    {
#if 0
        printf("get start; tid %u\n", gettid());
        fflush(stdout);
#endif
#if __GNUC__ == 4
#if defined(HWC_PLATFORM_ANDROID) && __GNUC_MINOR__ == 6
        // On Android with GCC 4.6 the pointer specialization breaks on the first store
        // in that subsequent stores have no apparent effect and loads after the
        // the first store return an incorrect result.  Using and casting works fine though 
        // (at least on 32-bit systems).
        // TODO see what is actually goign on once setup correctly to debug on Android (vs. using printf)
        static G42CORE_CONCURRENCY_NS atomic<int> pRegistrar;
#elif __GNUC_MINOR__ < 6
        static G42CORE_CONCURRENCY_NS atomic<void*> pRegistrar;
#endif
#else
        static G42CORE_CONCURRENCY_NS atomic<test_part_registrar*> pRegistrar;
#endif
        static G42CORE_CONCURRENCY_NS atomic<bool> initialized;
        test_part_registrar* p;
#if 0
        printf("get before while; tid %u\n", gettid());
        fflush(stdout);
#endif
        while((p = (test_part_registrar*)pRegistrar.load()) == NULL)
        {
#if 0
            auto pNull1 = (void*)pRegistrar.load();
            printf("get return pNull1 = %p; tid %u\n", pNull1, gettid());
            fflush(stdout);
#endif
#if 0
            printf("get in while; tid %u\n", gettid());
            fflush(stdout);
#endif
            bool expected = false;
            if(initialized.compare_exchange_weak(expected, true))
            {
#if 0
                printf("get do main init; tid %u\n", gettid());
                fflush(stdout);
#endif
#if 1
                static test_part_registrar registrar;
#if 0
                auto p0 = &registrar;
                printf("get return p0 = %p; tid %u\n", p0, gettid());
                fflush(stdout);
#endif
#if 0
                printf("get return &registrar = %p; tid %u\n", &registrar, gettid());
                fflush(stdout);
#endif
#if 0
                pRegistrar = 0;
                auto pNull = (void*)pRegistrar.load();
                printf("get return pNull = %p; tid %u\n", pNull, gettid());
                fflush(stdout);
#endif
#if defined(HWC_PLATFORM_ANDROID) && __GNUC_MINOR__ == 6
                pRegistrar.store((int)&registrar);
#else
                pRegistrar.store(&registrar);
#endif
#if 0
                auto p1 = (void*)pRegistrar.load();
                printf("get return p1 = %p; tid %u\n", p1, gettid());
                fflush(stdout);
#endif
#else
                pRegistrar.store(new test_part_registrar());
#endif
            }
        }
#if 0
        printf("get return p = %p; tid %u\n", p, gettid());
        fflush(stdout);
#endif
        return *p;
    }
#endif

private:
    typedef typename Policy::sequence_type sequence_type;

    test_part_registrar():
        registrationOpen(true)
#if 0
        , pTestParts(new sequence_type()),
        test_parts(*pTestParts)
#endif
    {
#if 0
        printf("test_part_registrar con calling test_parts.end(); tid %u\n", gettid());
        fflush(stdout);
        test_parts.end();
#endif
    }

    G42CORE_CONCURRENCY_NS atomic<bool> registrationOpen;
#if 0
    std::unique_ptr<sequence_type> pTestParts;
    sequence_type &test_parts;
#else
    sequence_type test_parts;
#endif
};

#if defined(G42CORE_TEST_REGISTRAR_ONE_STATIC)
template <class Policy>
test_part_registrar<Policy> test_part_registrar<Policy>::registrar;
#endif

template <class Registrar>
struct test_part_registry_policy
{
    typedef Registrar registrar;
};

template <class Policy>
struct test_part_registry
{
    typedef typename Policy::registrar registrar;
    typedef typename registrar::test_part test_part;
    typedef typename registrar::range_type range_type;

    static void add(const test_part& testPart)
    {
        registrar::get().add(testPart);
    }

    static range_type range()
    {
        return registrar::get().range();
    }

private:
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_D05BDCC8B8D74E43A9DEF963F4BDD1B5
