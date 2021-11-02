#ifndef NEST_CORE_UTILITY_ASSERT_HXX
#define NEST_CORE_UTILITY_ASSERT_HXX

#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <exception>

namespace Nest::Utility {

template <typename... Args>
void Assert(bool expr, fmt::format_string<Args...> fmt, Args&&... fmt_args) {
#ifdef NEST_DEBUG
	if (!expr) {
		spdlog::error(fmt, std::forward<Args>(fmt_args)...);
		std::terminate();
	}
#endif
}

}	 // namespace Nest

#endif	  // NEST_CORE_UTILITY_ASSERT_HXX
