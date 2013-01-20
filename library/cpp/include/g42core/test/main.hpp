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

typedef G42CORE_TEST_NS detail::reporter_outstream<
    G42CORE_TEST_NS detail::reporter_outstream_policies<std::ostream> > reporter_with_ostream;

G42CORE_MC_WARNING_PUSH

G42CORE_MC_MSVC_PRAGMA(warning(disable:4512)) // 'class' : assignment operator could not be generated

#ifndef TUT_H_GUARD
#include <tut/tut.hpp>
#endif

G42CORE_MC_WARNING_POP

#include "detail/tut_main.hpp"

#define G42CORE_TEST_RUN_TESTS() G42CORE_TEST_TUT_RUN_TESTS(reporter_with_ostream(std::cout), 0, nullptr)

#endif // G42CORE_HG_2F1EAE88DA374E4E817F118B850AB1D7
