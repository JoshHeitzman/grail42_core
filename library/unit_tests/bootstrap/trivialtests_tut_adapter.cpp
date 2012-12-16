/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "g42core/test/namespace.hpp"
#include "g42core/test/detail/detail_tut_adapter.hpp"

// While this is heavy handed, GCC does not provide a way to just disable the following warning:
// warning : 'g42::core::metacode::detail::svlw_element<g42::core::metacode::sparse_vector_with_list<g42::core::test::detail::tut_test_objects_for_svl, 0>, 16>' has a base 'g42::core::metacode::detail::svlw_elment_set<g42::core::metacode::sparse_vector_with_list<g42::core::test::detail::tut_test_objects_for_svl, 0>, 16, tut::test_object<<unnamed>::g42_tut_test_group_identifier16> >' whose type uses the anonymous namespace
#pragma warning(push)
#pragma warning(disable : 4068) // unknown pragma
#pragma GCC system_header
#pragma warning(pop)

// The test only verifies that the TUT internal adapter API compiles correctly, links correctly 
// and that that the successful test executions show up in the summary output.  Failures have to be
// manually validated by tweaking the preprocessor logic below.

G42CORE_TEST_TUT_BEGIN_GROUP()

G42CORE_TEST_TUT_DEFINE_TEST()
{

    G42CORE_TEST_TUT_IF_NOT_REPORT_ABORT_TEST(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT_ABORT_TEST(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT_ABORT_TEST(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT(true);
// TODO create a way to test expected unit test errors without failing/aborting
// the test run
#if 0 // enable and verify a test fails
    G42CORE_TEST_TUT_IF_NOT_REPORT(false);
#endif

}

G42CORE_TEST_TUT_DEFINE_TEST()
{

    G42CORE_TEST_TUT_IF_NOT_REPORT_ABORT_TEST(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT_ABORT_TEST(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT_ABORT_TEST(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT(true);
#if 0 // enable and verify a test fails
    G42CORE_TEST_TUT_IF_NOT_REPORT(false);
#endif

}

G42CORE_TEST_TUT_DEFINE_TEST()
{

    G42CORE_TEST_TUT_IF_NOT_REPORT_ABORT_TEST(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT_ABORT_TEST(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT_ABORT_TEST(true);
    G42CORE_TEST_TUT_IF_NOT_REPORT(true);

}

G42CORE_TEST_TUT_END_GROUP()
