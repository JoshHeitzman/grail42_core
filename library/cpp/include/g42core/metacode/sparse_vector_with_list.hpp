/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_E42C88FF6CA64B4686A2C6CC0B85DE31
#define G42CORE_HG_E42C88FF6CA64B4686A2C6CC0B85DE31

// TODO create xhtml documentation for this, possibly by using doc comments and generating
// documentation via the MSVC compiler.

#ifndef BOOST_MPL_IF_HPP_INCLUDED
#include <boost/mpl/if.hpp>
#endif
#ifndef BOOST_MPL_AT_HPP_INCLUDED
#include <boost/mpl/at.hpp>
#endif
#ifndef BOOST_MPL_IDENTITY_HPP_INCLUDED
#include <boost/mpl/identity.hpp>
#endif

#ifndef G42CORE_HG_53D3543A200E49EAA74FDA95197C8F9F
#include "namespace.hpp"
#endif

// The header guard check omitted as this should be the one and only inclusion of this file
#include "detail/detail_sparse_vector_with_list.hpp"

G42CORE_MC_PRAGMA_ONCE

G42CORE_METACODE_BEGIN_NAMESPACES

// The purpose of sparse_vector_with_list is to provide a means for a C++ metaprogramming 
// expression to reference state from the previous expression without having to be
// explicitly provided the result of the previous expression.  In particular the original
// motivation for this was to be able to utilize the combination of the C preprocessor 
// builtin __LINE__ macro and a sparse_vector_with_list sequence create an implicitly built
// stack.  For example line numbers can be thought of as indexes into a sparse vector and 
// lines with metaprogramming expression can be thought of indexes into a list that tracks
// the nonsparse elements of the sparse vector.
//
// The terms vector view index and list view index are used in reference to two aspects of 
// sparse_vector_with_list, and much of the API relates to mapping from a a vector view index
// to a list view index.

template <class Identifier, int FirstVectorIndex>
struct sparse_vector_with_list
{
    typedef sparse_vector_with_list<Identifier, FirstVectorIndex> this_;

    // Evaluates to true_ if the element at the vector view index has been set already, and false_
    // otherwise.  Has the side effect of fixing the unset element and lower unset elements as 
    // unset such that a subsequent attempt to set the elements will result in a compile error.
    template <int VectorIndex>
    struct is_set_at : // REVIEW rename is_set_at_vector or vector_is_set_at?
        G42CORE_METACODE_NS detail::svlw_element<this_, VectorIndex>::is_set {};

    // Evaluates to int_<-1> if the element at the vector view index has not been set, otherwise 
    // evaluates to int_<list_index>.  Has the side effect of fixing the unset element and lower 
    // unset elements as unset such that a subsequent attempt to set the elements will result in 
    // a compile error.
    template <int VectorIndex>
    struct vector_to_list_index :
        boost::mpl::int_<G42CORE_METACODE_NS detail::svlw_element<this_, VectorIndex>::list_index> {};

    // Evaluates to int_<-1> if there are no elements set below the element at the vector view 
    // index, otherwise evalutates to int_<list_index> for the elment with the greatest list view 
    // index whose vector view index is less then the VectorIndex argument.  Has the side effect 
    // of fixing the unset element and lower unset elements as unset such that a subsequent attempt 
    // to set the elements will result in a compile error.
    template <int VectorIndex>
    struct vector_to_prev_list_index :
        boost::mpl::int_<G42CORE_METACODE_NS detail::svlw_element<this_, VectorIndex>::prior::list_index> {};

    // As vector_to_prev_list_index but provides the actual type of the element instead of its 
    // list view index.
    template <int VectorIndex>
    struct vector_to_prev_list_element :
        G42CORE_METACODE_NS detail::svlw_element<this_, VectorIndex>::prior {};

// These were included in the prototype but not actually used, see lengthy comment about at_impl 
// below
#if 0
    typedef this_ type;

    template <int vector_index>
    struct to_type :
            boost::mpl::identity<G42CORE_METACODE_NS detail::svlw_element<this_, vector_index> > {};
    struct as_list {
        typedef detail::svlw_element<this_, first_vector_index> begin;
    };

    struct as_vector {
        typedef this_ container_identifier;
        typedef detail::sparse_vector_list_vector_tag tag;
        typedef detail::svlw_element<this_, first_vector_index> begin;

        // Convienence Metafunctions
        template <int Index>
        struct at : 
            boost::mpl::at<typename this_::as_vector, boost::mpl::int_<Index> >::type {};
    };
#endif

};

G42CORE_METACODE_END_NAMESPACES

// REVIEW If the design were changed such that all elements had a default type attribute then 
// boost::mpl:at could be supported for the vector view.  Currently, this functionality isn't actually 
// needed and omitting the defaulted value reduces compile time overhead, so this is not supported.  While a
// begin metafunction can be provided forward iterating also is problematic due to the side effect that 
// accessing an an unset element prevents it from being set.  An end metafunction isn't feasible either, as 
// the end of the list can only be found by querying with vector index greater than the vector index of the 
// element at the end of the list, so it will also have a side effect in addition to requiring the caller to 
// specify a appropriate vector index.  So may never make sense to provide an API compatiable with MPL 
// sequences directly for sparse_vector_with_list.  That said it is probably feasible to create an adapter
// for which such an API can be created, as the adapter could keep track of the last set and unset elements.
// Such an adapter would require that each modification would result in a new type the caller would need to
// keep track of and avoiding that is actually the point of sparse_vector_with_list.
#if 0
namespace boost { namespace mpl {
template <> struct at_impl<
    G42CORE_METACODE_NS detail::sparse_vector_list_vector_tag >
{
    template< typename Sequence, typename N > struct apply :
        G42CORE_METACODE_NS detail::svlw_element<
            typename Sequence::container_identifier, N::value>::type
    {};
};
}}
#endif

#if !defined(__GNUC__) || !defined(G42CORE_MC_SVWL_GCC_ANON_NS_WARN_WORKAROUND)
#define G42CORE_MC_SVWL_INITIALIZE_AT(unique_name, vector_index, type_) \
    G42CORE_MC_DETAIL_SVWL_INITIALIZE_AT(unique_name, vector_index, type_)
#else
// For gcc replicating the above results in an error that appears to be related to when 
// BOOST_PP_COMMA is expanded.  There is may be a portable fix to that issue, but the this is
// already a workaround another another gcc specific issue, so stop recursing here.
#define G42CORE_MC_SVWL_INITIALIZE_AT G42CORE_MC_DETAIL_SVWL_INITIALIZE_AT
#endif

#define G42CORE_MC_SVWL_INITIALIZE_SEQUENCE(unique_name, vector_index, type_) \
struct unique_name ## _ {}; \
typedef G42CORE_METACODE_NS sparse_vector_with_list<unique_name ## _, vector_index> unique_name; \
G42CORE_MC_SVWL_INITIALIZE_AT(unique_name, vector_index, type_)

#endif // G42CORE_HG_E42C88FF6CA64B4686A2C6CC0B85DE31
