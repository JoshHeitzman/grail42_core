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

#include <sstream>
#include <typeinfo>

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
#include "cpputest_adapter.hpp"
#elif defined(G42CORE_TEST_FRAMEWORK_GTEST)
#include "gtest_adapter.hpp"
#elif defined(G42CORE_TEST_FRAMEWORK_TUT)
#include "tut_adapter.hpp"
#else

#ifndef G42CORE_HG_07B49624629D491BB307076EE3D66BC6
#include "detail/test_part_common.hpp"
#endif
#ifndef G42CORE_HG_7BC3322891C04BA2BF239B77475FA2AE
#include "detail/test_registration.hpp"
#endif

#define G42CORE_TEST_BEGIN_GROUP G42CORE_TEST_DETAIL_BEGIN_GROUP
#define G42CORE_TEST_END_GROUP G42CORE_TEST_DETAIL_END_GROUP
#define G42CORE_TEST_DEFINE_TEST G42CORE_TEST_DETAIL_DEFINE_TEST

#ifndef G42CORE_HG_DD90B96B22A24EDA98FB3A6124ED98F7
#include "detail/if_not_report.hpp"
#endif

#define G42CORE_TEST_IF_NOT_REPORT G42CORE_TEST_DETAIL_IF_NOT_REPORT

#endif

#endif // G42CORE_HG_DD488BE2CF4B45D39736998E9FC5383D
