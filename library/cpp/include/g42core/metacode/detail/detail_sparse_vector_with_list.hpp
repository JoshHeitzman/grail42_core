/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_1A3225450B2B4C4D98A955B5DA88EDDC
#define G42CORE_HG_1A3225450B2B4C4D98A955B5DA88EDDC
#pragma warning(push)
#pragma warning(disable : 4068)
#pragma once
#pragma warning(pop)

G42CORE_METACODE_BEGIN_NAMESPACES

namespace detail
{

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

template <class container_identifier>
struct svlw_element<container_identifier, -1>
{
    static const int vector_index = -1;
    typedef boost::mpl::bool_<false> is_set;
    typedef svlw_element<container_identifier, vector_index> previous_vector_element;
    typedef previous_vector_element previous_list_element;
    static const int list_index = -1;
};

template <class container_identifier, int vector_index, class type_>
struct svlw_elment_set : svlw_elment_common<container_identifier, vector_index, true, svlw_element>
{
    typedef type_ type;
};

// This was included in the prototype but not actually used, see lengthy comment about at_impl 
// in the main file.
#if 0
struct sparse_vector_list_vector_tag {};
#endif
} // namespace detail

G42CORE_METACODE_END_NAMESPACES

#endif // G42CORE_HG_1A3225450B2B4C4D98A955B5DA88EDDC
