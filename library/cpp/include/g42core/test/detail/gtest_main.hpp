/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_B8737564E8B04D229051777FB21AD7BF
#define G42CORE_HG_B8737564E8B04D229051777FB21AD7BF

G42CORE_MC_PRAGMA_ONCE

#ifndef G42CORE_HG_1549DB5609BD466882EF863F21ADE601
#include "gtest_listener_to_reporter_adapter.hpp"
#endif

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

template <template<typename> class Listener = G42CORE_TEST_NS detail::gtest_listener_to_reporter_adapter>
struct gtest_main
{
    // REVIEW included in prototype.  Still needed?
    static const std::string& identifier()
    {
        static const std::string id("gtest");
        return id;
    }

    template <class OutStream>
    static void append_to_stream(OutStream& stream)
    {
        stream << "(via Google Test)";
    }

    template <typename Reporter>
    static int run(Reporter&& reporter, int argc, char* argv[])
    {
        ::testing::InitGoogleTest(&argc, argv);
        delete ::testing::UnitTest::GetInstance()->listeners().Release(::testing::UnitTest::GetInstance()->listeners().default_result_printer());

        auto p = new Listener<Reporter>(std::move(reporter));
        ::testing::UnitTest::GetInstance()->listeners().Append(p);
        return (::testing::UnitTest::GetInstance()->Run());
    }
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#define G42CORE_TEST_GTEST_RUN_TESTS(Reporter, Argc, Argv) G42CORE_TEST_NS detail::gtest_main<>::run<>(Reporter, Argc, Argv)

#endif // G42CORE_HG_B8737564E8B04D229051777FB21AD7BF
