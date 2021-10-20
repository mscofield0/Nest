#ifndef NEST_CORE_COMMUNICATION_RECEIVER_HXX
#define NEST_CORE_COMMUNICATION_RECEIVER_HXX

#include <Nest/Core/Communication/Channel.hxx>
#include <Nest/Core/Utility/Optional.hxx>
#include <memory>

namespace Nest::Core {

/// @brief A type that only receives messages from the channel.
///
/// @tparam MessageType Type that will be sent and received.
///
template <typename Message>
class Receiver
{
public:
	/// @brief The message type to receive
	///
	using MessageType = Message;

	/// @brief The channel type to listen to
	///
	using ChannelType = Channel<MessageType>;



private:
	/// @brief The channel to listen to
	///
	const std::shared_ptr<ChannelType> channel_;

public:
	/// @brief Construct a new Receiver object
	///
	/// @param channel The channel to listen to
	///
	explicit Receiver(std::shared_ptr<ChannelType> channel)
		: channel_(std::move(channel)) {}

	/// @brief Blocks until it has received a message from the channel.
	///
	/// @return The message received from the channel.
	///
	MessageType receive() const {
		return channel_->receive();
	}

	/// @brief Gets the received message from the channel if available.
	///
	/// @return The message if the channel has messages in its
	/// buffer, `std::nullopt` otherwise.
	///
	Optional<MessageType> try_receive() const {
		return channel_->try_receive();
	}
};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_COMMUNICATION_RECEIVER_HXX