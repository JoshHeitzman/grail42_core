/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_05CD3AFAF8B945B189E6C8E5E3133D27
#define G42CORE_HG_05CD3AFAF8B945B189E6C8E5E3133D27

#ifndef G42CORE_HG_977EE3D68FC449FDB779CEF0955C0194
#include "../metacode/classes.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#include <atomic>
#elif __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)
#include <stdatomic.h> // http://gcc.gnu.org/wiki/Atomic
#define G42CORE_CONCURRENCY_ATOMIC_REQUIRED
#else
#include <boost/atomic.hpp>
#endif

#ifndef G42CORE_HG_574A1DB99FFF499C9564FFD8855DBD94
#include "namespace.hpp"
#endif

G42CORE_CONCURRENCY_BEGIN_NAMESPACES

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)
using std::atomic;
#else
using boost::atomic;
#endif

G42CORE_CONCURRENCY_END_NAMESPACES

#endif // G42CORE_HG_05CD3AFAF8B945B189E6C8E5E3133D27
