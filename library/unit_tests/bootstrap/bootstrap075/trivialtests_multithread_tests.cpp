/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "stdafx.h"

#include "g42core/test/test.hpp"

G42CORE_TEST_BEGIN_GROUP()

G42CORE_TEST_DEFINE_TEST_PART_MULTITHREADED("Test1")
{
    G42CORE_TEST_IF_NOT_REPORT(true);
// TODO create a way to test expected unit test errors without failing/aborting
// the test run
#if 0 // enable and verify a test fails
    G42CORE_TEST_IF_NOT_REPORT(false);
#endif

}

G42CORE_TEST_DEFINE_TEST_PART_MULTITHREADED("Test2")
{
    G42CORE_TEST_IF_NOT_REPORT(true);
#if 0 // enable and verify a test fails
    G42CORE_TEST_IF_NOT_REPORT(false);
#endif

}

G42CORE_TEST_DEFINE_TEST_PART_MULTITHREADED("Test1")
{
    G42CORE_TEST_IF_NOT_REPORT(true);
// TODO create a way to test expected unit test errors without failing/aborting
// the test run
#if 0 // enable and verify a test fails
    G42CORE_TEST_IF_NOT_REPORT(false);
#endif

}

G42CORE_TEST_DEFINE_TEST_PART_MULTITHREADED("Test2")
{
    G42CORE_TEST_IF_NOT_REPORT(true);
#if 0 // enable and verify a test fails
    G42CORE_TEST_IF_NOT_REPORT(false);
#endif

}

G42CORE_TEST_END_GROUP()

G42CORE_TEST_BEGIN_GROUP()

G42CORE_TEST_DEFINE_TEST_PART_MULTITHREADED("Test3")
{
    G42CORE_TEST_IF_NOT_REPORT(true);
// TODO create a way to test expected unit test errors without failing/aborting
// the test run
#if 0 // enable and verify a test fails
    G42CORE_TEST_IF_NOT_REPORT(false);
#endif

}

G42CORE_TEST_DEFINE_TEST_PART_MULTITHREADED("Test3")
{
    G42CORE_TEST_IF_NOT_REPORT(true);
#if 0 // enable and verify a test fails
    G42CORE_TEST_IF_NOT_REPORT(false);
#endif

}

G42CORE_TEST_END_GROUP()