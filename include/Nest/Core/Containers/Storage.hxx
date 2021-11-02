#ifndef NEST_CORE_CONTAINERS_STORAGE_HXX
#define NEST_CORE_CONTAINERS_STORAGE_HXX

#include <Nest/Core/Utility/Assert.hxx>
#include <Nest/Core/Utility/CommonTypes.hxx>
#include <cstring>
#include <new>
#include <type_traits>

namespace Nest::Core {

template <typename T>
class Storage
{
public:
	using AlignedType = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
	using ValueType = T;

private:
	AlignedType* s_;
	usize size_;

public:
	explicit Storage(usize size) : s_(new AlignedType[size]), size_(size) {}

	// Note: The user is required to call the dtors of each individual
	// constructed object in the storage
	~Storage() {
		delete[] s_;
	}

	Storage(Storage& const other) requires std::is_copy_constructible_v<ValueType>
		: s_(new AlignedType[other.size_]), size_(other.size_) {
		for (usize i = 0; i < size_; ++i) {
			new (std::launder(&s_[i])) ValueType(other.get_at(i));
		}
	}

	Storage& operator=(Storage const& other) requires std::is_copy_constructible_v<ValueType> {
		if (this == &other) return *this;

		size_ = other.size_;
		delete[] s_;
		s_ = new AlignedType[size_];
		for (usize i = 0; i < size_; ++i) {
			new (std::launder(&s_[i])) ValueType(other.get_at(i));
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
		auto* new_s = new AlignedType[new_size];

		std::memcpy(new_s, s_, std::min(size_, new_size));
		delete[] s_;
		s_ = new_s;
	}

	template <typename... Args>
	void create_at(usize idx, Args&&... args) noexcept(std::is_nothrow_constructible_v<ValueType, Args...>) {
		Utility::Assert(idx < size_, "Index out of bounds: {}", idx);

		new (std::launder(&s_[idx])) T(std::forward<Args>(args)...);
	}

	// clang-format off
	void insert_at(usize idx, ValueType const& val)
		noexcept(std::is_nothrow_copy_constructible_v<ValueType>)
		requires std::is_copy_constructible_v<ValueType>
	{
		Utility::Assert(idx < size_, "Index out of bounds: {}", idx);

		new (std::launder(&s_[idx])) ValueType(val);
	}
	// clang-format on

	void destroy_at(usize idx) noexcept(std::is_nothrow_destructible_v<ValueType>) {
		Utility::Assert(idx < size_, "Index out of bounds: {}", idx);

		reinterpret_cast<ValueType*>(&s_[idx])->~ValueType();
	}

	ValueType& get_at(usize idx) noexcept {
		Utility::Assert(idx < size_, "Index out of bounds: {}", idx);

		return reinterpret_cast<ValueType>(s_[idx]);
	}

	ValueType const& get_at(usize idx) const noexcept {
		Utility::Assert(idx < size_, "Index out of bounds: {}", idx);

		return reinterpret_cast<ValueType>(s_[idx]);
	}

	void zero_out() noexcept {
		std::memset(s_, 0, size_);
	}
};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_CONTAINERS_STORAGE_HXX
