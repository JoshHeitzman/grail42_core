/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_8970E8BF17E44A67BC741E458157A037
#define G42CORE_HG_8970E8BF17E44A67BC741E458157A037

#ifndef G42CORE_HG_56B1D5B02B3F4B3695F15A06AFE668B3
#include "../metacode/pragmas.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

#ifndef G42CORE_HG_977EE3D68FC449FDB779CEF0955C0194
#include "../metacode/classes.hpp"
#endif
#ifndef G42CORE_HG_A276488FB6B8426896EB6C3CCB2150EA
#include "namespace.hpp"
#endif

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

template <class OutStream>
class framework_thread_base
{
G42CORE_MC_NOT_COPYABLE(framework_thread_base)
public:
    framework_thread_base(OutStream& outStream):
        outStream(outStream),
        result_(result_unknown)
    {}

    typedef std::exception result_is_unknown; // TODO better exception

    int result() const
    {
        if(result_ == result_unknown)
        {
            throw result_is_unknown();
        }
        return result_;
    }

    static const int result_unknown = -1;
    static const int result_passed = 0;
    static const int result_failed = 1;

protected:
    ~framework_thread_base() {}

    OutStream& outStream;
    int result_;
};

// TODO remove Reporter parameter
template <class OutStream, template<typename> class Reporter>
class framework_thread : public framework_thread_base<OutStream>
{
G42CORE_MC_NOT_COPYABLE(framework_thread)
public:
    framework_thread(OutStream& outStream, int argc, char* argv[]):
        framework_thread_base<OutStream>(outStream),
        argc(argc),
        argv(argv)
    {}

protected:
    ~framework_thread() {}

    int argc;
    char** argv;
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_8970E8BF17E44A67BC741E458157A037
