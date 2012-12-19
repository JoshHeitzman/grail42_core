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
    reporter_mock() {}

    reporter_mock(reporter_mock&& rhs)
    {
        // These are copied rather than moved, as the unit test needs a valid reference to the mock
        // and we don't want to make its internal member public (or friended), so the hack goes 
        // into the mock object instead.
        // When this was created it was only needed for GCC 4.6, as VC++ 2010 and an older version
        // of GCC both generated a copy constructor (i.e. failure only occur for the Android 
        // platform with the toolchain set to 4.6).
        this->impl_ = rhs.impl_;
        this->on_tests_starting_mock_ = rhs.on_tests_starting_mock_;
        this->on_complete_message_mock_ = rhs.on_complete_message_mock_;
        this->on_tests_complete_mock_ = rhs.on_tests_complete_mock_;
    }

    MOCK_NON_CONST_METHOD_EXT( on_tests_starting, 0, void(), on_tests_starting )
    MOCK_NON_CONST_METHOD_EXT_TPL( on_complete_message, 1, void(const M1& t), on_complete_message )
    MOCK_NON_CONST_METHOD_EXT( on_tests_complete, 3, void(unsigned int, unsigned int, unsigned int), on_tests_complete )
};

#endif // G42CORE_HG_4C7B4B01648748E79C2C060510A5FEE3
