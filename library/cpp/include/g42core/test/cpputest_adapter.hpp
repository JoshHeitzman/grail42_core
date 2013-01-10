/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_26F4B19B668146C693632DDE7F547D0E
#define G42CORE_HG_26F4B19B668146C693632DDE7F547D0E

#ifndef G42CORE_HG_A276488FB6B8426896EB6C3CCB2150EA
#include "namespace.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

#ifndef D_UTest_h
#include <CppUTest/Utest.h>
#endif
#ifndef D_TestResult_h
G42CORE_MC_WARNING_PUSH
G42CORE_MC_MSVC_PRAGMA(warning(disable:4512)) // 'TestResult' : assignment operator could not be generated
#include <CppUTest/TestResult.h>
G42CORE_MC_WARNING_POP
#endif
#ifndef D_TestFailure_H
#include <CppUTest/TestFailure.h>
#endif

#ifndef G42CORE_HG_B0B70F0DBCA6477BA7F85D09116580FC
#include "detail/detail_cpputest_adapter.hpp"
#endif

#define G42CORE_TEST_BEGIN_GROUP G42CORE_TEST_CPPUTEST_BEGIN_GROUP
#define G42CORE_TEST_END_GROUP G42CORE_TEST_CPPUTEST_END_GROUP
#define G42CORE_TEST_DEFINE_TEST G42CORE_TEST_CPPUTEST_DEFINE_TEST
#define G42CORE_TEST_IF_NOT_REPORT G42CORE_TEST_CPPUTEST_IF_NOT_REPORT

#endif // G42CORE_HG_26F4B19B668146C693632DDE7F547D0E
