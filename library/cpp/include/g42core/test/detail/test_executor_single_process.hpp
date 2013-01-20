/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_A2E75F8D46384F5480C33327460E2849
#define G42CORE_HG_A2E75F8D46384F5480C33327460E2849

#ifndef G42CORE_HG_977EE3D68FC449FDB779CEF0955C0194
#include "../../metacode/classes.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

#ifndef G42CORE_HG_05CD3AFAF8B945B189E6C8E5E3133D27
#include "../../concurrency/atomic.hpp"
#endif

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

struct test_executor_single_process_without_test_part_validation
{
    static int run()
    {
        // Combine test parts into tests

        // Notify reporter that tests are starting

        /*
        while tests remain:
            1 Create the number of threads necessary to run the parts to be run on nonprimary
                threads.
            2 Execute the part to be run on the primary thread, catching any infrastructure 
                exceptions.
            3 join all of the nonprimary threads
            4 Check the stringstream for each thread and output if it has contents
        */

        // Notify reporter that tests are complete with the number of passed, failed, and skipped
        return 0;
    };
};

struct test_executor_single_process
{
    static int run()
    {
        /*
        Combine test parts into tests and verify basic requirements:
            * each test has only one part for the primary thread of a process
        */

        /*
        Filter out:
            * tests that have a part that must be run in a nonprimary process
            * tests that have multiple parts that must be run on a primary thread
        Accmulate count of number of filtered out tests.
        */

        // Notify reporter that tests are starting

        /*
        while tests remain:
            1 Create the number of threads necessary to run the parts to be run on nonprimary
                threads.
            2 Execute the part to be run on the primary thread, catching any infrastructure 
                exceptions.
            3 join all of the nonprimary threads
            4 Check the stringstream for each thread and output if it has contents
        */

        // Notify reporter that tests are complete with the number of passed, failed, and skipped
        return 0;
    };
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_A2E75F8D46384F5480C33327460E2849
