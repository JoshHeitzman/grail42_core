/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

// The test only verifies that the public API compiles correctly, links correctly and that 
// the successful test executions show up in the summary output.  Failures have to be manually 
// validated by tweaking the preprocessor logic below.

G42CORE_TEST_BEGIN_GROUP()

G42CORE_TEST_DEFINE_TEST()
{

    G42CORE_TEST_IF_NOT_REPORT(true);
    G42CORE_TEST_IF_NOT_REPORT(true);
    G42CORE_TEST_IF_NOT_REPORT(true);
// TODO create a way to test expected unit test errors without failing/aborting
// the test run
#if 0 // enable and verify a test fails
    G42CORE_TEST_IF_NOT_REPORT(false);
#endif

}

G42CORE_TEST_DEFINE_TEST()
{

    G42CORE_TEST_IF_NOT_REPORT(true);
    G42CORE_TEST_IF_NOT_REPORT(true);
    G42CORE_TEST_IF_NOT_REPORT(true);
#if 0 // enable and verify a test fails
    G42CORE_TEST_IF_NOT_REPORT(false);
#endif

}

G42CORE_TEST_DEFINE_TEST()
{

    G42CORE_TEST_IF_NOT_REPORT(true);
    G42CORE_TEST_IF_NOT_REPORT(true);
    G42CORE_TEST_IF_NOT_REPORT(true);

}

G42CORE_TEST_END_GROUP()

G42CORE_TEST_BEGIN_GROUP()

G42CORE_TEST_DEFINE_TEST()
{

    G42CORE_TEST_IF_NOT_REPORT(true);
    G42CORE_TEST_IF_NOT_REPORT(true);
    G42CORE_TEST_IF_NOT_REPORT(true);
// TODO create a way to test expected unit test errors without failing/aborting
// the test run
#if 0 // enable and verify a test fails
    G42CORE_TEST_IF_NOT_REPORT(false);
#endif

}

G42CORE_TEST_DEFINE_TEST()
{

    G42CORE_TEST_IF_NOT_REPORT(true);
    G42CORE_TEST_IF_NOT_REPORT(true);
    G42CORE_TEST_IF_NOT_REPORT(true);
#if 0 // enable and verify a test fails
    G42CORE_TEST_IF_NOT_REPORT(false);
#endif

}

G42CORE_TEST_DEFINE_TEST()
{

    G42CORE_TEST_IF_NOT_REPORT(true);
    G42CORE_TEST_IF_NOT_REPORT(true);
    G42CORE_TEST_IF_NOT_REPORT(true);

}

G42CORE_TEST_END_GROUP()
