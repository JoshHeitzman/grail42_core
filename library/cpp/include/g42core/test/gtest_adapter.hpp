/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_CF4812F1513C4F08B64B3B6341339D68
#define G42CORE_HG_CF4812F1513C4F08B64B3B6341339D68

#ifndef G42CORE_HG_A276488FB6B8426896EB6C3CCB2150EA
#include "namespace.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
#define GTEST_DONT_DEFINE_TEST 1
#include <gtest/gtest.h>
#endif

#ifndef G42CORE_HG_F41077F7FEC44C0DB50ADE014085572E
#include "detail/detail_gtest_adapter.hpp"
#endif

#define G42CORE_TEST_BEGIN_GROUP G42CORE_TEST_GTEST_BEGIN_GROUP
#define G42CORE_TEST_END_GROUP G42CORE_TEST_GTEST_END_GROUP
#define G42CORE_TEST_DEFINE_TEST G42CORE_TEST_GTEST_DEFINE_TEST
#define G42CORE_TEST_IF_NOT_REPORT G42CORE_TEST_GTEST_IF_NOT_REPORT

#endif // G42CORE_HG_CF4812F1513C4F08B64B3B6341339D68
