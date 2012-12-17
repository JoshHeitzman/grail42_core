/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_C03ABA22C2A04F5FB419E6A771232810
#define G42CORE_HG_C03ABA22C2A04F5FB419E6A771232810

#ifndef BOOST_PREPROCESSOR_STRINGIZE_HPP
#include <boost/preprocessor/stringize.hpp>
#endif

#define G42CORE_MC_SVWL_GCC_ANON_NS_WARN_WORKAROUND
#ifndef G42CORE_HG_E42C88FF6CA64B4686A2C6CC0B85DE31
#include "g42core/metacode/sparse_vector_with_list.hpp"
#endif
#undef G42CORE_MC_SVWL_GCC_ANON_NS_WARN_WORKAROUND

G42CORE_MC_PRAGMA_ONCE

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail
{

class tut_test_group_name
{
public:
    tut_test_group_name(const char* sourcefilename):
        name(std::move(unique_name_from_source_filename(sourcefilename)))
    {
    }
    operator const char*()
    {
        return name.c_str();
    }
private:
    const std::string name;

    static const std::string unique_name_from_source_filename(const char* sourcefilename)
    {
        // NOTE As this provides for over 4 billion group names, it seems unnecessary to have a 
        // sepearte counter for each sourcefilename.
        // REVIEW this isn't thread safe.  Use a cryptorandom value instead?  Won't matter if this 
        // is only used to initialize file scope static variables, as those are all initialized on 
        // the the main thread prior to entering main.
        static unsigned int counter = 0;
        ++counter;
        std::stringstream s;
        s << sourcefilename << counter;
        return s.str();
    }
};

struct tut_test_objects_for_svl {};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#ifndef G42CORE_TEST_TUT_MAX_TESTS_PER_GROUP
#define G42CORE_TEST_TUT_MAX_TESTS_PER_GROUP 50
#endif

#define G42CORE_TEST_TUT_TESTS_IN_GROUP_REF() BOOST_PP_CAT(g42core_tut_tests_in_group, __LINE__)

#define G42CORE_TEST_TUT_TESTS_IN_GROUP_DECL(VectorToX) \
typedef G42CORE_METACODE_NS sparse_vector_with_list< \
        boost::mpl::int_< \
            G42CORE_METACODE_NS sparse_vector_with_list< \
                G42CORE_TEST_NS detail::tut_test_objects_for_svl, 0 \
            >::VectorToX<__LINE__>::value>, \
        0> \
    G42CORE_TEST_TUT_TESTS_IN_GROUP_REF();

#define  G42CORE_TEST_TUT_TESTS_IN_GROUP_INDEX() \
    G42CORE_TEST_TUT_TESTS_IN_GROUP_REF()::vector_to_list_index<__LINE__>::value

// TUT requires that test_group template class be specialized with a unique type, an instance of 
// that specialization be created, and a template method on that specialization to be further 
// specialized with a sufficiently smal unique integer for each test in a group.  These macro 
// fulfill these requirements without requiring the client code to define the unique type per 
// group or the sufficiently small unique integer per test.  The unique type is created through 
// the combination of using the preprocessor to create a typename unique within the current file 
// and then defining that typename in an anonymous namespace so it will not conflict symbols from 
// other translation units.  The sufficiently small unique integer is required to be small enough 
// that using __LINE__ isn't practical, so instead a sparse_vector_with_list is used to convert 
// __LINE__ in a indexes into a list of just the lines of interest.

#define G42CORE_TEST_TUT_BEGIN_GROUP() \
namespace { struct BOOST_PP_CAT(g42core_tut_test_group_identifier, __LINE__) {}; } \
typedef tut::test_group< \
        BOOST_PP_CAT(g42core_tut_test_group_identifier, __LINE__), \
        G42CORE_TEST_TUT_MAX_TESTS_PER_GROUP> \
    BOOST_PP_CAT(g42core_tut_test_group, __LINE__); \
G42CORE_MC_SVWL_INITIALIZE_AT( \
    G42CORE_METACODE_NS sparse_vector_with_list< \
        G42CORE_TEST_NS detail::tut_test_objects_for_svl BOOST_PP_COMMA() 0>, \
    __LINE__, \
    BOOST_PP_CAT(g42core_tut_test_group, __LINE__)::object) \
static G42CORE_TEST_NS detail::tut_test_group_name \
    BOOST_PP_CAT(g42core_tut_test_group_name, __LINE__)(__FILE__); \
static BOOST_PP_CAT(g42core_tut_test_group, __LINE__) \
    BOOST_PP_CAT(g42core_tut_test_group_, __LINE__)(BOOST_PP_CAT(g42core_tut_test_group_name, __LINE__)); \
G42CORE_TEST_TUT_TESTS_IN_GROUP_DECL(vector_to_list_index); \
G42CORE_MC_SVWL_INITIALIZE_AT( \
    G42CORE_TEST_TUT_TESTS_IN_GROUP_REF(), __LINE__, boost::mpl::void_) \
namespace tut {

#define G42CORE_TEST_TUT_END_GROUP() }

#define G42CORE_TEST_TUT_DEFINE_TEST() \
} \
G42CORE_TEST_TUT_TESTS_IN_GROUP_DECL(vector_to_prev_list_index); \
G42CORE_MC_SVWL_INITIALIZE_AT( \
    G42CORE_TEST_TUT_TESTS_IN_GROUP_REF(), __LINE__, boost::mpl::void_) \
static_assert( \
    G42CORE_TEST_TUT_TESTS_IN_GROUP_INDEX() > 0, \
    "G42_TEST_BEGIN_GROUP must precede G42_TEST_DEFINE_TEST"); \
 static_assert( \
    G42CORE_TEST_TUT_TESTS_IN_GROUP_INDEX() <= G42CORE_TEST_TUT_MAX_TESTS_PER_GROUP, \
    "Test sequence id must be no more than " BOOST_PP_STRINGIZE(G42CORE_TEST_TUT_MAX_TESTS_PER_GROUP)); \
namespace tut { \
    template<> template<> \
    void G42CORE_METACODE_NS sparse_vector_with_list< \
        G42CORE_TEST_NS detail::tut_test_objects_for_svl BOOST_PP_COMMA() 0 \
    >::vector_to_prev_list_element<__LINE__>::type::test< \
        G42CORE_TEST_TUT_TESTS_IN_GROUP_INDEX()>()

#define G42CORE_TEST_TUT_IF_NOT_REPORT G42CORE_TEST_TUT_IF_NOT_REPORT_ABORT_TEST

#define G42CORE_TEST_TUT_IF_NOT_REPORT_ABORT_TEST(Expression) tut::ensure( \
    __FILE__ "(" BOOST_PP_STRINGIZE(__LINE__) "): " BOOST_PP_STRINGIZE(Expression), \
    Expression);

// REVIEW this isn't exposed in the public interface, as the design may not be
// correct yet.
#define G42CORE_TEST_TUT_BEGIN_GROUP_NAMED(GroupName) \
struct GroupName {}; \
typedef tut::test_group< \
        GroupName, \
        G42CORE_TEST_TUT_MAX_TESTS_PER_GROUP> \
    BOOST_PP_CAT(g42core_tut_test_group, __LINE__); \
G42CORE_MC_SVWL_INITIALIZE_AT( \
    G42CORE_METACODE_NS sparse_vector_with_list< \
        G42CORE_TEST_NS detail::tut_test_objects_for_svl BOOST_PP_COMMA() 0>, \
    __LINE__, \
    BOOST_PP_CAT(g42core_tut_test_group, __LINE__)::object) \
static BOOST_PP_CAT(g42core_tut_test_group, __LINE__) \
    BOOST_PP_CAT(g42core_tut_test_group_, __LINE__)(BOOST_PP_STRINGIZE(GroupName)); \
G42CORE_TEST_TUT_TESTS_IN_GROUP_DECL(vector_to_list_index); \
G42CORE_MC_SVWL_INITIALIZE_AT( \
    G42CORE_TEST_TUT_TESTS_IN_GROUP_REF(), __LINE__, boost::mpl::void_) \
namespace tut {

#endif // G42CORE_HG_C03ABA22C2A04F5FB419E6A771232810
