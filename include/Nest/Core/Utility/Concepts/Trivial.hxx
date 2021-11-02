#ifndef NEST_CORE_UTILITY_CONCEPTS_TRIVIAL_HXX
#define NEST_CORE_UTILITY_CONCEPTS_TRIVIAL_HXX

#include <type_traits>

namespace Nest::Utility::Concepts {

template <typename T>
concept Trivial = std::is_trivial_v<T>;

}	 // namespace Nest::Utility::Concepts

#endif	  // NEST_CORE_UTILITY_CONCEPTS_TRIVIAL_HXX
