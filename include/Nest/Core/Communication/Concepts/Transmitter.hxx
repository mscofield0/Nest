#ifndef NEST_CORE_COMMUNICATION_CONCEPTS_TRANSMITTER_HXX
#define NEST_CORE_COMMUNICATION_CONCEPTS_TRANSMITTER_HXX

#include <concepts>

namespace Nest::Core::Concepts {

// clang-format off
template <typename Tx>
concept Transmitter = requires (Tx t, typename Tx::MessageType m) {
  typename Tx::MessageType;
  { t.send(m) } -> std::same_as<void>;
  { t.try_send(m) } -> std::same_as<bool>;
};
// clang-format on

}	 // namespace Nest::Core::Concepts

#endif	  // NEST_CORE_COMMUNICATION_CONCEPTS_TRANSMITTER_HXX