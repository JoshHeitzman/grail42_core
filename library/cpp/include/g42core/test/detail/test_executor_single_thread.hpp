/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_5E922C53B4834E6D989168F89AECDD61
#define G42CORE_HG_5E922C53B4834E6D989168F89AECDD61

#ifndef G42CORE_HG_977EE3D68FC449FDB779CEF0955C0194
#include "../../metacode/classes.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

template <class Registry>
struct test_executor_single_thread_without_test_part_validation
{
    typedef Registry registry;

    template <class Reporter>
    static int run(Reporter&& reporter)
    {
        reporter.on_tests_starting();

        auto range = registry::range();

        unsigned int passed = 0;
        unsigned int failed = 0;

        for(auto i = range.begin(); i != range.end(); ++i)
        {
            try
            {
                (*i)->run();
                ++passed;
            }
            catch(...) // TODO change to catch a custom exception type only
            {
                // TODO extract error message from custom exception and call reporter.on_complete_message
                ++failed;
            }
        }

        reporter.on_tests_complete(passed, failed, 0);

        return failed ? 1 : 0;
    };
};

struct test_executor_single_thread
{
    static int run()
    {
        /*
        Combine test parts into tests and verify basic requirements:
            * each test has only one part for the primary thread of a process
        */

        /*
        Filter out all tests have more then one part or have one part that must 
        run on a nonprimary thread or in a nonprimary process.
        Accmulate count of number of filtered out tests.
        */

        // Notify reporter that tests are starting

        /*
        Execute each test part, catching any test infrastructure exceptions
        */

        // Notify reporter that tests are complete with the number of passed, failed, and skipped
        return 0;
    };
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_5E922C53B4834E6D989168F89AECDD61
