#ifndef NEST_CORE_COMMUNICATION_ONESHOT_HXX
#define NEST_CORE_COMMUNICATION_ONESHOT_HXX

#include <Nest/Core/Communication/Channel.hxx>
#include <Nest/Core/Communication/Receiver.hxx>
#include <Nest/Core/Communication/Transmitter.hxx>
#include <Nest/Core/Utility/CommonTypes.hxx>
#include <Nest/Core/Utility/Traits/NonCopyable.hxx>

namespace Nest::Core {

/// @brief A single producer, single consumer communication type
/// with a single message sending.
///
/// @tparam MessageType Type that will be sent and received.
///
template <typename MessageType>
class Oneshot
{
	/// @brief A non-copyable Transmitter type.
	///
	struct Transmitter : public ::Nest::Core::Transmitter<MessageType>,
						 Utility::NonCopyable
	{};

	/// @brief A non-copyable Receiver type.
	///
	struct Receiver : public ::Nest::Core::Receiver<MessageType>,
					  Utility::NonCopyable
	{};

public:
	using ChannelType = Channel<MessageType>;
	using Tx = Tunnel::Transmitter;
	using Rx = Tunnel::Receiver;

	Tx tx;
	Rx rx;

public:
	/// @brief Creates a Oneshot channel.
	///
	/// @return The created Oneshot channel.
	///
	static Oneshot create() {
		auto channel = std::make_shared<ChannelType>(1);

		return {
		  Tx(channel),
		  Rx(std::move(channel)),
		};
	}
};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_COMMUNICATION_ONESHOT_HXX