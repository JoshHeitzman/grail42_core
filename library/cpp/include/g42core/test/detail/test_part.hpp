/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_75A911EAE43046428600CA20037AF34C
#define G42CORE_HG_75A911EAE43046428600CA20037AF34C

G42CORE_MC_PRAGMA_ONCE

#ifndef BOOST_INTEGER_TRAITS_HPP
#include <boost/integer_traits.hpp>
#endif

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

// TODO BEGIN move these to a different file
class basic_source_code_info_holder
{
public:
    basic_source_code_info_holder(const char* filename, unsigned int line):
        filename_(filename),
        line_(line)
    {}

    const char* filename() const
    {
        return filename_;
    }
    unsigned int line() const
    {
        return line_;
    }
private:
    const char* filename_;
    const unsigned int line_;
    basic_source_code_info_holder& operator=(const basic_source_code_info_holder&);
};

class logical_process_and_thread_holder
{
public:
    struct special_thread_ids
    {
        // the thread main or its equivalent is executing on
        static const int primary = boost::integer_traits<int>::const_max;
        // any thread other than the primary
        static const int nonprimary = boost::integer_traits<int>::const_max-1;
        // any thread
        static const int any = boost::integer_traits<int>::const_max-1;
    };
    struct special_process_ids
    {
        // the first process that causes other processes to start directly or indirectly; aka master process; aka oldest process
        static const int primary = boost::integer_traits<int>::const_max;
        // any process other than the primary; might not actually be a subprocess (i.e. could be started by something other than the primary process)
        static const int nonprimary = boost::integer_traits<int>::const_max-1;
        // any process
        static const int any = boost::integer_traits<int>::const_max-1;
    };
    logical_process_and_thread_holder(int threadId = special_thread_ids::any, int processId = special_process_ids::primary):
        processId(processId),
        threadId(threadId)
    {}
private:
    const int processId;
    const int threadId;
    logical_process_and_thread_holder& operator=(const logical_process_and_thread_holder&);
};

class test_part_base_common
{
G42CORE_MC_NOT_COPYABLE(test_part_base_common)
protected:
    test_part_base_common(const char* id, logical_process_and_thread_holder&& lpt, basic_source_code_info_holder&& sci):
        id(id),
        lpt(std::move(lpt)),
        sci(std::move(sci))
    {
    }

    ~test_part_base_common() {}

public:
    const char* test_id() const
    {
        return id;
    }

    const logical_process_and_thread_holder& logical_process_and_thread() const
    {
        return lpt;
    }

    const basic_source_code_info_holder& basic_source_code_info() const
    {
        return sci;
    }

    virtual void run() const = 0;

private:
    const char* id;
    const logical_process_and_thread_holder lpt;
    const basic_source_code_info_holder sci;
};
// TODO END move these to a different file

template <class Registry>
class test_part_base_policy
{
public:
    typedef Registry registry;
};

template <class Policy>
class test_part_base_with_policy : public test_part_base_common
{
G42CORE_MC_NOT_COPYABLE(test_part_base_with_policy)
protected:
    test_part_base_with_policy(const char* id, logical_process_and_thread_holder&& lpt, basic_source_code_info_holder&& sci):
        test_part_base_common(id, std::move(lpt), std::move(sci))
    {
        Policy::registry::add(this);
    }

    ~test_part_base_with_policy() {}
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_75A911EAE43046428600CA20037AF34C
