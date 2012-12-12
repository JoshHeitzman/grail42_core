/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef MACRO_PREFIX_HG_DA28A37B28C9478581C4EF3ED6FB6402
#define MACRO_PREFIX_HG_DA28A37B28C9478581C4EF3ED6FB6402
#pragma warning(push)
#pragma warning(disable : 4068)
#pragma once
#pragma warning(pop)

#define G42CORE_BEGIN_NAMESPACE1(ns1) namespace ns1 {
#define G42CORE_END_NAMESPACE1 }
#define G42CORE_NAMESPACE1(ns1) ns1

#define G42CORE_BEGIN_NAMESPACE2(ns1, ns2) namespace ns1 { namespace ns2 {
#define G42CORE_END_NAMESPACE2 }}
#define G42CORE_NAMESPACE2(ns1, ns2) ns1::ns2

#define G42CORE_BEGIN_NAMESPACE3(ns1, ns2, ns3) namespace ns1 { namespace ns2 { namespace ns3 {
#define G42CORE_END_NAMESPACE3 }}}
#define G42CORE_NAMESPACE3(ns1, ns2, ns3) ns1::ns2::ns3

#endif // MACRO_PREFIX_HG_DA28A37B28C9478581C4EF3ED6FB6402
