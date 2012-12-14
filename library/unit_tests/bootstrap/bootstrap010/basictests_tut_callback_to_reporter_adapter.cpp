/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "stdafx.h"

#include "g42core/test/namespace.hpp"
#include "g42core/test/detail/tut_callback_to_reporter_adapter.hpp"

template <class M1>
class mock_reporter : public mock::object
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

namespace tut
{
    template<>
    template<>
    void object::test<1>()
    {
        typedef mock_reporter<std::string> mock_reporter_std_string;
        typedef G42CORE_TEST_NS detail::tut_callback_to_reporter_adapter<mock_reporter_std_string> adapter_with_mock;

        // ensure default construction and destruction without overt errors
        {
            adapter_with_mock adapter2;
        }

        tut::test_result result0;
        std::string error_message1("error message 1");
        tut::test_result result1(std::string("group1"), 1, "test1", tut::test_result::fail, std::runtime_error(error_message1));
        std::string error_message2("error message 2");
        tut::test_result result2(std::string("group1"), 1, "test1", tut::test_result::ok, std::runtime_error(error_message2));


        // Verify that a lack of test_completed calls results in 0 passes, 0 fails, all_ok == true,
        // and that calls to on_tests_starting and on_tests_complete occur in the correct order.
        {
        mock_reporter_std_string reporter;
        adapter_with_mock adapter(std::move(reporter));
        mock::sequence s;
        MOCK_EXPECT( reporter.on_tests_starting ).once().in(s);
        MOCK_EXPECT( reporter.on_complete_message ).never();
        MOCK_EXPECT( reporter.on_tests_complete ).once().with(0, 0, 0).in(s);
        adapter.run_started();
        adapter.run_completed();
        ensure(mock::verify());
        ensure(adapter.all_ok());
        }

        // Verify that group_started and group_completed don't call through to to reporter or 
        // impact the result of all_ok, or cause passed or failed tests to be reported.
        {
        mock_reporter_std_string reporter;
        adapter_with_mock adapter(std::move(reporter));
        MOCK_EXPECT( reporter.on_tests_starting ).never();
        MOCK_EXPECT( reporter.on_complete_message ).never();
        MOCK_EXPECT( reporter.on_tests_complete ).never();
        adapter.group_started(std::string());
        adapter.group_completed(std::string());
        ensure(mock::verify());
        ensure(adapter.all_ok());
        mock::reset();

        MOCK_EXPECT( reporter.on_complete_message ).once().with(error_message1.c_str());
        MOCK_EXPECT( reporter.on_tests_complete ).once().with(0, 1, 0);
        adapter.test_completed(result1);
        ensure(!adapter.all_ok());
        adapter.group_started(std::string());
        adapter.group_completed(std::string());
        adapter.run_completed();
        ensure(mock::verify());
        ensure(!adapter.all_ok());
        }

        // Verify that ok status don't result in on_complete_message being called, all_ok == true,
        // and the correct number of passed tests is reported.
        {
        mock_reporter_std_string reporter;
        adapter_with_mock adapter(std::move(reporter));

        MOCK_EXPECT( reporter.on_tests_starting ).once();
        MOCK_EXPECT( reporter.on_complete_message ).never();
        MOCK_EXPECT( reporter.on_tests_complete ).once().with(2, 0, 0);
        adapter.run_started();
        adapter.test_completed(result0);
        adapter.test_completed(result2);
        adapter.run_completed();
        ensure(mock::verify());
        ensure(adapter.all_ok());
        }

        // Verify that a fail status result in on_complete_message being called, all_ok == false,
        // and the correct number of passed and failed tests being reported.
        {
        mock_reporter_std_string reporter;
        adapter_with_mock adapter(std::move(reporter));

        MOCK_EXPECT( reporter.on_tests_starting ).once();
        MOCK_EXPECT( reporter.on_complete_message ).once().with(error_message1.c_str());
        MOCK_EXPECT( reporter.on_tests_complete ).once().with(1, 1, 0);
        adapter.run_started();
        adapter.test_completed(result0);
        adapter.test_completed(result1);
        adapter.run_completed();
        ensure(mock::verify());
        ensure(!adapter.all_ok());
        }

        // Verify that all remaining status codes are treated as failures
        {
        mock_reporter_std_string reporter;
        adapter_with_mock adapter(std::move(reporter));
        MOCK_EXPECT( reporter.on_tests_starting ).once();
        MOCK_EXPECT( reporter.on_complete_message ).exactly(6);
        MOCK_EXPECT( reporter.on_tests_complete ).once().with(0, 6, 0);
        adapter.run_started();
        std::string error_message3("error message 3");
        tut::test_result result3(std::string("group1"), 1, "test1", tut::test_result::ok, std::runtime_error(error_message3));
        result3.result = tut::test_result::ex;
        adapter.test_completed(result3);
        result3.result = tut::test_result::warn;
        adapter.test_completed(result3);
        result3.result = tut::test_result::term;
        adapter.test_completed(result3);
        result3.result = tut::test_result::ex_ctor;
        adapter.test_completed(result3);
        result3.result = tut::test_result::rethrown;
        adapter.test_completed(result3);
        result3.result = tut::test_result::dummy;
        adapter.test_completed(result3);
        adapter.run_completed();
        ensure(mock::verify());
        ensure(adapter.all_ok());
        }
    }
}