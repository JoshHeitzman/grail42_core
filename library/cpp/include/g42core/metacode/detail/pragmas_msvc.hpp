/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_74FF227A606D42A994740B2A4B7438A6
#define G42CORE_HG_74FF227A606D42A994740B2A4B7438A6

#if defined(_MSC_VER)
#define G42CORE_MC_PRAGMA_ONCE __pragma(once)
#define G42CORE_MC_WARNING_PUSH __pragma(warning(push))
#define G42CORE_MC_WARNING_POP __pragma(warning(pop))
#define G42CORE_MC_MSVC_WARNING_DISABLE_4512 __pragma(warning(disable:4512))
#define G42CORE_MC_MSVC_WARNING_DISABLE_4389 __pragma(warning(disable:4389))
// assignment operator could not be generated
#else
#define G42CORE_MC_MSVC_WARNING_DISABLE_4512
#define G42CORE_MC_MSVC_WARNING_DISABLE_4389
#endif // defined(_MSC_VER)

G42CORE_MC_PRAGMA_ONCE

#endif // G42CORE_HG_74FF227A606D42A994740B2A4B7438A6
