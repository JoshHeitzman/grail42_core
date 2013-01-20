/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_D05BDCC8B8D74E43A9DEF963F4BDD1B5
#define G42CORE_HG_D05BDCC8B8D74E43A9DEF963F4BDD1B5

G42CORE_MC_PRAGMA_ONCE

#ifndef G42CORE_HG_05CD3AFAF8B945B189E6C8E5E3133D27
#include "../../concurrency/atomic.hpp"
#endif

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

class test_part_registrar
{
G42CORE_MC_NOT_COPYABLE(test_part_registrar)
public:
    test_part_registrar():
        registrationOpen(true)
    {}
private:
    G42CORE_CONCURRENCY_NS atomic<bool> registrationOpen;
};

struct test_part_registry
{
    static void add(const G42CORE_TEST_NS detail::test_part_base_common&)
    {
    }
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_D05BDCC8B8D74E43A9DEF963F4BDD1B5
