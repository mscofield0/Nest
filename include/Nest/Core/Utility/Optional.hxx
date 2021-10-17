#ifndef NEST_CORE_UTILITY_OPTIONAL_HXX
#define NEST_CORE_UTILITY_OPTIONAL_HXX

#include <optional>

namespace Nest {

template <typename T>
using Optional = std::optional<T>;

}

#endif	  // NEST_CORE_UTILITY_OPTIONAL_HXX