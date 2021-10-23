#ifndef NEST_CORE_UTILITY_ATOMIC_HXX
#define NEST_CORE_UTILITY_ATOMIC_HXX

#include <atomic>

namespace Nest {

template <typename T>
using Atomic = std::atomic<T>;

}

#endif	  // NEST_CORE_UTILITY_ATOMIC_HXX
