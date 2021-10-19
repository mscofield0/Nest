#ifndef NEST_UTILITY_TRAITS_NONCOPYABLE_HXX
#define NEST_UTILITY_TRAITS_NONCOPYABLE_HXX

namespace Nest::Utility {

class NonCopyable
{
public:
	NonCopyable() = default;
	NonCopyable(NonCopyable const&) = delete;
	NonCopyable& operator=(NonCopyable const&) = delete;
	NonCopyable(NonCopyable&&) = default;
	NonCopyable& operator=(NonCopyable&&) = default;
};

}	 // namespace Nest::Utility

#endif	  // NEST_UTILITY_TRAITS_NONCOPYABLE_HXX