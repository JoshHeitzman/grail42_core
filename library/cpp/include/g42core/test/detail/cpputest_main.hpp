/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_A0C6177CD91C4C04AA76C8D5E62F7BF4
#define G42CORE_HG_A0C6177CD91C4C04AA76C8D5E62F7BF4

G42CORE_MC_PRAGMA_ONCE

#ifndef G42CORE_HG_BF13623FF71347EBA031ED83ADDA8ACE
#include "cpputest_output_to_reporter_adapter.hpp"
#endif

G42CORE_MC_WARNING_PUSH
G42CORE_MC_MSVC_PRAGMA(warning(disable:4512)) // 'TestResult' : assignment operator could not be generated
#undef CHECK
#undef CHECK_EQUAL
#undef RUN_ALL_TESTS
#define CPPUTEST_MEM_LEAK_DETECTION_DISABLED
#include <CppUTest/CommandLineTestRunner.h>
#undef CHECK
#undef CHECK_EQUAL
#undef RUN_ALL_TESTS
G42CORE_MC_WARNING_POP

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

template <template<typename> class Output = G42CORE_TEST_NS detail::cpputest_reporter_adapter>
struct cpputest_main
{
    // REVIEW included in prototype.  Still needed?
	static const std::string& identifier()
	{
		static const std::string id("cpputest");
		return id;
	}

	template <class OutStream>
	static void append_to_stream(OutStream& stream)
	{
		stream << "(via CppUTest)";
	}

    template <typename Reporter>
	static int run(Reporter&& reporter, int argc, char* argv[])
	{
        Output<Reporter> output(std::move(reporter));
		CommandLineTestRunner runner(argc, const_cast<const char**>(argv), &output);
		return runner.runAllTestsMain();
	}
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#define G42CORE_TEST_CPPUTEST_RUN_TESTS(Reporter, Argc, Argv) G42CORE_TEST_NS detail::cpputest_main<>::run<>(Reporter, Argc, Argv)

#endif // G42CORE_HG_A0C6177CD91C4C04AA76C8D5E62F7BF4
