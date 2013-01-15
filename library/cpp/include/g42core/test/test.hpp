/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_DD488BE2CF4B45D39736998E9FC5383D
#define G42CORE_HG_DD488BE2CF4B45D39736998E9FC5383D

#ifndef G42CORE_HG_56B1D5B02B3F4B3695F15A06AFE668B3
#include "../metacode/pragmas.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

#if defined(G42CORE_TEST_FRAMEWORK_CPPUTEST)
#include "cpputest_adapter.hpp"
#elif defined(G42CORE_TEST_FRAMEWORK_GTEST)
#include "gtest_adapter.hpp"
#elif defined(G42CORE_TEST_FRAMEWORK_TUT)
#include "tut_adapter.hpp"
#else
// TODO replace with grail42 native test framework
#include "tut_adapter.hpp"
#endif

#endif // G42CORE_HG_DD488BE2CF4B45D39736998E9FC5383D
