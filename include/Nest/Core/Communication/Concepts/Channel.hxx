#ifndef NEST_CORE_COMMUNICATION_CONCEPTS_CHANNEL_HXX
#define NEST_CORE_COMMUNICATION_CONCEPTS_CHANNEL_HXX

#include <Nest/Core/Utility/Optional.hxx>
#include <concepts>

namespace Nest::Core::Concepts {

// clang-format off
template <typename C>
concept Channel = requires (C c, typename C::MessageType m) {
  typename C::MessageType;
  { c.send(m) } -> std::same_as<void>;
  { c.try_send(m) } -> std::same_as<bool>;
  { c.receive() } -> std::same_as<typename C::MessageType>;
  { c.try_receive() } -> std::same_as<Optional<typename C::MessageType>>;
};
// clang-format on

}	 // namespace Nest::Core::Concepts

#endif	  // NEST_CORE_COMMUNICATION_CONCEPTS_CHANNEL_HXX