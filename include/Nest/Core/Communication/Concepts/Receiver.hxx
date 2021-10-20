#ifndef NEST_CORE_COMMUNICATION_CONCEPTS_RECEIVER_HXX
#define NEST_CORE_COMMUNICATION_CONCEPTS_RECEIVER_HXX

#include <Nest/Core/Utility/Optional.hxx>
#include <concepts>

namespace Nest::Core::Concepts {

template <typename Tx>
concept Receiver = requires (Tx t) {
  typename Tx::MessageType;
  { t.receive() } -> std::same_as<typename Tx::MessageType>;
  { t.try_receive() } -> std::same_as<Optional<typename Tx::MessageType>>;
};

}

#endif // NEST_CORE_COMMUNICATION_CONCEPTS_RECEIVER_HXX