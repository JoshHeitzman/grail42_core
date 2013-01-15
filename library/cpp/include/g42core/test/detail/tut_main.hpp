/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_961FDCAE328040D8BD7568688ACC2748
#define G42CORE_HG_961FDCAE328040D8BD7568688ACC2748

G42CORE_MC_PRAGMA_ONCE

#ifndef G42CORE_HG_8970E8BF17E44A67BC741E458157A037
#include "framework_thread.hpp"
#endif

#ifndef G42CORE_HG_B23E23313A314046AAA5963A99D9CE74
#include "tut_callback_to_reporter_adapter.hpp"
#endif

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

template <template<typename> class Callback = G42CORE_TEST_NS detail::tut_callback_to_reporter_adapter>
struct tut_main
{
    template <typename Reporter>
    static int run(Reporter&& reporter)
    {
        tut::test_runner_singleton runner;
        ((void)runner);
        Callback<Reporter> callback(std::move(reporter));
        tut::test_runner_singleton::get().set_callback(&callback);
        tut::test_runner_singleton::get().run_tests();
        return callback.all_ok() ? 0 : 1;
    }
};

struct tut_append_note
{
    template <class OutStream>
    static void append_to_stream(OutStream& outStream)
    {
        outStream << "(via TUT)";
    }
};

#define G42CORE_TEST_TUT_RUN_TESTS(Reporter, Argc, Argv) G42CORE_TEST_NS detail::tut_main<>::run<>(Reporter)

template <class OutStream, template<typename> class Reporter>
class tut_thread : public framework_thread<OutStream, Reporter>
{
G42CORE_MC_NOT_COPYABLE(tut_thread)
public:
    typedef tut_thread<OutStream, Reporter> type;
    typedef reporter_outstream_policies<OutStream, reporter_outstream_formatter_char<reporter_outstream_formatter_header_char<tut_append_note> > > reporter_policy;
    typedef Reporter<reporter_policy> reporter_with_policy;
    tut_thread(OutStream& outStream, int argc, char* argv[]):
        framework_thread<OutStream, Reporter>(outStream, argc, argv)
    {}

    static void* thread_func(void* p)
    {
        type* this_ = reinterpret_cast<type*>(p);
        this_->result_ = G42CORE_TEST_TUT_RUN_TESTS(reporter_with_policy(this_->outStream), this_->argc, this_->argv);
        return NULL;
    }

    // REVIEW included in prototype.  Still needed?
    static const std::string& identifier()
    {
        static const std::string id("tut");
        return id;
    }
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_961FDCAE328040D8BD7568688ACC2748
