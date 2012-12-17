/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#include "stdafx.h"

#include "g42core/metacode/classes.hpp"
#include "g42core/test/namespace.hpp"
#include "g42core/test/detail/reporter_outstream.hpp"

namespace tut
{
    struct basictests_reporter_outstream{};
    typedef test_group<basictests_reporter_outstream> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("basictests_reporter_outstream");
}

typedef G42CORE_TEST_NS detail::reporter_outstream<G42CORE_TEST_NS detail::reporter_outstream_policies<std::ostream> > reporter_with_ostream;

namespace tut
{
    template<>
    template<>
    void object::test<1>()
    {
        typedef G42CORE_METACODE_NS ensure_not_copyable<reporter_with_ostream> ensure_not_copyable;
        {
        std::string expected_header_content("*** Tests started  ***\n");
        std::stringstream ss;
        // Basic test of on_tests_starting
        reporter_with_ostream reporter(ss);
        reporter.on_tests_starting();
        auto contents = ss.str();
        ensure(contents == expected_header_content);
        ss.str(std::string());
        // All three should be included in the content even when 0
        reporter.on_tests_complete(0, 0, 0);
        contents = ss.str();
        ensure(contents == "*** Tests complete: 0 passed, 0 failed, 0 skipped ***\n");
        ss.str(std::string());
        // message should work with literal char string
        reporter.on_complete_message("");
        contents = ss.str();
        ensure(contents == "\n");
        ss.str(std::string());
        // ditto for message_part
        reporter.message_part("");
        contents = ss.str();
        ensure(contents == "");
        ss.str(std::string());
        // message should also work with std::string
        reporter.on_complete_message(std::string("message 2"));
        contents = ss.str();
        ensure(contents == "message 2\n");
        ss.str(std::string());
        // ditto for message_part
        reporter.message_part(std::string("message B"));
        contents = ss.str();
        ensure(contents == "message B");
        ss.str(std::string());
        // Should be able to invoke on_tests_starting again and get the same content
        reporter.on_tests_starting();
        contents = ss.str();
        ensure(contents == expected_header_content);
        ss.str(std::string());
        // Now test that again with numbers other than zero including a multidigit numbers.
        reporter.on_tests_complete(1, 12, 1000);
        contents = ss.str();
        ensure(contents == "*** Tests complete: 1 passed, 12 failed, 1000 skipped ***\n");
        ss.str(std::string());
        }
    }
}

#include "g42core/metacode/classes.hpp"
#include "g42core/test/namespace.hpp"
// Although the contents are not executed, this is included so that it will be parsed as early as
// as possible in the build order.
#include "g42core/test/detail/tut_main.hpp"

namespace {
void not_called()
{
    std::stringstream ss;
    G42CORE_TEST_TUT_RUN_TESTS(reporter_with_ostream(ss), 0, nullptr);
}
}
