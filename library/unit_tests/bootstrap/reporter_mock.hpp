/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_4C7B4B01648748E79C2C060510A5FEE3
#define G42CORE_HG_4C7B4B01648748E79C2C060510A5FEE3

G42CORE_MC_PRAGMA_ONCE

template <class M1>
class reporter_mock : public mock::object
{
public:
    MOCK_NON_CONST_METHOD_EXT( on_tests_starting, 0, void(), on_tests_starting )
    MOCK_NON_CONST_METHOD_EXT_TPL( on_complete_message, 1, void(const M1& t), on_complete_message )
    MOCK_NON_CONST_METHOD_EXT( on_tests_complete, 3, void(unsigned int, unsigned int, unsigned int), on_tests_complete )
};

namespace tut
{
    struct basictest_tut_callback_to_reporter_adapter{};
    typedef test_group<basictest_tut_callback_to_reporter_adapter> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("basictest_tut_callback_to_reporter_adapter");
}

#endif // G42CORE_HG_4C7B4B01648748E79C2C060510A5FEE3
