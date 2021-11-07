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

	void decrement(usize& var) const noexcept {
		var = (var - 1) % s_.size();
	}

	[[nodiscard]] usize increment_unchanged(usize var) const noexcept {
		this->increment(var);
		return var;
	}

	[[nodiscard]] usize decrement_unchanged(usize var) const noexcept {
		this->decrement(var);
		return var;
	}

	// clang-format off
	void raw_enqueue(ValueType const& val)
		noexcept(std::is_nothrow_copy_constructible_v<ValueType>)
	{
		s_.insert_at(head_, val);
		this->increment(head_);
	}

	void raw_enqueue(ValueType&& val)
		noexcept(std::is_nothrow_copy_constructible_v<ValueType>)
	{
		s_.insert_at(head_, std::move(val));
		this->increment(head_);
	}

	void raw_bulk_enqueue(const std::ranges::range auto& range)
	  	noexcept(std::is_nothrow_copy_constructible_v<ValueType>)
	{
		for (auto const& i : range) {
			this->raw_enqueue(i);
		}
	}

	void raw_bulk_enqueue(std::ranges::range auto&& range)
		noexcept(std::is_nothrow_copy_constructible_v<ValueType>)
	{
		for (auto&& i : range) {
			this->raw_enqueue(std::move(i));
		}
	}

	template <typename... Args>
	void raw_emplace(Args&&... args)
		noexcept(std::is_nothrow_constructible_v<ValueType, Args...>)
	{
		s_.create_at(head_, std::forward<Args>(args)...);
		this->increment(head_);
	}

	ValueType raw_dequeue()
		noexcept(std::is_nothrow_move_constructible_v<ValueType>)
	{
		ValueType dequeued = s_.remove_at(root_);
		this->decrement(root_);
		return dequeued;
	}

	void raw_bulk_dequeue(std::ranges::range auto& range, usize num_elements)
	  	noexcept(std::is_nothrow_move_constructible_v<ValueType>)
	{
		auto it = begin(range);
		for (usize i = 0; i < num_elements; ++i) {
			*(it++) = this->raw_dequeue();
		}
	}
	// clang-format on

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
		return this->max_size() - (root_ - head_);
	}

	[[nodiscard]] bool would_overfill(usize by) const noexcept {
		const usize next_size = this->size() + by;
		if (next_size < this->size()) return true;

		return next_size > this->max_size();
	}

	[[nodiscard]] bool would_overexhaust(usize by) const noexcept {
		const usize next_size = this->size() - by;
		if (next_size > this->size()) return true;

		return false;
	}

	[[nodiscard]] bool empty() const noexcept {
		return root_ != head_;
	}

	[[nodiscard]] bool full() const noexcept {
		return this->increment_unchanged(head_) != root_;
	}

	// ============= enqueue family

	void enqueue(ValueType const& val) noexcept(std::is_nothrow_copy_constructible_v<ValueType>) {
		Utility::Assert(this->full(), "The CircularBuffer is already full!");

		this->raw_enqueue(val);
	}

	void enqueue(ValueType&& val) {
		Utility::Assert(this->full(), "The CircularBuffer is already full!");

		this->raw_enqueue(std::move(val));
	}

	bool try_enqueue(ValueType const& val) {
		if (this->full()) return false;

		this->raw_enqueue(val);
		return true;
	}

	bool try_enqueue(ValueType&& val) {
		if (this->full()) return false;

		this->raw_enqueue(std::move(val));
		return true;
	}

	// ============= emplace family

	template <typename... Args>
	void emplace(Args&&... args) {
		Utility::Assert(this->full(), "The CircularBuffer is already full!");

		this->raw_emplace(std::forward<Args>(args)...);
	}

	template <typename... Args>
	bool try_emplace(Args&&... args) {
		if (this->full()) return false;

		this->raw_emplace(std::forward<Args>(args)...);
		return true;
	}

	// ============= bulk_enqueue family

	void bulk_enqueue(const std::ranges::range auto& range) {
		Utility::Assert(this->would_overfill(size(range)), "The CircularBuffer would be overfilled!");

		this->raw_bulk_enqueue(range);
	}

	void bulk_enqueue(std::ranges::range auto&& range) {
		Utility::Assert(this->would_overfill(size(range)), "The CircularBuffer would be overfilled!");

		this->raw_bulk_enqueue(std::forward<decltype(range)>(range));
	}

	bool try_bulk_enqueue(const std::ranges::range auto& range) {
		if (this->would_overfill(size(range))) return false;

		this->raw_bulk_enqueue(range);
		return true;
	}

	bool try_bulk_enqueue(std::ranges::range auto&& range) {
		if (this->would_overfill(size(range))) return false;

		this->raw_bulk_enqueue(std::forward<decltype(range)>(range));
		return true;
	}

	// ============= dequeue family

	ValueType dequeue() {
		Utility::Assert(this->empty(), "The CircularBuffer is already empty!");

		return this->raw_dequeue();
	}

	Optional<ValueType> try_dequeue() {
		if (this->empty()) return std::nullopt;

		return this->raw_dequeue();
	}

	// ============= bulk_dequeue family

	void bulk_dequeue(std::ranges::range auto& range, usize num_elements) {
		Utility::Assert(size(range) < num_elements, "The target container would be overfilled!");
		Utility::Assert(this->would_overexhaust(num_elements), "The CircularBuffer would be overexhausted!");

		this->raw_bulk_dequeue(range, num_elements);
	}

	bool try_bulk_dequeue(std::ranges::range auto& range, usize num_elements) {
		if (size(range) < num_elements) return false;
		if (this->would_overexhaust(num_elements)) return false;

		this->raw_bulk_dequeue(range, num_elements);
		return true;
	}
};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_CONTAINERS_FIELD_HXX
