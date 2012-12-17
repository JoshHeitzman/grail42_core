/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_1A3225450B2B4C4D98A955B5DA88EDDC
#define G42CORE_HG_1A3225450B2B4C4D98A955B5DA88EDDC

G42CORE_MC_PRAGMA_ONCE

G42CORE_METACODE_BEGIN_NAMESPACES

namespace detail
{

#if !defined(__GNUC__) || !defined(G42CORE_MC_SVWL_GCC_ANON_NS_WARN_WORKAROUND)

template <class container_identifier, int vector_index_, bool is_set_, template<class, int> class previous_vector_element_type>
struct svlw_elment_common
{
public:
    static const int vector_index = vector_index_;
    typedef boost::mpl::bool_<is_set_> is_set;
    typedef previous_vector_element_type<container_identifier, vector_index - 1> previous_vector_element;
    typedef typename boost::mpl::if_<
        typename previous_vector_element::is_set,
        previous_vector_element,
        typename previous_vector_element::previous_list_element
    >::type previous_list_element;
    typedef previous_list_element prior;
    static const int list_index = boost::mpl::if_<is_set,
        boost::mpl::int_<previous_list_element::list_index>,
        boost::mpl::int_<-2> >::type::value + 1;
};

template <class container_identifier, int vector_index>
struct svlw_element : svlw_elment_common<container_identifier, vector_index, false, svlw_element>
{
};

template <class container_identifier, int vector_index, class type_>
struct svlw_elment_set : svlw_elment_common<container_identifier, vector_index, true, svlw_element>
{
    typedef type_ type;
};

#define G42CORE_MC_DETAIL_SVWL_INITIALIZE_AT(unique_name, vector_index, type_) \
G42CORE_METACODE_BEGIN_NAMESPACES namespace detail { \
template <> struct svlw_element<unique_name, vector_index> : \
    svlw_elment_set<unique_name, vector_index, type_> {}; \
} G42CORE_METACODE_END_NAMESPACES

#else // !defined(__GNUC__) || !defined(G42CORE_MC_SVWL_GCC_ANON_NS_WARN_WORKAROUND)

// This is a workaround to a gcc warning that can not be selectively disabled:
//   warning : 'g42::core::metacode::detail::svlw_element<g42::core::metacode::sparse_vector_with_list<g42::core::test::detail::tut_test_objects_for_svl, 0>, 18>' has a base 'g42::core::metacode::detail::svlw_elment_set<g42::core::metacode::sparse_vector_with_list<g42::core::test::detail::tut_test_objects_for_svl, 0>, 18, tut::test_object<<unnamed>::g42_tut_test_group_identifier16> >' whose type uses the anonymous namespace
template <class container_identifier, int vector_index_>
struct svlw_element
{
    static const int vector_index = vector_index_;
    typedef boost::mpl::bool_<false> is_set;
    typedef svlw_element<container_identifier, vector_index - 1> previous_vector_element;
    typedef typename boost::mpl::if_<
        typename previous_vector_element::is_set,
        previous_vector_element,
        typename previous_vector_element::previous_list_element
    >::type previous_list_element;
    typedef previous_list_element prior;
    static const int list_index = boost::mpl::if_<is_set,
        boost::mpl::int_<previous_list_element::list_index>,
        boost::mpl::int_<-2> >::type::value + 1;
};

#define G42CORE_MC_DETAIL_SVWL_INITIALIZE_AT(container_identifier, vector_index_, type_) \
G42CORE_METACODE_BEGIN_NAMESPACES namespace detail { \
template <> struct svlw_element<container_identifier, vector_index_> \
{ \
    static const int vector_index = vector_index_; \
    typedef boost::mpl::bool_<true> is_set; \
    typedef svlw_element<container_identifier, vector_index - 1> previous_vector_element; \
    typedef boost::mpl::if_< \
        previous_vector_element::is_set, \
        previous_vector_element, \
        previous_vector_element::previous_list_element \
    >::type previous_list_element; \
    typedef previous_list_element prior; \
    static const int list_index = boost::mpl::if_<is_set, \
        boost::mpl::int_<previous_list_element::list_index>, \
        boost::mpl::int_<-2> >::type::value + 1; \
    typedef type_ type; \
}; \
} G42CORE_METACODE_END_NAMESPACES

#endif // !defined(__GNUC__) || !defined(G42CORE_MC_SVWL_GCC_ANON_NS_WARN_WORKAROUND)

template <class container_identifier>
struct svlw_element<container_identifier, -1>
{
    static const int vector_index = -1;
    typedef boost::mpl::bool_<false> is_set;
    typedef svlw_element<container_identifier, vector_index> previous_vector_element;
    typedef previous_vector_element previous_list_element;
    static const int list_index = -1;
};


// This was included in the prototype but not actually used, see lengthy comment about at_impl 
// in the main file.
#if 0
struct sparse_vector_list_vector_tag {};
#endif
} // namespace detail

G42CORE_METACODE_END_NAMESPACES


#endif // G42CORE_HG_1A3225450B2B4C4D98A955B5DA88EDDC
