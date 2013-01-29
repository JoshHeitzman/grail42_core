#include "g42core/test/detail/test_part_registry.hpp"

typedef G42CORE_TEST_NS detail::test_part_registrar_policy<int> mock_registrar_policy;
typedef G42CORE_TEST_NS detail::test_part_registrar<mock_registrar_policy> mocked_registrar;

extern G42CORE_CONCURRENCY_NS atomic<int> shared_index;

#ifdef HWC_PLATFORM_ANDROID
#include <sched.h>
#endif

inline void test_func()
{
#if 0
    printf("The ID of this thread is: %u\n", gettid());
    fflush(stdout);
#endif
    // Although the value isn't used, execute to try to create a race condition on initialization
    mocked_registrar::get();

#ifdef HWC_PLATFORM_ANDROID
    const unsigned int maxIterations = 10000;
#else
    const unsigned int maxIterations = 4000000000u;
#endif

    const int minCount = 10;
    unsigned int iterations = 0;
    while(shared_index.load() <= minCount)
    {
        if(iterations > maxIterations)
        {
            break;
        }
        ++iterations;
#ifdef HWC_PLATFORM_ANDROID
        if(iterations % 250)
        {
            sched_yield();
        }
#endif
    }
    auto range = mocked_registrar::get().range();
    (void)range;
#if 0
    auto count = boost::distance(range);
    printf("count in test_func %i ; iterations in test_count %u\n", count, iterations);
    fflush(stdout);
    VERIFY(count >= minCount);
#endif
}