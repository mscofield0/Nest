#ifndef NEST_CORE_CONTAINERS_CONCURRENTQUEUE_HXX
#define NEST_CORE_CONTAINERS_CONCURRENTQUEUE_HXX

#include <concurrent_queue.h>

namespace Nest::Core {

template <typename T>
using ConcurrentQueue = moodycamel::ConcurrentQueue<T>;

}	 // namespace Nest::Core

#endif	  // NEST_CORE_CONTAINERS_CONCURRENTQUEUE_HXX