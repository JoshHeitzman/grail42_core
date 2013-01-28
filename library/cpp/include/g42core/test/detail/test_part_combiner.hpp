/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_793BBB264C13407490A6832B9CC390E9
#define G42CORE_HG_793BBB264C13407490A6832B9CC390E9

G42CORE_MC_PRAGMA_ONCE

#include <map>

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail {

// TODO remove need for &(*(...)) via use of type_traits
//
// REVIEW is RVO and move construction actually occuring such the containers isn't copied (i.e. 
// should return value be an out param)?
//
struct test_parts_combiner
{
    template <class Range>
    static auto combine(const Range& range) -> std::map<decltype((*(range.begin()))->test_id()), std::list<decltype(&(*(*(range.begin()))))> >
    {
        typedef std::map<decltype((*(range.begin()))->test_id()), std::list<decltype(&(*(*(range.begin()))))> > id_to_list_map;
        id_to_list_map id_to_list;
        for(auto i = range.begin(); i != range.end(); ++i)
        {
            auto p = &(*(*i));
            auto found = id_to_list.find(p->test_id());
            if(found != id_to_list.end())
            {
                (*found).second.push_back(p);
            }
            else
            {
                id_to_list.insert(typename id_to_list_map::value_type(p->test_id(), typename id_to_list_map::mapped_type()));
                id_to_list[p->test_id()].push_back(p);
            }
        }
        return id_to_list;
    }

};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_793BBB264C13407490A6832B9CC390E9
