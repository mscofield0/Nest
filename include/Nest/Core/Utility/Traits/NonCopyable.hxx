#ifndef NEST_UTILITY_TRAITS_NONCOPYABLE_HXX
#define NEST_UTILITY_TRAITS_NONCOPYABLE_HXX

namespace Nest::Utility {

class NonCopyable
{
public:
	NonCopyable(NonCopyable const&) = delete;
	NonCopyable operator=(NonCopyable const&) = delete;
};

}	 // namespace Nest::Utility

#endif	  // NEST_UTILITY_TRAITS_NONCOPYABLE_HXX