#ifndef NEST_CORE_CONCURRENCY_THREADPOOL_HXX
#ifndef NEST_CORE_CONCURRENCY_THREADPOOL_HXX

#include <vector>
#include <thread>
#include <Nest/Core/Containers/ConcurrentQueue.hxx>
#include <Nest/Core/Concurrency/Task.hxx>

namespace Nest::Core {

class ThreadPool {
	std::vector<std::thread> workers_;
	ConcurrentQueue<Task> work_queue_;

public:
	void enqueue(Task task);
};

}

#endif // NEST_CORE_CONCURRENCY_THREADPOOL_HXX