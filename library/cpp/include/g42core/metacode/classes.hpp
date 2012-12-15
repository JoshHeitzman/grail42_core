/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_977EE3D68FC449FDB779CEF0955C0194
#define G42CORE_HG_977EE3D68FC449FDB779CEF0955C0194
#pragma warning(push)
#pragma warning(disable : 4068)
#pragma once
#pragma warning(pop)

#define G42CORE_MC_NOT_COPYABLE(Typename) \
private: \
    Typename(const Typename&); \
    Typename& operator=(const Typename&);

#endif // G42CORE_HG_977EE3D68FC449FDB779CEF0955C0194
