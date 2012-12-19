/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef HG_6ED6281E3B354BAE95FD2C7E72CAF8D7
#define HG_6ED6281E3B354BAE95FD2C7E72CAF8D7

#ifndef G42CORE_HG_56B1D5B02B3F4B3695F15A06AFE668B3
#include "g42core/metacode/pragmas.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

G42CORE_MC_WARNING_PUSH

G42CORE_MC_MSVC_PRAGMA(warning(disable:4389)) // 'operator' : signed/unsigned mismatch
G42CORE_MC_MSVC_PRAGMA(warning(disable:4512)) // 'class' : assignment operator could not be generated

G42CORE_MC_GCC_PRAGMA("GCC diagnostic ignored\"-Wsign-compare\"")

#include <stdio.h>

#if !defined(HWC_PLATFORM_WIN32) && !defined(HWC_PLATFORM_ANDROID) && !defined(HWC_PLATFORM_NACL)
#if defined(_WIN32) && !defined(PPAPI)
#define HWC_PLATFORM_WIN32
#elif defined(__ANDROID__)
#define HWC_PLATFORM_ANDROID
#elif defined(__native_client__) || defined(PPAPI)
#define HWC_PLATFORM_NACL
#else
#error Could not deduce target platform.
#endif
#endif // !defined(HWC_PLATFORM_WIN32) && !defined(HWC_PLATFORM_ANDROID) && !defined(HWC_PLATFORM_NACL)

#if defined(HWC_PLATFORM_WIN32)

#include <tchar.h>

#elif defined(HWC_PLATFORM_ANDROID)

#include <jni.h>
#include <android/log.h>

#elif defined(HWC_PLATFORM_NACL)

#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

#endif // HWC_PLATFORM_*

#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <map>
#include <utility>

#include <boost/static_assert.hpp>

#include <boost/preprocessor/stringize.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/assert.hpp>

#include <tut/tut_runner.hpp>
#include <tut/tut.hpp>

#include <turtle/function.hpp>
#include <turtle/mock.hpp>

G42CORE_MC_WARNING_POP

#include "g42core/metacode/type_constraints.hpp"

#endif // HG_6ED6281E3B354BAE95FD2C7E72CAF8D7