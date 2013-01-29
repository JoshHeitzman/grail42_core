/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "stdafx.h"

#define G42CORE_TEST_FRAMEWORK_TUT
#include "g42core/test/test.hpp"
#include "g42core/test/short_defines.hpp"
#include "g42core/test/detail/test_part.hpp"

// TODO replace with mock that ensures add was called.
struct mock_registry
{
    static void add(const G42CORE_TEST_NS detail::test_part_base_common&)
    {
    }
};

typedef G42CORE_TEST_NS detail::test_part_base_policy<mock_registry> test_part_base_policy_mock_registry;

#define G42CORE_TEST_DEFAULT_TEST_REGISTRY mock_registry

#include "g42core/test/detail/test_registration.hpp"

class test1 : public G42CORE_TEST_NS detail::test_part_base_with_policy<test_part_base_policy_mock_registry>
{
public:
    test1(const char* id, int threadId, int processId, const char* filename, int line):
        G42CORE_TEST_NS detail::test_part_base_with_policy<test_part_base_policy_mock_registry>(
            id,
            G42CORE_TEST_NS detail::logical_process_and_thread_holder(threadId, processId), 
            G42CORE_TEST_NS detail::basic_source_code_info_holder(filename, line)),
        ran(false)
    {}
    virtual void run() const
    {
        const_cast<test1*>(this)->ran = true;
    }
    bool ran;
};

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

G42CORE_TEST_DETAIL_BEGIN_GROUP()
G42CORE_TEST_DETAIL_DEFINE_TEST()
{
}
G42CORE_TEST_DETAIL_END_GROUP()

G42CORE_TEST_DETAIL_BEGIN_GROUP()
G42CORE_TEST_DETAIL_DEFINE_TEST()
{
}
G42CORE_TEST_DETAIL_END_GROUP()

#include "atomic_trivial_test.hpp"

atomic_trivial_test atomicTrivialTest;


BEGIN_TESTS()

DEFINE_TEST()
{
    {
    G42CORE_CONCURRENCY_NS atomic<bool> atom(true);
#if !defined(HWC_PLATFORM_ANDROID)
    bool atom_is_lock_free = atom.is_lock_free();
    VERIFY(atom_is_lock_free);
#endif
    VERIFY(atom.load());
    atom.store(false);
    VERIFY(!atom.load());
    }

    atomicTrivialTest.ExecuteOnEachThread();

    {
    const char* id1 = "id1";
    const char* filename1 = "filename1";
    const unsigned int line1 = 1;
    const int proc1 = 100000;
    const int thread1 = -2000000;
    test1 t1(id1, thread1, proc1, filename1, line1);
    VERIFY(strcmp(t1.test_id(), id1) == 0);
    VERIFY(t1.basic_source_code_info().line() == line1);
    VERIFY(strcmp(t1.basic_source_code_info().filename(), filename1) == 0);
    t1.run();
    VERIFY(t1.ran);

    // repeat with a different instance while the previous instance is still live to ensure
    // no sharing between instances.

    const char* id2 = "id1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890";
    const char* filename2 = "filename1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890";
    const unsigned int line2 = 20000;
    const int proc2 = 0;
    const int thread2 = 0;
    test2 t2(id2, thread2, proc2, filename2, line2);
    VERIFY(strcmp(t2.test_id(), id2) == 0);
    VERIFY(t2.basic_source_code_info().line() == line2);
    VERIFY(strcmp(t2.basic_source_code_info().filename(), filename2) == 0);
    t2.run();
    }
}

END_TESTS()
