#ifndef NEST_CORE_COMMUNICATION_CONCEPTS_RECEIVER_HXX
#define NEST_CORE_COMMUNICATION_CONCEPTS_RECEIVER_HXX

#include <Nest/Core/Utility/Concepts/Common.hxx>
#include <Nest/Core/Utility/Optional.hxx>

namespace Nest::Core::Concepts {

// clang-format off
template <typename Rx>
concept Receiver = requires (Rx t) {
  typename Rx::MessageType;
  { t.receive() } -> SameAs<typename Rx::MessageType>;
  { t.try_receive() } -> SameAs<Optional<typename Rx::MessageType>>;
};
// clang-format on

}	 // namespace Nest::Core::Concepts

#endif	  // NEST_CORE_COMMUNICATION_CONCEPTS_RECEIVER_HXX