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

template <class Policy>
class test_part_registrar
{
G42CORE_MC_NOT_COPYABLE(test_part_registrar)
public:
    typedef typename Policy::range_type range_type;
    typedef typename Policy::test_part test_part;

    void add(const test_part& testPart)
    {
        // TOOD validate current thread id against id of thread that constructed this instance,
        // but first this requires providing this_thread::get_id in G42CORE_CONCURRENCY_NS, and
        // then the unit test will need to be expanded as well.
        if(!registrationOpen.load())
        {
            throw std::exception(); // TODO better exception
        }
        test_parts.push_back(&testPart);
    }

    range_type range()
    {
        registrationOpen.store(false);
        return range_type(test_parts);
    }

    static test_part_registrar& get()
    {
#if __GNUC__ == 4 && __GNUC_MINOR__ < 6
        static G42CORE_CONCURRENCY_NS atomic<void*> pRegistrar;
#else
        static G42CORE_CONCURRENCY_NS atomic<test_part_registrar*> pRegistrar;
#endif
        static G42CORE_CONCURRENCY_NS atomic<bool> initialized;
        test_part_registrar* p;
        while((p = (test_part_registrar*)pRegistrar.load()) == NULL)
        {
            bool expected = false;
            if(initialized.compare_exchange_weak(expected, true))
            {
                static test_part_registrar registrar;
                pRegistrar.store(&registrar);
            }
        }
        return *p;
    }

private:
    typedef typename Policy::sequence_type sequence_type;

    test_part_registrar():
        registrationOpen(true)
    {}

    G42CORE_CONCURRENCY_NS atomic<bool> registrationOpen;
    sequence_type test_parts;
};

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
