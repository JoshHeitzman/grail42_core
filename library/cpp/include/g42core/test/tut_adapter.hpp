/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_B51A3C840B644C4E8D02FB145152DC3D
#define G42CORE_HG_B51A3C840B644C4E8D02FB145152DC3D

#ifndef G42CORE_HG_A276488FB6B8426896EB6C3CCB2150EA
#include "g42core/test/namespace.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

G42CORE_MC_WARNING_PUSH

G42CORE_MC_MSVC_WARNING_DISABLE_4512

#ifndef TUT_H_GUARD
#include <tut/tut.hpp>
#endif

G42CORE_MC_WARNING_POP

#ifndef G42CORE_HG_977EE3D68FC449FDB779CEF0955C0194
#include "g42core/metacode/classes.hpp"
#endif

#ifndef G42CORE_HG_C03ABA22C2A04F5FB419E6A771232810
#include "detail/detail_tut_adapter.hpp"
#endif

#define G42CORE_TEST_BEGIN_GROUP G42CORE_TEST_TUT_BEGIN_GROUP
#define G42CORE_TEST_END_GROUP G42CORE_TEST_TUT_END_GROUP
#define G42CORE_TEST_DEFINE_TEST G42CORE_TEST_TUT_DEFINE_TEST
#define G42CORE_TEST_IF_NOT_REPORT G42CORE_TEST_TUT_IF_NOT_REPORT

#endif // G42CORE_HG_B51A3C840B644C4E8D02FB145152DC3D
