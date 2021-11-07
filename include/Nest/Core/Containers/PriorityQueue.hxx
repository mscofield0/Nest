#ifndef NEST_CORE_CONTAINERS_PRIORITYQUEUE_HXX
#define NEST_CORE_CONTAINERS_PRIORITYQUEUE_HXX

#include <Nest/Core/Utility/CommonTypes.hxx>
#include <Nest/Core/Utility/Concepts/Trivial.hxx>
#include <Nest/Core/Utility/Assert.hxx>
#include <Nest/Core/Containers/CircularBuffer.hxx>
#include <memory>

namespace Nest::Core {

template <typename T>
class PriorityQueue
{
public:
	using ValueType = T;

private:
	CircularBuffer<ValueType> buf_;

public:
	explicit PriorityQueue(usize buf_size) : buf_(buf_size) {}

	void push(ValueType const& val) {
		buf_.enqueue(val);
	}

	void push(ValueType&& val) {
		buf_.push_back(std::move(val));
	}

	T pop() {
		Utility::Assert(root_ != head_, "The queue is already empty!");

		usize prev_root = root_;
		root_ = (root_ + 1) % field_.size();
		return field_[prev_root];
	}

};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_CONTAINERS_PRIORITYQUEUE_HXX
