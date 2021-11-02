#ifndef NEST_CORE_CONTAINERS_FIELD_HXX
#define NEST_CORE_CONTAINERS_FIELD_HXX

#include <Nest/Core/Containers/Storage.hxx>
#include <Nest/Core/Utility/Optional.hxx>
#include <utility>

namespace Nest::Core {

template <typename T>
class CircularBuffer
{
public:
	using ValueType = T;

private:
	Storage<ValueType> s_;
	usize root_;
	usize head_;

private:
	void increment(usize& var) const noexcept {
		var = (var + 1) % s_.size();
	}

	usize increment_unchanged(usize var) const noexcept {
		this->increment(var);
		return var;
	}

	void raw_enqueue(ValueType const& val) noexcept(std::is_nothrow_copy_constructible_v<ValueType>) {
		s_.insert_at(head_, val);
		this->increment(head_);
	}

	void raw_enqueue(ValueType&& val) noexcept(std::is_nothrow_copy_constructible_v<ValueType>) {
		s_.insert_at(head_, std::move(val));
		this->increment(head_);
	}

	ValueType raw_dequeue() noexcept(std::is_nothrow_move_constructible_v<ValueType>)

public:
	explicit CircularBuffer(usize size) : s_(size), root_(0), head_(0) {}

	~CircularBuffer() {
		while (root_ != head_) {
			s_.destroy_at(root_);
			this->increment(root_);
		}
	}

	CircularBuffer(CircularBuffer const&) = default;
	CircularBuffer& operator=(CircularBuffer const&) = default;
	CircularBuffer(CircularBuffer&&) noexcept = default;
	CircularBuffer& operator=(CircularBuffer&&) noexcept = default;

	[[nodiscard]] usize max_size() const noexcept {
		return s_.size();
	}

	[[nodiscard]] usize size() const noexcept {
		if (head_ >= root_) return head_ - root_;
		return max_size() - (root_ - head_);
	}

	[[nodiscard]] bool would_overfill(usize by) const noexcept {
		const usize next_size = size() + by;
		if (next_size < size()) return true;

		return next_size > max_size();
	}

	[[nodiscard]] bool empty() const noexcept {
		return root_ != head_;
	}

	[[nodiscard]] bool full() const noexcept {
		return this->increment_unchanged(head_) != root_;
	}

	void enqueue(ValueType const& val) noexcept(std::is_nothrow_copy_constructible_v<ValueType>) {
		Utility::Assert(this->full(), "The CircularBuffer is already full!");

		this->raw_enqueue(val);
	}

	void enqueue(ValueType&& val) {
		Utility::Assert(this->full(), "The CircularBuffer is already full!");

		this->raw_enqueue(std::move(val));
	}

	template <typename... Args>
	void emplace(Args&&... args) {
		Utility::Assert(this->full(), "The CircularBuffer is already full!");

		s_.create_at(head_, std::forward<Args>(args)...);
		this->increment(head_);
	}

	void bulk_enqueue(std::ranges::range auto&& range) {
		Utility::Assert(would_overfill(size(range)), "The CircularBuffer would be overfilled!");

		for (auto const& i : range) {
			this->raw_enqueue(i);
		}
	}

	bool try_enqueue(ValueType const& val) {
		if (this->full()) return false;

		s_.insert_at(head_, val);
		this->increment(head_);
		return true;
	}

	bool try_enqueue(ValueType&& val) {
		if (this->full()) return false;

		s_.insert_at(head_, std::move(val));
		this->increment(head_);
		return true;
	}

	template <typename... Args>
	bool try_emplace(Args&&... args) {
		if (this->full()) return false;

		s_.create_at(head_, std::forward<Args>(args)...);
		this->increment(head_);
		return true;
	}

	ValueType dequeue() {
		Utility::Assert(this->empty(), "The CircularBuffer is already empty!");

		return s_.remove_at(root_);
	}

	Optional<ValueType> try_dequeue() {
		if (this->empty()) return std::nullopt;

		return s_.remove_at(root_);
	}
};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_CONTAINERS_FIELD_HXX
