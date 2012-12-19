/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_F41077F7FEC44C0DB50ADE014085572E
#define G42CORE_HG_F41077F7FEC44C0DB50ADE014085572E

G42CORE_MC_PRAGMA_ONCE

#define G42CORE_TEST_GTEST_BEGIN_GROUP() namespace {

#define G42CORE_TEST_GTEST_END_GROUP() }

#define G42CORE_TEST_GTEST_DEFINE_TEST() \
GTEST_TEST(only_test_case, BOOST_PP_CAT(test_defined_on_line_, __LINE__) )

#define G42CORE_TEST_GTEST_IF_NOT_REPORT G42CORE_TEST_GTEST_IF_NOT_REPORT_ONLY

#define G42CORE_TEST_GTEST_IF_NOT_REPORT_ONLY(Expression) EXPECT_TRUE(Expression)
#define G42CORE_TEST_GTEST_IF_NOT_REPORT_ABORT_TEST(Expression) ASSERT_TRUE(Expression)

#endif // G42CORE_HG_F41077F7FEC44C0DB50ADE014085572E
