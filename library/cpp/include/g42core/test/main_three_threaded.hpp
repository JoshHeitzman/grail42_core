/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_58E27C97EE6A414E830ABAC3D5B77C7A
#define G42CORE_HG_58E27C97EE6A414E830ABAC3D5B77C7A

#ifndef G42CORE_HG_A276488FB6B8426896EB6C3CCB2150EA
#include "namespace.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

#include <sstream>
#include "main.hpp"
#include "detail/gtest_main.hpp"
#include "detail/tut_main.hpp"
#include "detail/cpputest_main.hpp"
#include "../concurrency/thread.hpp"

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

struct main_three_threaded
{
    static int run()
    {
        std::stringstream tut_ss;
        typedef G42CORE_TEST_NS detail::tut_thread<decltype(tut_ss), G42CORE_TEST_NS detail::reporter_outstream> tut_thread_ss;
        tut_thread_ss tut_thread_functor(tut_ss, 0, 0);
        G42CORE_CONCURRENCY_NS thread tut_thread(tut_thread_ss::thread_func, &tut_thread_functor);

        std::stringstream gtest_ss;
        typedef G42CORE_TEST_NS detail::gtest_thread<decltype(gtest_ss), G42CORE_TEST_NS detail::reporter_outstream> gtest_thread_ss;
        gtest_thread_ss gtest_thread_functor(gtest_ss, 0, 0);
        G42CORE_CONCURRENCY_NS thread gtest_thread(gtest_thread_ss::thread_func, &gtest_thread_functor);

        std::stringstream cpputest_ss;
        typedef G42CORE_TEST_NS detail::cpputest_thread<decltype(cpputest_ss), G42CORE_TEST_NS detail::reporter_outstream> cpputest_thread_ss;
        cpputest_thread_ss cpputest_thread_functor(cpputest_ss, 0, 0);
        G42CORE_CONCURRENCY_NS thread cpputest_thread(cpputest_thread_ss::thread_func, &cpputest_thread_functor);

        tut_thread.join();
        gtest_thread.join();
        cpputest_thread.join();

        std::cout << tut_ss.str();
        std::cout << gtest_ss.str();
        std::cout << cpputest_ss.str();

        return tut_thread_functor.result() | gtest_thread_functor.result() | cpputest_thread_functor.result();
    }
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#define G42CORE_TEST_RUN_TESTS_THREE_THREADED() G42CORE_TEST_NS detail::main_three_threaded::run()

#endif // G42CORE_HG_58E27C97EE6A414E830ABAC3D5B77C7A
