/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_2F1EAE88DA374E4E817F118B850AB1D7
#define G42CORE_HG_2F1EAE88DA374E4E817F118B850AB1D7

#ifndef G42CORE_HG_56B1D5B02B3F4B3695F15A06AFE668B3
#include "../metacode/pragmas.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

#ifndef G42CORE_HG_977EE3D68FC449FDB779CEF0955C0194
#include "../metacode/classes.hpp"
#endif
#ifndef G42CORE_HG_A276488FB6B8426896EB6C3CCB2150EA
#include "namespace.hpp"
#endif
#ifndef G42CORE_HG_A533B033358A43CB9FC53C9C607EC0AE
#include "detail/reporter_outstream.hpp"
#endif

#if defined(G42CORE_TEST_FRAMEWORK_CPPUTEST)

#include "detail/cpputest_main.hpp"

#define G42CORE_TEST_RUN_TESTS() G42CORE_TEST_CPPUTEST_RUN_TESTS(G42CORE_TEST_NS detail::reporter_with_ostream(std::cout), 0, nullptr)

#elif defined(G42CORE_TEST_FRAMEWORK_GTEST)

#include "detail/gtest_main.hpp"

#define G42CORE_TEST_RUN_TESTS() G42CORE_TEST_GTEST_RUN_TESTS(G42CORE_TEST_NS detail::reporter_with_ostream(std::cout), 0, nullptr)

#elif defined(G42CORE_TEST_FRAMEWORK_TUT)

#include "detail/tut_main.hpp"

#define G42CORE_TEST_RUN_TESTS() G42CORE_TEST_TUT_RUN_TESTS(G42CORE_TEST_NS detail::reporter_with_ostream(std::cout), 0, nullptr)

#else

#include "detail/test_part_common.hpp"

#define G42CORE_TEST_RUN_TESTS() G42CORE_TEST_NS detail::test_executor_single_thread_without_test_part_validation<G42CORE_TEST_DEFAULT_TEST_REGISTRY>::run(G42CORE_TEST_NS detail::reporter_with_ostream(std::cout))

#endif

#endif // G42CORE_HG_2F1EAE88DA374E4E817F118B850AB1D7
