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

#ifndef G42CORE_HG_8970E8BF17E44A67BC741E458157A037
#include "framework_thread.hpp"
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
    template <typename Reporter>
    static int run(Reporter&& reporter, int argc, char* argv[])
    {
        Output<Reporter> output(std::move(reporter));
        CommandLineTestRunner runner(argc, const_cast<const char**>(argv), &output);
        return runner.runAllTestsMain();
    }
};

struct cpputest_append_note
{
    template <class OutStream>
    static void append_to_stream(OutStream& outStream)
    {
        outStream << "(via CppUTest)";
    }
};

#define G42CORE_TEST_CPPUTEST_RUN_TESTS(Reporter, Argc, Argv) G42CORE_TEST_NS detail::cpputest_main<>::run<>(Reporter, Argc, Argv)

template <class OutStream, template<typename> class Reporter>
class cpputest_thread : public framework_thread<OutStream, Reporter>
{
G42CORE_MC_NOT_COPYABLE(cpputest_thread)
public:
    typedef cpputest_thread<OutStream, Reporter> type;
    typedef reporter_outstream_policies<OutStream, reporter_outstream_formatter_char<reporter_outstream_formatter_header_char<cpputest_append_note> > > reporter_policy;
    typedef Reporter<reporter_policy> reporter_with_policy;
    cpputest_thread(OutStream& outStream, int argc, char* argv[]):
        framework_thread<OutStream, Reporter>(outStream, argc, argv)
    {}

    static void* thread_func(void* p)
    {
        type* this_ = reinterpret_cast<type*>(p);
        this_->result_ = G42CORE_TEST_CPPUTEST_RUN_TESTS(reporter_with_policy(this_->outStream), this_->argc, this_->argv);
        return NULL;
    }

    // REVIEW included in prototype.  Still needed?
    static const std::string& identifier()
    {
        static const std::string id("cpputest");
        return id;
    }
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_A0C6177CD91C4C04AA76C8D5E62F7BF4
