/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_DD90B96B22A24EDA98FB3A6124ED98F7
#define G42CORE_HG_DD90B96B22A24EDA98FB3A6124ED98F7

G42CORE_MC_PRAGMA_ONCE

#ifndef G42CORE_HG_D77D32DBE31648699B84FAED892E1723
#include "verification_failure.hpp"
#endif

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

inline void if_not_report(bool exp_value, const char* filename, unsigned int line, const char* expression)
{
    if(!exp_value)
    {
        throw verification_failure(filename, line, expression);
    }
}

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#define G42CORE_TEST_DETAIL_IF_NOT_REPORT(Expression) G42CORE_TEST_NS detail::if_not_report((Expression), __FILE__, __LINE__, #Expression)

#endif // G42CORE_HG_DD90B96B22A24EDA98FB3A6124ED98F7
