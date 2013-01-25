/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_7BC3322891C04BA2BF239B77475FA2AE
#define G42CORE_HG_7BC3322891C04BA2BF239B77475FA2AE

G42CORE_MC_PRAGMA_ONCE

#if !defined(G42CORE_TEST_DEFAULT_TEST_REGISTRY) && !defined(G42CORE_TEST_DEFAULT_TEST_PART_POLICY)
#error Either G42CORE_TEST_DEFAULT_TEST_REGISTRY or G42CORE_TEST_DEFAULT_TEST_PART_POLICY must be defined prior to including registration.hpp
#endif


#if !defined(G42CORE_TEST_DEFAULT_TEST_PART_POLICY) && defined(G42CORE_TEST_DEFAULT_TEST_REGISTRY)
#define G42CORE_TEST_DEFAULT_TEST_PART_POLICY G42CORE_TEST_NS detail::test_part_base_policy<G42CORE_TEST_DEFAULT_TEST_REGISTRY>
#endif

#define G42CORE_TEST_DETAIL_BEGIN_GROUP() namespace {

#define G42CORE_TEST_DETAIL_END_GROUP() }

#define G42CORE_TEST_DETAIL_DEFINE_TEST() \
class BOOST_PP_CAT(test_, __LINE__) : public G42CORE_TEST_NS detail::test_part_base_with_policy<G42CORE_TEST_DEFAULT_TEST_PART_POLICY> \
{ \
public: \
    BOOST_PP_CAT(test_, __LINE__)(): \
        G42CORE_TEST_NS detail::test_part_base_with_policy<G42CORE_TEST_DEFAULT_TEST_PART_POLICY>( \
            typeid(BOOST_PP_CAT(test_, __LINE__)).name(), \
            G42CORE_TEST_NS detail::logical_process_and_thread_holder(G42CORE_TEST_NS detail::logical_process_and_thread_holder::special_thread_ids::primary), \
            G42CORE_TEST_NS detail::basic_source_code_info_holder(__FILE__, __LINE__)) \
    {} \
    virtual void run() const; \
} BOOST_PP_CAT(instance_, __LINE__); \
void BOOST_PP_CAT(test_, __LINE__)::run() const

#endif // G42CORE_HG_7BC3322891C04BA2BF239B77475FA2AE
