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
#undef G42CORE_TEST_FRAMEWORK_TUT
#include "g42core/test/short_defines.hpp"

#include "../reporter_mock.hpp"

#include "g42core/test/detail/cpputest_output_to_reporter_adapter.hpp"

#include <CppUTest/Utest.h>

BEGIN_TESTS()

DEFINE_TEST()
{
    typedef reporter_mock<std::string> reporter_mock_std_string;
    typedef G42CORE_TEST_NS detail::cpputest_reporter_adapter<reporter_mock_std_string> adapter_with_mock;
    typedef G42CORE_METACODE_NS ensure_not_copyable<adapter_with_mock> ensure_not_copyable;

    // ensure default construction and destruction without overt errors
    {
        adapter_with_mock adapter;
    }

    // Verify that a lack of printCurrentTestEnded and print calls results in 0 passes, 0 fails, 0 skips,
    // and that calls to on_tests_starting and on_tests_complete occur in the correct order.
    {
    reporter_mock_std_string reporter;
    adapter_with_mock adapter(std::move(reporter));
    TestResult testResultDefault(adapter);
    mock::sequence s;
    MOCK_EXPECT( reporter.on_tests_starting ).once().in(s);
    MOCK_EXPECT( reporter.on_complete_message ).never();
    MOCK_EXPECT( reporter.on_tests_complete ).once().with(0, 0, 0).in(s);
    adapter.printTestsStarted();
    adapter.printTestsEnded(testResultDefault);
    VERIFY(mock::verify());
    }

    // Verify that noop methods don't call through to reporter or cause passed/failed tests to 
    // be reported.
    {
    reporter_mock_std_string reporter;
    adapter_with_mock adapter(std::move(reporter));
    TestResult testResultDefault(adapter);
    const char* groupName = "";
    const char* testName = "";
    UtestShell testShell(groupName, testName, 0, 0);
    MOCK_EXPECT( reporter.on_tests_starting ).never();
    MOCK_EXPECT( reporter.on_complete_message ).never();
    MOCK_EXPECT( reporter.on_tests_complete ).never();
    adapter.printCurrentTestStarted(testShell);
    adapter.printCurrentGroupStarted(testShell);
    adapter.printCurrentGroupEnded(testResultDefault);
    adapter.verbose();
    adapter.printBuffer("");
    adapter.print("");
    adapter.print(0l);
    adapter.printDouble(0.0);
    adapter.printHex(0);
    adapter.printTestRun(0, 0);
    adapter.setProgressIndicator("");
    adapter.flush();
    VERIFY(mock::verify());
    mock::reset();

    mock::sequence s;
    MOCK_EXPECT( reporter.on_tests_starting ).once().in(s);
    MOCK_EXPECT( reporter.on_complete_message ).never();
    MOCK_EXPECT( reporter.on_tests_complete ).once().with(0, 0, 0).in(s);
    adapter.printTestsStarted();
    adapter.printCurrentTestStarted(testShell);
    adapter.printCurrentGroupStarted(testShell);
    adapter.printCurrentGroupEnded(testResultDefault);
    adapter.verbose();
    adapter.printBuffer("");
    adapter.print("");
    adapter.print(0l);
    adapter.printDouble(0.0);
    adapter.printHex(0);
    adapter.printTestRun(0, 0);
    adapter.setProgressIndicator("");
    adapter.flush();
    adapter.printTestsEnded(testResultDefault);
    VERIFY(mock::verify());
    }

    // Verify that a result with no failures deson't result in on_complete_message being called
    // and the correct number of passed tests is reported.
    {
    reporter_mock_std_string reporter;
    adapter_with_mock adapter(std::move(reporter));
    TestResult testResultDefault(adapter);
    TestResult testResultDefault1(adapter);
    TestResult testResultDefault2(adapter);

    MOCK_EXPECT( reporter.on_tests_starting ).once();
    MOCK_EXPECT( reporter.on_complete_message ).never();
    MOCK_EXPECT( reporter.on_tests_complete ).once().with(2, 0, 0);
    adapter.printTestsStarted();
    adapter.printCurrentTestEnded(testResultDefault1);
    adapter.printCurrentTestEnded(testResultDefault2);
    adapter.printTestsEnded(testResultDefault);
    VERIFY(mock::verify());
    }

    // Verify that a result with failures results in on_complete_message being called
    // and the correct number of passed tests is reported.
    {
    reporter_mock_std_string reporter;
    adapter_with_mock adapter(std::move(reporter));
    TestResult testResultDefault(adapter);
    TestResult testResultDefault1(adapter);
    TestResult testResultDefault2(adapter);
    const char* groupName = "";
    const char* testName = "";
    UtestShell testShell(groupName, testName, 0, 0);
    std::string error_message1("error message 1");
    std::string full_error_message1("(0): ");
    full_error_message1.append(error_message1);
    SimpleString str(error_message1.c_str());
    TestFailure testFailure(&testShell, str);

    MOCK_EXPECT( reporter.on_tests_starting ).once();
    MOCK_EXPECT( reporter.on_complete_message ).once().with(full_error_message1.c_str());
    MOCK_EXPECT( reporter.on_tests_complete ).once().with(1, 1, 0);
    adapter.printTestsStarted();
    testResultDefault2.addFailure(testFailure);
    adapter.printCurrentTestEnded(testResultDefault1);
    adapter.printCurrentTestEnded(testResultDefault2);
    adapter.printTestsEnded(testResultDefault);
    VERIFY(mock::verify());
    }
}

END_TESTS()
