#ifndef NEST_CORE_COMMUNICATION_CONCEPTS_CHANNEL_HXX
#define NEST_CORE_COMMUNICATION_CONCEPTS_CHANNEL_HXX

#include <Nest/Core/Utility/Optional.hxx>
#include <Nest/Core/Utility/Concepts/Common.hxx>

namespace Nest::Core::Concepts {

// clang-format off
template <typename C>
concept Channel = requires (C c, typename C::MessageType m) {
  typename C::MessageType;
  { c.send(m) } -> SameAs<void>;
  { c.try_send(m) } -> SameAs<bool>;
  { c.receive() } -> SameAs<typename C::MessageType>;
  { c.try_receive() } -> SameAs<Optional<typename C::MessageType>>;
};
// clang-format on

}	 // namespace Nest::Core::Concepts

#endif	  // NEST_CORE_COMMUNICATION_CONCEPTS_CHANNEL_HXX