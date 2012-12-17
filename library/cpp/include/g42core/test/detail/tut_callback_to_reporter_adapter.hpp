/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_B23E23313A314046AAA5963A99D9CE74
#define G42CORE_HG_B23E23313A314046AAA5963A99D9CE74

#ifndef TUT_RUNNER_H_GUARD
#include <tut/tut_runner.hpp>
#endif

G42CORE_MC_PRAGMA_ONCE

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail
{

template <class Reporter>
class tut_callback_to_reporter_adapter : public tut::callback
{
G42CORE_MC_NOT_COPYABLE(tut_callback_to_reporter_adapter)
public:
    tut_callback_to_reporter_adapter():
        all_ok_(true),
        passed(0),
        skipped(0),
        failed(0),
        reporter() {}

    explicit tut_callback_to_reporter_adapter(Reporter&& reporter):
        all_ok_(true),
        passed(0),
        skipped(0),
        failed(0),
        reporter(std::move(reporter)) {}

    virtual ~tut_callback_to_reporter_adapter() {}

    virtual void run_started()
    {
        reporter.on_tests_starting();
    }

    virtual void test_completed(const tut::test_result& tr)
    {
#if defined(G42CORE_TEST_TUT_ENABLE_SKIP_TEST)
        // FUTURE skipped was added in the svn trunk but hasn't been included in a packaged 
        // release (as of 2012/12/13).
        bool notOkay = !(tr.result == tr.ok || tr.result == tr.skipped);
#else
        bool notOkay = !(tr.result == tr.ok);
#endif

        if(notOkay)
        {
            all_ok_ = false;
            ++failed;
            // output is only desired when some kind of failure occurs
            if(tr.message.size() > 0)
            {
                reporter.on_complete_message(tr.message);
            }
        }
        else
        {
            if(tr.result == tr.ok) ++passed;
#if defined(G42CORE_TEST_TUT_ENABLE_SKIP_TEST)
            if(tr.result == tr.skipped) ++skipped;
#endif
        }
    }

    virtual void run_completed()
    {
        reporter.on_tests_complete(passed, failed, skipped);
    }

    virtual bool all_ok() const
    {
        return all_ok_;
    }

    // The common reporter does not include an equivalent as not all unit test frameworks 
    // provide this event.  Explicitly makes these noops in case base ever provides non-noop
    // implementations.
    virtual void group_started(const std::string&) {}
    virtual void group_completed(const std::string&) {}

private:
    bool all_ok_;
    unsigned int passed;
    unsigned int skipped;
    unsigned int failed;
    Reporter reporter;
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_B23E23313A314046AAA5963A99D9CE74
