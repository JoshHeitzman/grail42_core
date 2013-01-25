#include "g42core/test/detail/test_part_registry.hpp"

typedef G42CORE_TEST_NS detail::test_part_registrar_policy<int> mock_registrar_policy;
typedef G42CORE_TEST_NS detail::test_part_registrar<mock_registrar_policy> mocked_registrar;

extern G42CORE_CONCURRENCY_NS atomic<int> shared_index;

inline void test_func()
{
    // Although the value isn't used, execute to try to create a race condition on initialization
    mocked_registrar::get();

    const int minCount = 10;
    while(shared_index.load() <= minCount);
    auto range = mocked_registrar::get().range();
    auto count = boost::distance(range);
    VERIFY(count >= minCount);
}