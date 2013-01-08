/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_BF13623FF71347EBA031ED83ADDA8ACE
#define G42CORE_HG_BF13623FF71347EBA031ED83ADDA8ACE

G42CORE_MC_PRAGMA_ONCE

G42CORE_MC_WARNING_PUSH
G42CORE_MC_MSVC_PRAGMA(warning(disable:4512)) // 'TestResult' : assignment operator could not be generated
G42CORE_MC_MSVC_PRAGMA(warning(disable:4290)) // C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestOutput.h>
G42CORE_MC_WARNING_POP

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail
{

template <class Reporter>
class cpputest_reporter_adapter : public TestOutput
{
public:
    explicit cpputest_reporter_adapter():
        passed(0),
        skipped(0),
        failed(0),
        assertion_failures(0),
        reporter() {}

    explicit cpputest_reporter_adapter(Reporter&& reporter):
        passed(0),
        skipped(0),
        failed(0),
        assertion_failures(0),
        reporter(std::move(reporter)) {}

    virtual ~cpputest_reporter_adapter() {}

    virtual void printTestsStarted()
    {
        reporter.on_tests_starting();
    }

    virtual void printTestsEnded(const TestResult&)
    {
        reporter.on_tests_complete(passed, failed, skipped);
    }

    virtual void printCurrentTestEnded(const TestResult& res)
    {
        if(res.getFailureCount() > assertion_failures)
        {
            assertion_failures = res.getFailureCount();
            ++failed;
        }
        else
        {
            ++passed;
        }
    }

    virtual void print(const TestFailure& failure)
    {
        // REVIEW can the adapter macros wrap the raw message so that it an be robustly extracted?
        // FRAGILE cpputest doesn't provide a hook for the raw message, so it is necessary to extract
        // the raw message from the formatted message, so any changes in the formatting will break
        // this.
        // TODO handle find or substr failing.
        std::string s(failure.getMessage().asCharString());
        const std::string::size_type i = s.find('(')+1;
        s = s.substr(i, s.find(')')-i);
        std::stringstream ss;
        ss << failure.getFileName().asCharString() << "(" << failure.getFailureLineNumber() << "): " << s;
        reporter.on_complete_message(ss.str());
    }

    // The common reporter does not include an equivalent as not all unit test frameworks 
    // provide these events.  Explicitly make these noops in case base ever provides non-noop
    // implementations.
    virtual void printCurrentTestStarted(const UtestShell&) {}
    virtual void printCurrentGroupStarted(const UtestShell&) {}
    virtual void printCurrentGroupEnded(const TestResult&) {}
    virtual void verbose() {}
    virtual void printBuffer(const char*) {}
    virtual void print(const char*) {}
    virtual void print(long) {}
    virtual void printDouble(double) {}
    virtual void printHex(long) {}
    virtual void printTestRun(int, int) {}
    virtual void setProgressIndicator(const char*) {}
    virtual void flush() {}
private:
    int passed;
    int skipped;
    int failed;
    int assertion_failures;
    Reporter reporter;
};


} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_BF13623FF71347EBA031ED83ADDA8ACE
