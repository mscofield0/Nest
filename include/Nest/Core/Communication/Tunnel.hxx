#ifndef NEST_CORE_COMMUNICATION_TUNNEL_HXX
#define NEST_CORE_COMMUNICATION_TUNNEL_HXX

#include <Nest/Core/Communication/Channel.hxx>
#include <Nest/Core/Communication/Receiver.hxx>
#include <Nest/Core/Communication/Transmitter.hxx>
#include <Nest/Core/Utility/CommonTypes.hxx>
#include <Nest/Core/Utility/Traits/NonCopyable.hxx>

namespace Nest::Core {

/// @brief A single producer, single consumer communication type.
///
/// @tparam MessageType Type that will be sent and received.
///
template <typename MessageType>
class Tunnel
{
	/// @brief A non-copyable Transmitter type.
	///
	struct Transmitter : public ::Nest::Core::Transmitter<MessageType>,
						 Utility::NonCopyable
	{
		using ::Nest::Core::Transmitter<MessageType>::Transmitter;
	};

	/// @brief A non-copyable Receiver type.
	///
	struct Receiver : public ::Nest::Core::Receiver<MessageType>,
					  Utility::NonCopyable
	{
		using ::Nest::Core::Receiver<MessageType>::Receiver;
	};

public:
	using ChannelType = Channel<MessageType>;
	using Tx = Tunnel::Transmitter;
	using Rx = Tunnel::Receiver;

	Tx tx;
	Rx rx;

public:
	/// @brief Creates a Tunnel.
	///
	/// @param buffer_size The maximum number of messages stored by the
	/// channel.
	///
	/// @return The created Tunnel.
	///
	static Tunnel create(usize buffer_size) {
		auto channel = std::make_shared<ChannelType>(buffer_size);

		return {
		  Tx(channel),
		  Rx(std::move(channel)),
		};
	}
};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_COMMUNICATION_TUNNEL_HXX