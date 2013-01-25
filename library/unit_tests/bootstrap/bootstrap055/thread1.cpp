/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "stdafx.h"

#define G42CORE_TEST_FRAMEWORK_TUT
#include <g42core/test/test.hpp>
#include <g42core/test/short_defines.hpp>

#include "mock_registry.hpp"

G42CORE_CONCURRENCY_NS atomic<int> shared_index(-1);

// At file scope so it isn't delaying start of the loop in the test below
static std::vector<int> ints(10000);

BEGIN_TESTS()

DEFINE_TEST()
{
    bool exception_caught = false;
    try
    {
        // NOTE This isn't a execution environment independent way of acheiving the exception 
        // being thrown as a result of the action of one of the two other threads, but using 
        // a better synchronization method in this test code would mean that the synchronization 
        // of the production code wouldn't be getting tested since the test code had its own sync.
        // In the execution environemnt this was written in 1000, 5000, and 10000 interations were
        // sometimes insufficient while 20000 was sufficient over a few dozen runs.
        // TODO Add yield to G42CORE_CONCURRENCY_NS and make use of it here to see about bringing
        // number of iterations down (hopefully considerably).
        int i = -1;
        for(; i < 20000;)
        {
            ++i;
            int* val = &ints[i];
            *val = i;
            mocked_registrar::get().add(*val);
            shared_index.store(i);
        }
    }
    catch(...)
    {
        exception_caught = true;
    }
    VERIFY(exception_caught);

    // Verify all of the expected values are present.  If the statics were re-initialized on
    // a second thread after the first value was added above, then that value (and possibly
    // others) should be missing.
    auto range = mocked_registrar::get().range();
    auto count = boost::distance(range);
    int iMax = shared_index;
    VERIFY(count == iMax+1);
    int i = 0;
    for(auto iter = range.begin(); iter != range.end(); ++i, ++iter)
    {
        VERIFY(*(*iter) == i);
    }
}

END_TESTS()
