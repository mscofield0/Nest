#ifndef NEST_CORE_COMMUNICATION_TRANSMITTER_HXX
#define NEST_CORE_COMMUNICATION_TRANSMITTER_HXX

#include <memory>
#include <utility>

#include <Nest/Core/Communication/Channel.hxx>

namespace Nest::Core {

/// @brief A type that only sends messages to the channel.
///
/// @tparam MessageType Type that will be sent and received.
///
template <typename Message>
class Transmitter
{
public:
	/// @brief The message type to receive
	///
	using MessageType = Message;

	/// @brief The channel type to send to.
	///
	using ChannelType = Channel<MessageType>;

private:
	/// @brief The channel to send to.
	///
	const std::shared_ptr<ChannelType> channel_;

public:
	/// @brief Construct a new Transmitter object.
	///
	/// @param channel The channel to send to.
	///
	explicit Transmitter(std::shared_ptr<ChannelType> channel)
		: channel_(std::move(channel)) {}

	/// @brief Sends a message to the channel.
	///
	/// @param msg The message to sent to the channel.
	///
	void send(MessageType&& msg) const {
		channel_->send(std::move(msg));
	}

	/// @brief Sends a message to the channel.
	///
	/// @param msg The message to sent to the channel.
	///
	void send(MessageType const& msg) const {
		channel_->send(msg);
	}

	/// @brief Tries to send a message to the channel.
	///
	/// @param msg The message to sent to the channel.
	///
	/// @return True if the message was sent successfully,
	/// false otherwise.
	///
	bool try_send(MessageType&& msg) const {
		return channel_->try_send(std::move(msg));
	}

	/// @brief Tries to send a message to the channel.
	///
	/// @param msg The message to sent to the channel.
	///
	/// @return True if the message was sent successfully,
	/// false otherwise.
	///
	bool try_send(MessageType const& msg) const {
		return channel_->try_send(msg);
	}
};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_COMMUNICATION_TRANSMITTER_HXX