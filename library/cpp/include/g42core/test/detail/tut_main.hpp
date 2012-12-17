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

#ifndef G42CORE_HG_B23E23313A314046AAA5963A99D9CE74
#include "tut_callback_to_reporter_adapter.hpp"
#endif

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

template <template<typename> class Callback = G42CORE_TEST_NS detail::tut_callback_to_reporter_adapter>
struct tut_main
{
    // REVIEW included in prototype.  Still needed?
    static const std::string& identifier()
    {
        static const std::string id("tut");
        return id;
    }

    template <class OutStream>
    static void append_to_stream(OutStream& stream)
    {
        stream << "(via TUT)";
    }

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

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#define G42CORE_TEST_TUT_RUN_TESTS(Reporter, Argc, Argv) G42CORE_TEST_NS detail::tut_main<>::run<>(Reporter)

#endif // G42CORE_HG_961FDCAE328040D8BD7568688ACC2748
