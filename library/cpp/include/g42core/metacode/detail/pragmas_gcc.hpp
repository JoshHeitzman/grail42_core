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
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#define G42CORE_MC_WARNING_PUSH _Pragma("GCC diagnostic push")
#define G42CORE_MC_WARNING_POP _Pragma("GCC diagnostic pop")
#else // __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 6)
#define G42CORE_MC_WARNING_PUSH
#define G42CORE_MC_WARNING_POP
#endif // __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 6)
#define G42CORE_MC_GCC_DISABLE_ALL_WARNINGS_IN_INCLUDE_FILE _Pragma("GCC system_header")
#define G42CORE_MC_GCC_DISABLE_WARNING_SIGN_COMPARE _Pragma("GCC diagnostic ignored\"-Wsign-compare\"")
#else // defined(__GNUC__)
#define G42CORE_MC_GCC_DISABLE_ALL_WARNINGS_IN_INCLUDE_FILE
#define G42CORE_MC_GCC_DISABLE_WARNING_SIGN_COMPARE
#endif // defined(__GNUC__)

G42CORE_MC_PRAGMA_ONCE

#endif // G42CORE_HG_9BAC0A6A9CAB43D2AAC38B5DBBB60F08
