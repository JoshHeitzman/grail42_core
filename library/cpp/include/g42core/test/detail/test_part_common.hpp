/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_07B49624629D491BB307076EE3D66BC6
#define G42CORE_HG_07B49624629D491BB307076EE3D66BC6

G42CORE_MC_PRAGMA_ONCE

#include "test_part.hpp"
#include "test_part_registry.hpp"

#ifndef G42CORE_TEST_DEFAULT_TEST_REGISTRY
#define G42CORE_TEST_DEFAULT_TEST_REGISTRY G42CORE_TEST_NS detail::test_part_registry<G42CORE_TEST_NS detail::test_part_registry_policy<G42CORE_TEST_NS detail::test_part_registrar<G42CORE_TEST_NS detail::test_part_registrar_policy<const G42CORE_TEST_NS detail::test_part_base_common> > > >
#endif

#endif // G42CORE_HG_07B49624629D491BB307076EE3D66BC6
