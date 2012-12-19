/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_9BAC0A6A9CAB43D2AAC38B5DBBB60F08
#define G42CORE_HG_9BAC0A6A9CAB43D2AAC38B5DBBB60F08

#if defined(__GNUC__)

#define G42CORE_MC_PRAGMA_ONCE _Pragma("once")
#define G42CORE_MC_GCC_PRAGMA(p) _Pragma(p)

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#define G42CORE_MC_WARNING_PUSH G42CORE_MC_GCC_PRAGMA("GCC diagnostic push")
#define G42CORE_MC_WARNING_POP G42CORE_MC_GCC_PRAGMA("GCC diagnostic pop")
#else // __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 6)
#define G42CORE_MC_WARNING_PUSH
#define G42CORE_MC_WARNING_POP
#endif // __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 6)

#else // defined(__GNUC__)

#if !defined(G42CORE_MC_PRAGMA_ONCE) || !defined(G42CORE_MC_WARNING_PUSH) || !defined(G42CORE_MC_WARNING_POP)
#error G42CORE_MC_PRAGMA_ONCE, G42CORE_MC_WARNING_PUSH, and G42CORE_MC_WARNING_POP must be defined prior to the inclusion of pragmas_gcc.hpp
#endif

#define G42CORE_MC_GCC_PRAGMA(p)

#endif // defined(__GNUC__)

G42CORE_MC_PRAGMA_ONCE

#endif // G42CORE_HG_9BAC0A6A9CAB43D2AAC38B5DBBB60F08
