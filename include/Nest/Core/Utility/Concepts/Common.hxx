#ifndef NEST_CORE_UTILITY_CONCEPTS_COMMON_HXX
#define NEST_CORE_UTILITY_CONCEPTS_COMMON_HXX

#include <concepts>

namespace Nest::Core {

template <typename T, typename U>
concept SameAs = std::same_as<T, U>;

template <typename Derived, typename Base>
concept DerivedFrom = std::derived_from<Derived, Base>;

template <typename From, typename To>
concept ConvertibleTo = std::convertible_to<From, To>;

template <typename T, typename U>
concept CommonReferenceWith = std::common_reference_with<T, U>;

template <typename T, typename U>
concept CommonWith = std::common_with<T, U>;

template <typename T>
concept Integral = std::integral<T>;

template <typename T>
concept SignedIntegral = std::signed_integral<T>;

template <typename T>
concept UnsignedIntegral = std::unsigned_integral<T>;

template <typename T>
concept FloatingPoint = std::floating_point<T>;

template <typename L, typename R>
concept AssignableFrom = std::assignable_from<L, R>;

template <typename T>
concept Swappable = std::swappable<T>;

template <typename T, typename U>
concept SwappableWith = std::swappable_with<T, U>;

template <typename T>
concept NothrowDestructible = std::destructible<T>;

template <typename T, typename... Args>
concept ConstructibleFrom = std::constructible_from<T, Args...>;

template <typename T>
concept DefaultInitializable = std::default_initializable<T>;

template <typename T>
concept MoveConstructible = std::move_constructible<T>;

template <typename T>
concept CopyConstructible = std::copy_constructible<T>;

template <typename T>
concept EqualityComparable = std::equality_comparable<T>;

template <typename T, typename U>
concept EqualityComparableWith = std::equality_comparable_with<T, U>;

template <typename T>
concept TotallyOrdered = std::totally_ordered<T>;

template <typename T, typename U>
concept TotallyOrderedWith = std::totally_ordered_with<T, U>;

template <typename T>
concept Movable = std::movable<T>;

template <typename T>
concept Copyable = std::copyable<T>;

template <typename T>
concept Semiregular = std::semiregular<T>;

template <typename T>
concept Regular = std::regular<T>;

template <typename F, typename... Args>
concept Invocable = std::invocable<F, Args...>;

template <typename F, typename... Args>
concept RegularInvocable = std::regular_invocable<F, Args...>;

template <typename F, typename... Args>
concept Predicate = std::predicate<F, Args...>;

template <typename R, typename T, typename U>
concept Relation = std::relation<R, T, U>;

template <typename R, typename T, typename U>
concept EquivalenceRelation = std::equivalence_relation<R, T, U>;

template <typename R, typename T, typename U>
concept StrictWeakOrder = std::strict_weak_order<R, T, U>;

}

#endif	  // NEST_CORE_UTILITY_CONCEPTS_COMMON_HXX
