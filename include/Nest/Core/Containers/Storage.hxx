#ifndef NEST_CORE_CONTAINERS_STORAGE_HXX
#define NEST_CORE_CONTAINERS_STORAGE_HXX

#include <Nest/Core/Utility/Assert.hxx>
#include <Nest/Core/Utility/CommonTypes.hxx>
#include <Nest/Core/Utility/Concepts/Common.hxx>
#include <cstring>
#include <new>
#include <type_traits>

namespace Nest::Core {

template <typename T>
class Storage
{
	union StorageValueType {
		T value;

		StorageValueType() {}
		~StorageValueType() {}
	};

public:
	using ValueType = T;

private:
	StorageValueType* s_;
	usize size_;

public:
	explicit Storage(usize size) : s_(new StorageValueType[size]), size_(size) {}

	// Note: The user is required to call the dtors of each individual
	// constructed object in the storage
	~Storage() {
		delete[] s_;
	}

	Storage(Storage& const other) requires CopyConstructible<ValueType>
		: s_(new StorageValueType[other.size_]), size_(other.size_) {
		for (usize i = 0; i < size_; ++i) {
			s_[i].value = ValueType(other.get_at(i));
		}
	}

	Storage& operator=(Storage const& other) requires std::is_copy_assignable_v<ValueType> {
		if (this == &other) return *this;

		size_ = other.size_;
		delete[] s_;
		s_ = new StorageValueType[size_];
		for (usize i = 0; i < size_; ++i) {
			s_[i].value = ValueType(other.get_at(i));
		}

		return *this;
	}

	Storage(Storage&& other) noexcept : s_(std::exchange(other.s_, nullptr)), size_(std::exchange(other.size_, 0)) {}

	Storage& operator=(Storage&& other) noexcept {
		if (this == &other) return *this;

		s_ = std::exchange(other.s_, nullptr);
		size_ = std::exchange(other.size_, 0);

		return *this;
	}

	[[nodiscard]] usize size() const noexcept {
		return size_;
	}

	void resize(usize new_size) {
		auto* new_s = new StorageValueType[new_size];

		std::memcpy(new_s, s_, std::min(size_, new_size));
		delete[] s_;
		s_ = new_s;
	}

	template <typename... Args>
	void create_at(usize idx, Args&&... args) noexcept(std::is_nothrow_constructible_v<ValueType, Args...>) {
		Utility::Assert(idx < size_, "Index out of bounds: {}", idx);

		s_[idx].value = ValueType(std::forward<Args>(args)...);
	}

	// clang-format off
	void insert_at(usize idx, ValueType const& val)
		noexcept(std::is_nothrow_copy_constructible_v<ValueType>)
		requires std::is_copy_constructible_v<ValueType>
	{
		Utility::Assert(idx < size_, "Index out of bounds: {}", idx);

		s_[idx].value = ValueType(val);
	}

	void insert_at(usize idx, ValueType&& val)
		noexcept(std::is_nothrow_copy_constructible_v<ValueType>)
		requires std::is_copy_constructible_v<ValueType>
	{
		Utility::Assert(idx < size_, "Index out of bounds: {}", idx);

		s_[idx].value = ValueType(std::move(val));
	}

	ValueType remove_at(usize idx)
		noexcept(std::is_nothrow_move_constructible_v<ValueType>)
		requires std::is_move_constructible_v<>
	{
		Utility::Assert(idx < size_, "Index out of bounds: {}", idx);

		ValueType temp = std::move(s_[idx].value);
		return temp;
	}

	// clang-format on

	void destroy_at(usize idx) noexcept(std::is_nothrow_destructible_v<ValueType>) {
		Utility::Assert(idx < size_, "Index out of bounds: {}", idx);

		s_[idx].value.~ValueType();
	}


	ValueType& get_at(usize idx) noexcept {
		Utility::Assert(idx < size_, "Index out of bounds: {}", idx);

		return s_[idx].value;
	}

	ValueType const& get_at(usize idx) const noexcept {
		Utility::Assert(idx < size_, "Index out of bounds: {}", idx);

		return s_[idx].value;
	}
};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_CONTAINERS_STORAGE_HXX
