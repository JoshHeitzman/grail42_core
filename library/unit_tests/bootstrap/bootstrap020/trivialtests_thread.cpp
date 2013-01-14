/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "stdafx.h"

#include "g42core/test/test.hpp"
#include "g42core/test/short_defines.hpp"

#include "g42core/concurrency/thread.hpp"

void* f1(void*)
{
    return NULL;
}

void* f2(void* i)
{
    *(int*)i = 1;
    return NULL;
}

BEGIN_TESTS()

DEFINE_TEST()
{
    {
    G42CORE_CONCURRENCY_NS thread thread1(f1, (void*)NULL);
    VERIFY(thread1.joinable());
    thread1.join();
    VERIFY(!thread1.joinable());
    }

    {
    int i = 0;
    G42CORE_CONCURRENCY_NS thread thread1(f2, (void*)&i);
    VERIFY(thread1.joinable());
    thread1.join();
    VERIFY(!thread1.joinable());
    VERIFY(i == 1);
    }

    {
    G42CORE_CONCURRENCY_NS thread thread1(f1, (void*)NULL);
    VERIFY(thread1.joinable());
    thread1.join();
    bool caught = false;
    try
    {
        thread1.join();
    }
    // no common base class between exception thrown by boost::thread, std::thread, and G42CORE_CONCURRENCY_NS thread
    // Since this is a unit test it is reasonable to risk catching a non-C++ exception.
    catch(...) 
    {
        caught = true;
    }
    VERIFY(caught);
    }
}

END_TESTS()

