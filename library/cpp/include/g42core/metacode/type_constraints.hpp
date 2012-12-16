/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_B4A6B60C2F81410EAAC81298B88F61AD
#define G42CORE_HG_B4A6B60C2F81410EAAC81298B88F61AD

#include <type_traits>

#ifndef BOOST_MPL_ASSERT_HPP_INCLUDED
#include <boost/mpl/assert.hpp>
#endif

#ifndef G42CORE_53D3543A200E49EAA74FDA95197C8F9F
#include "namespace.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

G42CORE_METACODE_BEGIN_NAMESPACES

template <typename T>
struct ensure_not_copyable
{
    // FUTURE replace with std::is_copy_constructible, std::is_copy_assignable, 
    // std::is_move_constructible, and std::is_move_assignable when they are available for all
    // target compilers
    BOOST_MPL_ASSERT_NOT((std::has_trivial_copy_constructor<T>));
    BOOST_MPL_ASSERT_NOT((std::has_nothrow_copy_constructor<T>));
#if !defined(__ANDROID__)
    BOOST_MPL_ASSERT_NOT((std::has_trivial_assign<T>));
    BOOST_MPL_ASSERT_NOT((std::has_nothrow_assign<T>));
#endif
};

G42CORE_METACODE_END_NAMESPACES

#endif // G42CORE_HG_B4A6B60C2F81410EAAC81298B88F61AD
