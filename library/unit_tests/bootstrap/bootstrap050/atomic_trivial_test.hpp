#include "g42core/concurrency/atomic.hpp"

class atomic_trivial_test
{
public:
    atomic_trivial_test():
        atom(false)
    {}
    void ExecuteOnEachThread()
    {
        // This is a "doesn't crash" test rather than a correctness test and not a great one at 
        // that
        for(unsigned int i = 0; i < 10000; ++i)
        {
            atom.store(!atom.load());
        }
    }
private:
    G42CORE_CONCURRENCY_NS atomic<bool> atom;
};

extern atomic_trivial_test atomicTrivialTest;