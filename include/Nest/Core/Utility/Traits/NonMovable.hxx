#ifndef NEST_CORE_UTILITY_TRAITS_NONMOVEBLE_HXX
#define NEST_CORE_UTILITY_TRAITS_NONMOVEBLE_HXX

namespace Nest::Utility {

class NonMovable
{
public:
	NonMovable() = default;
	NonMovable(NonMovable const&) = default;
	NonMovable& operator=(NonMovable const&) = default;
	NonMovable(NonMovable&&) = delete;
	NonMovable& operator=(NonMovable&&) = delete;
};

}	 // namespace Nest::Utility

#endif	  // NEST_CORE_UTILITY_TRAITS_NONMOVEBLE_HXX