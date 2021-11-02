#ifndef NEST_CORE_CONTAINERS_PRIORITYQUEUE_HXX
#define NEST_CORE_CONTAINERS_PRIORITYQUEUE_HXX

#include <Nest/Core/Utility/CommonTypes.hxx>
#include <Nest/Core/Utility/Concepts/Trivial.hxx>
#include <Nest/Core/Utility/Assert.hxx>
#include <memory>

namespace Nest::Core {

template <typename T>
class PriorityQueue
{
	std::unique_ptr<std::aligned_storage<>> field_;
	usize root_;
	usize head_;

	void push_impl(T const& val) {
		field_[head_] = val;
		head_ = (head_ + 1) % field_.size();
	}

	void push_impl(T&& val) {
		field_[head_] = std::move(val);
	}

public:
	explicit PriorityQueue(usize buf_size) : field_(buf_size), root_{0}, head_{0} {}

	void push(T const& val) {
		Assert(head_ + 1 != root_, "The queue is already full!");

		field_[head_] = val;

	}

	void push(T&& val) {
		field_.push_back(std::move(val));
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
