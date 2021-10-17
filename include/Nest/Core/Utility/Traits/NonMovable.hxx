#ifndef NEST_UTILITY_TRAITS_NONMOVEBLE_HXX
#define NEST_UTILITY_TRAITS_NONMOVEBLE_HXX

namespace Nest::Utility {

class NonMovable
{
public:
	NonMovable(NonMovable&&) = delete;
	NonMovable operator=(NonMovable&&) = delete;
};

}	 // namespace Nest::Utility

#endif	  // NEST_UTILITY_TRAITS_NONMOVEBLE_HXX