#ifndef NEST_CORE_CONTAINERS_FIELD_HXX
#define NEST_CORE_CONTAINERS_FIELD_HXX

#include <Nest/Core/Containers/Storage.hxx>

namespace Nest::Core {

template <typename T>
class Field {
	Storage<T> s_;
	usize root_;
	usize head_;

private:
	void increment(usize& var) noexcept {
		var = (var + 1) % s_.size();
	}

public:
	explicit Field(usize size) : s_(size), root_(0), head_(0) {}

	~Field() {
		while (root_ != head_) {
			s_.destroy_at(root_);
			increment(root_);
		}
	}
};

}

#endif	  // NEST_CORE_CONTAINERS_FIELD_HXX
