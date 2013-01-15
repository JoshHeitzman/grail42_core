/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_8970E8BF17E44A67BC741E458157A037
#define G42CORE_HG_8970E8BF17E44A67BC741E458157A037

G42CORE_MC_PRAGMA_ONCE

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

template <class OutStream, template<typename> class Reporter>
class framework_thread
{
G42CORE_MC_NOT_COPYABLE(framework_thread)
public:
    framework_thread(OutStream& outStream, int argc, char* argv[]):
        outStream(outStream),
        argc(argc),
        argv(argv),
        result_(-1)
    {}

    virtual ~framework_thread() {}

    int result() const
    {
        return result_;
    }

protected:
    OutStream& outStream;
    int argc;
    char** argv;
    int result_;
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_8970E8BF17E44A67BC741E458157A037
