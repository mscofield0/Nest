#ifndef NEST_CORE_COMMUNICATION_ONESHOT_HXX
#define NEST_CORE_COMMUNICATION_ONESHOT_HXX

#include <Nest/Core/Communication/OneshotChannel.hxx>
#include <Nest/Core/Communication/Receiver.hxx>
#include <Nest/Core/Communication/Transmitter.hxx>
#include <Nest/Core/Utility/CommonTypes.hxx>
#include <Nest/Core/Utility/Traits/NonCopyable.hxx>

namespace Nest::Core {

/// @brief A single producer, single consumer communication type
/// with a single message sending.
///
/// @tparam Message Type that will be sent and received.
///
template <typename Message>
class Oneshot
{
public:
	using MessageType = Message;
	using ChannelType = OneshotChannel<MessageType>;

private:
	/// @brief A non-copyable Transmitter type.
	///
	struct Transmitter : public ::Nest::Core::Transmitter<ChannelType>,
						 Utility::NonCopyable
	{
		using ::Nest::Core::Transmitter<ChannelType>::Transmitter;
	};

	/// @brief A non-copyable Receiver type.
	///
	struct Receiver : public ::Nest::Core::Receiver<ChannelType>,
					  Utility::NonCopyable
	{
		using ::Nest::Core::Receiver<ChannelType>::Receiver;
	};

public:
	using Tx = Oneshot::Transmitter;
	using Rx = Oneshot::Receiver;

	Tx tx;
	Rx rx;

public:
	/// @brief Creates a Oneshot channel.
	///
	/// @return The created Oneshot channel.
	///
	static Oneshot create() {
		auto channel = std::make_shared<ChannelType>();

		return {
		  Tx(channel),
		  Rx(std::move(channel)),
		};
	}
};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_COMMUNICATION_ONESHOT_HXX