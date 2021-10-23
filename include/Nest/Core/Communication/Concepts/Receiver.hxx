#ifndef NEST_CORE_COMMUNICATION_CONCEPTS_RECEIVER_HXX
#define NEST_CORE_COMMUNICATION_CONCEPTS_RECEIVER_HXX

#include <Nest/Core/Utility/Optional.hxx>
#include <concepts>

namespace Nest::Core::Concepts {

// clang-format off
template <typename Rx>
concept Receiver = requires (Rx t) {
  typename Rx::MessageType;
  { t.receive() } -> std::same_as<typename Rx::MessageType>;
  { t.try_receive() } -> std::same_as<Optional<typename Rx::MessageType>>;
};
// clang-format on

}	 // namespace Nest::Core::Concepts

#endif	  // NEST_CORE_COMMUNICATION_CONCEPTS_RECEIVER_HXX