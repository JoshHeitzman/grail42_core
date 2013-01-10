/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_B0B70F0DBCA6477BA7F85D09116580FC
#define G42CORE_HG_B0B70F0DBCA6477BA7F85D09116580FC

#ifndef BOOST_PREPROCESSOR_CAT_HPP
#include <boost/preprocessor/cat.hpp>
#endif

#ifndef BOOST_PREPROCESSOR_STRINGIZE_HPP
#include <boost/preprocessor/stringize.hpp>
#endif

#ifndef BOOST_PREPROCESSOR_PUNCTUATION_COMMA_HPP
#include <boost/preprocessor/comma.hpp>
#endif

#define G42CORE_MC_SVWL_GCC_ANON_NS_WARN_WORKAROUND
#ifndef G42CORE_HG_E42C88FF6CA64B4686A2C6CC0B85DE31
#include "../../metacode/sparse_vector_with_list.hpp"
#endif
#undef G42CORE_MC_SVWL_GCC_ANON_NS_WARN_WORKAROUND

G42CORE_MC_PRAGMA_ONCE

G42CORE_MC_MSVC_PRAGMA(warning(disable:4127)) // conditional expression is constant

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail
{

struct cpputest_test_groups_for_svl {};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#define G42CORE_TEST_CPPUTEST_BEGIN_GROUP() \
namespace { \
struct BOOST_PP_CAT(BOOST_PP_CAT(TEST_GROUP_, __LINE__), testGroup) : public Utest {}; \
} \
G42CORE_MC_SVWL_INITIALIZE_AT(G42CORE_METACODE_NS sparse_vector_with_list<G42CORE_TEST_NS detail::cpputest_test_groups_for_svl BOOST_PP_COMMA() 0>, __LINE__, BOOST_PP_CAT(BOOST_PP_CAT(TEST_GROUP_, __LINE__), testGroup) ) \

#define G42CORE_TEST_CPPUTEST_END_GROUP()

#define G42CORE_TEST_CPPUTEST_DEFINE_TEST() \
namespace { \
typedef G42CORE_METACODE_NS sparse_vector_with_list<G42CORE_TEST_NS detail::cpputest_test_groups_for_svl BOOST_PP_COMMA() 0>::vector_to_prev_list_element<__LINE__>::type BOOST_PP_CAT(BOOST_PP_CAT(TEST_, __LINE__), _Test_Base); \
class BOOST_PP_CAT(BOOST_PP_CAT(TEST_, __LINE__), _Test) : public BOOST_PP_CAT(BOOST_PP_CAT(TEST_, __LINE__), _Test_Base) \
{ public: BOOST_PP_CAT(BOOST_PP_CAT(TEST_, __LINE__), _Test) () : BOOST_PP_CAT(BOOST_PP_CAT(TEST_, __LINE__), _Test_Base) () {} \
       void testBody(); }; \
class BOOST_PP_CAT(BOOST_PP_CAT(TEST_, __LINE__), _TestShell) : public UtestShell { \
    virtual Utest* createTest() { return new BOOST_PP_CAT(BOOST_PP_CAT(TEST_, __LINE__), _Test); } \
} BOOST_PP_CAT(BOOST_PP_CAT(TEST_, __LINE__), _TestShell_instance); \
TestInstaller BOOST_PP_CAT(BOOST_PP_CAT(TEST_, __LINE__), _Installer)(BOOST_PP_CAT(BOOST_PP_CAT(TEST_, __LINE__), _TestShell_instance), BOOST_PP_STRINGIZE(BOOST_PP_CAT(test_a_group_defined_before_, __LINE__)), BOOST_PP_STRINGIZE(BOOST_PP_CAT(test_defined_at_, __LINE__)), __FILE__,__LINE__); \
} \
void BOOST_PP_CAT(BOOST_PP_CAT(TEST_, __LINE__), _Test)::testBody()

#define G42CORE_TEST_CPPUTEST_IF_NOT_REPORT(Expression) \
{ UtestShell::getTestResult()->countCheck(); \
if(!((Expression) != 0)) { \
    UtestShell::getTestResult()->addFailure(CheckFailure(UtestShell::getCurrent(), __FILE__, __LINE__, "CHECK_REPORT_ONLY", BOOST_PP_STRINGIZE(Expression))); } }

#define G42CORE_TEST_CPPUTEST_IF_NOT_REPORT_ABORT_TEST(Expression) CHECK(Expression)

#endif // G42CORE_HG_B0B70F0DBCA6477BA7F85D09116580FC
