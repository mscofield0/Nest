#ifndef NEST_CORE_CONTAINERS_CONCURRENTQUEUE_HXX
#define NEST_CORE_CONTAINERS_CONCURRENTQUEUE_HXX

#include <Nest/Core/Containers/Detail/ConcurrentQueueImpl.hxx>

namespace Nest::Core {

template <typename T>
using ConcurrentQueue = moodycamel::ConcurrentQueue<T>;

}	 // namespace Nest::Core

#endif	  // NEST_CORE_CONTAINERS_CONCURRENTQUEUE_HXX