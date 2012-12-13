/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "g42core/metacode/sparse_vector_with_list.hpp"

template <typename sequence, int vector_index>
struct vector_index_attributes
{
    typedef typename sequence::template vector_to_list_index<vector_index>::type list_index;
    typedef typename sequence::template is_set_at<vector_index>::type element_set;
    typedef typename sequence::template vector_to_prev_list_index<vector_index>::type prev_list_index;
};

template <typename sequence, int vector_index, int expected_prior_list_index, int unique_id=0>
struct ensure_no_element_at
{
    typedef vector_index_attributes<sequence, vector_index> attributes;
    BOOST_STATIC_ASSERT((attributes::list_index::value == -1));
    BOOST_MPL_ASSERT_NOT((typename attributes::element_set));
    BOOST_STATIC_ASSERT((attributes::prev_list_index::value == expected_prior_list_index));
};

template <typename sequence, int vector_index, int unique_id=0>
struct ensure_no_element_at_or_before : 
    ensure_no_element_at<sequence, vector_index, -1, unique_id>
{
};

template <typename sequence, int vector_index, int expected_prior_list_index, int unique_id=0>
struct ensure_no_element_at_but_one_prior : 
    ensure_no_element_at<sequence, vector_index, expected_prior_list_index, unique_id>
{
};

template <typename sequence, int vector_index, int expected_list_index, typename expected_type = boost::mpl::void_>
struct ensure_element_at
{
    typedef vector_index_attributes<sequence, vector_index> attributes;
    BOOST_STATIC_ASSERT((attributes::list_index::value == expected_list_index));
    BOOST_MPL_ASSERT((typename attributes::element_set));
    BOOST_STATIC_ASSERT((attributes::prev_list_index::value == expected_list_index-1));
    // An element only has a type attribute if it was set, so lots of hoop jumping to be able
    // check it versus the expected type when present, and not have a compile error when not 
    // present.
    BOOST_MPL_ASSERT((typename boost::mpl::if_< 
        typename boost::mpl::greater_equal<typename attributes::prev_list_index, boost::mpl::int_<0> >,
        typename std::template is_same<
            typename boost::mpl::eval_if<
                typename boost::mpl::greater_equal<typename attributes::prev_list_index, boost::mpl::int_<0> >,
                boost::mpl::identity<typename sequence::template vector_to_prev_list_element<vector_index> >,
                boost::mpl::identity<boost::mpl::identity<attributes> >
            >::type::type,
            expected_type
        >,
        typename boost::mpl::template bool_<true>
    >));
};

typedef G42CORE_METACODE_NS sparse_vector_with_list<void, 0> sequence_void_0;
// should be able to check unset elements non-consecutively
template struct ensure_no_element_at_or_before<sequence_void_0, 1>;
template struct ensure_no_element_at_or_before<sequence_void_0, 3>;
template struct ensure_no_element_at_or_before<sequence_void_0, 5>;
// and then go back check unset elements at indexes that were skipped over
template struct ensure_no_element_at_or_before<sequence_void_0, 4>;
template struct ensure_no_element_at_or_before<sequence_void_0, 2>;
template struct ensure_no_element_at_or_before<sequence_void_0, 0>;
// and should be able to check them all again and still get the same result
template struct ensure_no_element_at_or_before<sequence_void_0, 5, 1>;
template struct ensure_no_element_at_or_before<sequence_void_0, 4, 1>;
template struct ensure_no_element_at_or_before<sequence_void_0, 2, 1>;
template struct ensure_no_element_at_or_before<sequence_void_0, 1, 1>;
template struct ensure_no_element_at_or_before<sequence_void_0, 0, 1>;
template struct ensure_no_element_at_or_before<sequence_void_0, 3, 1>;

// Should not be able to initialize an element an index <= than the highest index that has
// has been set or accessed already.

// TODO create a way to test expected compile errors without failing the build
#if 0 // enable and verify fails to compile
G42CORE_METACODE_BEGIN_NAMESPACES namespace detail {
template <> struct svlw_element<sequence_void_0, 3> : svlw_elment_set<sequence_void_0, 3, boost::mpl::void_ > {};
} G42CORE_METACODE_END_NAMESPACES
#endif
#if 0 // enable and verify fails to compile
G42CORE_METACODE_BEGIN_NAMESPACES namespace detail {
template <> struct svlw_element<sequence_void_0, 5> : svlw_elment_set<sequence_void_0, 5, boost::mpl::void_ > {};
} G42CORE_METACODE_END_NAMESPACES
#endif

// Should be able to initialize element an indexes > than the highest index that has
// has been set or accessed already.

G42CORE_METACODE_BEGIN_NAMESPACES namespace detail {
template <> struct svlw_element<sequence_void_0, 6> : svlw_elment_set<sequence_void_0, 6, boost::mpl::int_<-6> > {};
} G42CORE_METACODE_END_NAMESPACES
template struct ensure_element_at<sequence_void_0, 6, 0>;

G42CORE_METACODE_BEGIN_NAMESPACES namespace detail {
template <> struct svlw_element<sequence_void_0, 8> : svlw_elment_set<sequence_void_0, 8, boost::mpl::int_<-8> > {};
} G42CORE_METACODE_END_NAMESPACES
template struct ensure_element_at<sequence_void_0, 8, 1, boost::mpl::int_<-6> >;

G42CORE_METACODE_BEGIN_NAMESPACES namespace detail {
template <> struct svlw_element<sequence_void_0, 9> : svlw_elment_set<sequence_void_0, 9, boost::mpl::void_ > {};
} G42CORE_METACODE_END_NAMESPACES
template struct ensure_element_at<sequence_void_0, 9, 2, boost::mpl::int_<-8> >;

#if 0 // enable and verify fails to compile
G42CORE_METACODE_BEGIN_NAMESPACES namespace detail {
template <> struct svlw_element<sequence_void_0, 7> : svlw_elment_set<sequence_void_0, 7, boost::mpl::void_ > {};
} G42CORE_METACODE_END_NAMESPACES
#endif
template struct ensure_no_element_at_but_one_prior<sequence_void_0, 7, 0>;
template struct ensure_no_element_at_but_one_prior<sequence_void_0, 10, 2>;
template struct ensure_no_element_at_but_one_prior<sequence_void_0, 11, 2>;
template struct ensure_no_element_at_but_one_prior<sequence_void_0, 12, 2>;

// Initializing via the macro should work just as well via explicit specialization of the detail type
G42CORE_MC_SVWL_INITIALIZE_AT(sequence_void_0, 14, boost::mpl::int_<-14>);
template struct ensure_element_at<sequence_void_0, 14, 3>;
template struct ensure_no_element_at_but_one_prior<sequence_void_0, 13, 2>;
template struct ensure_no_element_at_but_one_prior<sequence_void_0, 15, 3>;
G42CORE_MC_SVWL_INITIALIZE_AT(sequence_void_0, 16, boost::mpl::int_<-16>);
template struct ensure_element_at<sequence_void_0, 16, 4, boost::mpl::int_<-14>>;

// Initializing the sequence via the macro should also initialize the element at the index specified
G42CORE_MC_SVWL_INITIALIZE_SEQUENCE(sequence_void_1, 0, boost::mpl::int_<0>);
template struct ensure_element_at<sequence_void_1, 0, 0>;
template struct ensure_no_element_at_but_one_prior<sequence_void_1, 1, 0>;
template struct ensure_no_element_at_but_one_prior<sequence_void_1, 2, 0>;
G42CORE_MC_SVWL_INITIALIZE_AT(sequence_void_1, 5, boost::mpl::int_<-5>);
template struct ensure_element_at<sequence_void_1, 5, 1, boost::mpl::int_<0>>;

// Make sure an index other than 0 works when initializing the sequence
G42CORE_MC_SVWL_INITIALIZE_SEQUENCE(sequence_void_2, 2, boost::mpl::void_);
template struct ensure_no_element_at_or_before<sequence_void_2, 0>;
template struct ensure_no_element_at_or_before<sequence_void_2, 1>;
template struct ensure_element_at<sequence_void_2, 2, 0>;
template struct ensure_no_element_at_but_one_prior<sequence_void_2, 6, 0>;
