#ifndef NEST_CORE_COMMUNICATION_CHANNEL_HXX
#define NEST_CORE_COMMUNICATION_CHANNEL_HXX

#include <Nest/Core/Containers/ConcurrentQueue.hxx>
#include <Nest/Core/Utility/CommonTypes.hxx>
#include <Nest/Core/Utility/Optional.hxx>

namespace Nest::Core {

/// @brief An interface for sending and receiving messages from a queue.
///
/// @tparam MessageType Type that will be sent and received.
///
template <typename MessageType>
class Channel
{
	/// @brief The message buffer.
	///
	ConcurrentQueue<MessageType> queue_;

public:
	/// @brief Construct a new Channel object.
	///
	/// @param size The number of messages able to store.
	///
	explicit Channel(usize size) : queue_(size) {}

	/// @brief Blocks until it has enqueued a message in the queue.
	///
	/// @param msg The message to enqueue in the queue.
	///
	void send(MessageType&& msg) {
		while (!queue_.try_enqueue(std::move(msg)))
			;
	}

	/// @brief Blocks until it has enqueued a message in the queue.
	///
	/// @param msg The message to enqueue in the queue.
	///
	void send(MessageType const& msg) {
		while (!queue_.try_enqueue(msg))
			;
	}

	/// @brief Tries to enqueue a message in the queue.
	///
	/// @param msg The message to enqueue in the queue.
	///
	/// @return True if the message was enqueued successfully,
	/// false otherwise.
	///
	bool try_send(MessageType&& msg) {
		return queue_.try_enqueue(std::move(msg));
	}

	/// @brief Tries to enqueue a message in the queue.
	///
	/// @param msg The message to enqueue in the queue.
	///
	/// @return True if the message was enqueued successfully,
	/// false otherwise.
	///
	bool try_send(MessageType const& msg) {
		return queue_.try_enqueue(msg);
	}

	/// @brief Blocks until it has dequeued a message from the queue.
	///
	/// @return The message dequeued from the queue.
	///
	MessageType receive() {
		MessageType msg;
		while (!queue_.try_dequeue(msg))
			;

		return msg;
	}

	/// @brief Blocks until it has dequeued a message from the queue.
	///
	/// @return The message if the queue is not empty, `std::nullopt`
	/// otherwise.
	///
	Optional<MessageType> try_receive() {
		MessageType msg;
		if (!queue_.try_dequeue(msg)) return {};

		return msg;
	}
};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_COMMUNICATION_CHANNEL_HXX