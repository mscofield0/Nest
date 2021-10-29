#ifndef NEST_CORE_CONCURRENCY_SCHEDULER_HXX
#define NEST_CORE_CONCURRENCY_SCHEDULER_HXX

#include <chrono>
#include <Nest/Core/Concurrency/ThreadPool.hxx>

namespace Nest::Core {

class Scheduler {
	ThreadPool thread_pool_;

	void reschedule();
	void add_task();
	Task current();
	Task next();

};

}

#endif	  // NEST_CORE_CONCURRENCY_SCHEDULER_HXX