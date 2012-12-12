/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef MACRO_PREFIX_HG_53D3543A200E49EAA74FDA95197C8F9F
#define MACRO_PREFIX_HG_53D3543A200E49EAA74FDA95197C8F9F
#pragma warning(push)
#pragma warning(disable : 4068)
#pragma once
#pragma warning(pop)

#include "namespaces.hpp"
#include "../namespace.hpp"

#ifndef G42CORE_METACODE_NAMESPACE
#define G42CORE_METACODE_NAMESPACE metacode
#endif

#ifndef G42CORE_METACODE_BEGIN_NAMESPACES
#define G42CORE_METACODE_BEGIN_NAMESPACES G42CORE_BEGIN_NAMESPACE3(G42CORE_ROOT_NAMESPACE, G42CORE_CORE_NAMESPACE, G42CORE_METACODE_NAMESPACE)
#endif

#ifndef G42CORE_METACODE_END_NAMESPACES
#define G42CORE_METACODE_END_NAMESPACES G42CORE_END_NAMESPACE3
#endif

#ifndef	G42CORE_METACODE_NS
#define G42CORE_METACODE_NS G42CORE_NAMESPACE3(G42CORE_ROOT_NAMESPACE, G42CORE_CORE_NAMESPACE, G42CORE_METACODE_NAMESPACE)::
#endif

#endif // MACRO_PREFIX_HG_53D3543A200E49EAA74FDA95197C8F9F
