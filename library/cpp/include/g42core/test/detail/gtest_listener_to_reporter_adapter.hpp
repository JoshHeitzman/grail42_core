/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_1549DB5609BD466882EF863F21ADE601
#define G42CORE_HG_1549DB5609BD466882EF863F21ADE601

G42CORE_MC_PRAGMA_ONCE

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
#define GTEST_DONT_DEFINE_TEST 1
#include <gtest/gtest.h>
#endif

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail
{

#define G42CORE_TEST_DETAIL_GTEST_LISTENER_MESSAGE_HEADER "Value of: "

template <class Reporter>
class gtest_listener_to_reporter_adapter : public ::testing::TestEventListener
{
G42CORE_MC_NOT_COPYABLE(gtest_listener_to_reporter_adapter)
public:
    gtest_listener_to_reporter_adapter():
        passed(0),
        skipped(0),
        failed(0),
        reporter() {}

    explicit gtest_listener_to_reporter_adapter(Reporter&& reporter):
        passed(0),
        skipped(0),
        failed(0),
        reporter(std::move(reporter)) {}

    virtual ~gtest_listener_to_reporter_adapter() {}

    // The following methods override what's in the TestEventListener class.
    virtual void OnTestProgramStart(const ::testing::UnitTest& /*unit_test*/)
    {
        reporter.on_tests_starting();
    }

    virtual void OnTestPartResult(const ::testing::TestPartResult& result)
    {
        // REVIEW can the adapter macros wrap the raw message so that it an be robustly extracted?
        // FRAGILE gtest doesn't provide a hook for the raw message, so it is necessary to extract
        // the raw message from the formatted message, so any changes in the formatting will break
        // this.
        // TODO handle find or substr failing.
        std::string s(result.message());
        const std::string::size_type i = sizeof(G42CORE_TEST_DETAIL_GTEST_LISTENER_MESSAGE_HEADER)-1;
        s = s.substr(i, s.find('\n')-i);
        std::stringstream ss;
        ss << result.file_name() << "(" << result.line_number() << "): " << s;
        reporter.on_complete_message(ss.str());
    }

    virtual void OnTestEnd(const ::testing::TestInfo& test_info)
    {
        if(test_info.result()->Failed())
        {
            ++failed;
        }
        else if(test_info.result()->Passed())
        {
            ++passed;
        }
        else if(!test_info.should_run())
        {
            ++skipped;
        }
    }
    virtual void OnTestProgramEnd(const ::testing::UnitTest& /*unit_test*/)
    {
        reporter.on_tests_complete(passed, failed, skipped);
    }

    // The common reporter does not include an equivalent as not all unit test frameworks 
    // provide these events.  Explicitly make these noops in case base ever provides non-noop
    // implementations.
    virtual void OnTestIterationStart(const ::testing::UnitTest&, int) {}
    virtual void OnEnvironmentsSetUpStart(const ::testing::UnitTest&) {}
    virtual void OnEnvironmentsSetUpEnd(const ::testing::UnitTest&) {}
    virtual void OnTestCaseStart(const ::testing::TestCase&) {}
    virtual void OnTestStart(const ::testing::TestInfo&) {}
    virtual void OnTestCaseEnd(const ::testing::TestCase&) {}
    virtual void OnEnvironmentsTearDownStart(const ::testing::UnitTest&) {}
    virtual void OnEnvironmentsTearDownEnd(const ::testing::UnitTest& ) {}
    virtual void OnTestIterationEnd(const ::testing::UnitTest&, int ) {}

private:
    int passed;
    int skipped;
    int failed;
    Reporter reporter;
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_1549DB5609BD466882EF863F21ADE601
