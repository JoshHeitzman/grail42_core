/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "stdafx.h"

#include "../reporter_mock.hpp"

#include "g42core/test/detail/gtest_listener_to_reporter_adapter.hpp"

BEGIN_TESTS()

DEFINE_TEST()
{
    typedef reporter_mock<std::string> reporter_mock_std_string;
    typedef G42CORE_TEST_NS detail::gtest_listener_to_reporter_adapter<reporter_mock_std_string> adapter_with_mock;
    typedef G42CORE_METACODE_NS ensure_not_copyable<adapter_with_mock> ensure_not_copyable;

    // ensure default construction and destruction without overt errors
    {
        adapter_with_mock adapter;
    }

    const ::testing::UnitTest& ut = *::testing::UnitTest::GetInstance();
    const ::testing::TestCase tc("name", "a_type_param", 0, 0);
    // Unfortunately TestInfos constructor is private (internally a friend class creates it), so
    // OnTestEnd can not be tested properly, which in turn means that testing of correct calls to
    // the mock's on_tests_complete is also rather limited.
    // TODO workaround the constructor being private by directly setting memory and fill out the
    // unit test.
    char faux_object[sizeof(::testing::TestInfo)];
    const ::testing::TestInfo& ti1 = *(::testing::TestInfo*)&(faux_object[0]);
    (void)ti1; (void)ut;

    std::string filename("filename");
    int line_number = 1;
    std::string header(G42CORE_TEST_DETAIL_GTEST_LISTENER_MESSAGE_HEADER);
    std::string error_message1("error message 1");
    std::stringstream formated_message;
    formated_message << header << error_message1;
    std::stringstream expected_message1;
    expected_message1 << filename << "(" << line_number << "): " << error_message1;
    const ::testing::TestPartResult result(::testing::TestPartResult::kNonFatalFailure, filename.c_str(), 1, formated_message.str().c_str());

    // Verify that a lack of test_completed calls results in 0 passes, 0 fails, all_ok == true,
    // and that calls to on_tests_starting and on_tests_complete occur in the correct order.
    {
    reporter_mock_std_string reporter;
    adapter_with_mock adapter(std::move(reporter));
    mock::sequence s;
    MOCK_EXPECT( reporter.on_tests_starting ).once().in(s);
    MOCK_EXPECT( reporter.on_complete_message ).never();
    MOCK_EXPECT( reporter.on_tests_complete ).once().with(0, 0, 0).in(s);
    adapter.OnTestProgramStart(ut);
    adapter.OnTestProgramEnd(ut);
    VERIFY(mock::verify());
    }

    // Verify that noop methods don't call through to to reporter or cause passed/failed tests to 
    // be reported.
    {
    reporter_mock_std_string reporter;
    adapter_with_mock adapter(std::move(reporter));
    MOCK_EXPECT( reporter.on_tests_starting ).never();
    MOCK_EXPECT( reporter.on_complete_message ).never();
    MOCK_EXPECT( reporter.on_tests_complete ).never();
    adapter.OnTestIterationStart(ut, 0);
    adapter.OnEnvironmentsSetUpStart(ut);
    adapter.OnEnvironmentsSetUpEnd(ut);
    adapter.OnTestCaseStart(tc);
    adapter.OnTestStart(ti1);
    adapter.OnTestCaseEnd(tc);
    adapter.OnEnvironmentsTearDownStart(ut);
    adapter.OnEnvironmentsTearDownEnd(ut);
    adapter.OnTestIterationEnd(ut, 0);
    VERIFY(mock::verify());
    mock::reset();

    mock::sequence s;
    MOCK_EXPECT( reporter.on_tests_starting ).once().in(s);
    MOCK_EXPECT( reporter.on_complete_message ).never();
    MOCK_EXPECT( reporter.on_tests_complete ).once().with(0, 0, 0).in(s);
    adapter.OnTestProgramStart(ut);
    // TODO call OnTestEnd here and modify expected result above
    adapter.OnTestIterationStart(ut, 0);
    adapter.OnEnvironmentsSetUpStart(ut);
    adapter.OnEnvironmentsSetUpEnd(ut);
    adapter.OnTestCaseStart(tc);
    adapter.OnTestStart(ti1);
    adapter.OnTestCaseEnd(tc);
    adapter.OnEnvironmentsTearDownStart(ut);
    adapter.OnEnvironmentsTearDownEnd(ut);
    adapter.OnTestIterationEnd(ut, 0);
    adapter.OnTestProgramEnd(ut);
    ensure(mock::verify());
    }

    // Verify that calling OnTestPartResult results in on_complete_message being called
    {
    reporter_mock_std_string reporter;
    adapter_with_mock adapter(std::move(reporter));

    MOCK_EXPECT( reporter.on_tests_starting ).once();
    MOCK_EXPECT( reporter.on_complete_message ).once().with(expected_message1.str());
    MOCK_EXPECT( reporter.on_tests_complete ).once().with(0, 0, 0);
    adapter.OnTestProgramStart(ut);
    adapter.OnTestPartResult(result);
    adapter.OnTestProgramEnd(ut);
    ensure(mock::verify());
    }
}

END_TESTS()

