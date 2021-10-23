#ifndef NEST_CORE_COMMUNICATION_ONESHOTCHANNEL_HXX
#define NEST_CORE_COMMUNICATION_ONESHOTCHANNEL_HXX

#include <Nest/Core/Utility/Atomic.hxx>
#include <Nest/Core/Utility/Optional.hxx>

#include <stdexcept>

namespace Nest::Core {

/// @brief A channel holding a single value and accepting only one send.
///
/// @tparam Message Type that will be sent and received.
///
template <typename Message>
class OneshotChannel
{
public:
	/// @brief The message type.
	///
	using MessageType = Message;

private:
	enum class State {
		Empty,
		Firing,
		Fired,
		Acquired
	};

private:
	/// @brief The message buffer.
	///
	Optional<MessageType> value_;
	Atomic<State> state_;

public:
	OneshotChannel() noexcept = default;

	/// @brief Tries to fire a message into the channel.
	///
	/// @param msg The message to fire into the channel.
	///
	/// @return True if the message was fired successfully,
	/// false otherwise.
	///
	bool try_send(MessageType&& msg) noexcept(std::is_nothrow_move_assignable_v<MessageType>) {
		State expected = State::Empty;
		if (!state_.compare_exchange_strong(expected, State::Firing, std::memory_order_acq_rel)) {
			return false;
		}

		value_ = std::move(msg);
		state_.store(State::Fired, std::memory_order_release);

		return true;
	}

	/// @brief Tries to fire a message into the channel.
	///
	/// @param msg The message to fire into the channel.
	///
	/// @return True if the message was fired successfully,
	/// false otherwise.
	///
	bool try_send(MessageType const& msg) noexcept(std::is_nothrow_copy_assignable_v<MessageType>) {
		State expected = State::Empty;
		if (!state_.compare_exchange_strong(expected, State::Firing, std::memory_order_acq_rel)) {
			return false;
		}

		value_ = msg;
		state_.store(State::Fired, std::memory_order_relaxed);

		return true;
	}

	/// @brief Tries to fire a message into the channel.
	///
	/// @param msg The message to fire into the channel.
	///
	/// @remark Throws if the channel is exhausted.
	/// Prefer `try_send()` instead.
	///
	/// @note This method is only to satisfy the contract for
	/// `Concepts::Channel`.
	///
	void send(MessageType&& msg) {
		const bool already_sent = !this->try_send(std::move(msg));

		if (already_sent) {
			throw std::runtime_error("Already sent a message to the Oneshot channel.");
		}
	}

	/// @brief Tries to fire a message into the channel.
	///
	/// @param msg The message to fire into the channel.
	///
	/// @remark Throws if the channel is exhausted.
	/// Prefer `try_send()` instead.
	///
	/// @note This method is only to satisfy the contract for
	/// `Concepts::Channel`.
	///
	void send(MessageType const& msg) {
		const bool already_sent = !this->try_send(msg);

		if (already_sent) {
			throw std::runtime_error("Already sent a message to the Oneshot channel.");
		}
	}

	/// @brief Tries to receive a message from the channel.
	///
	/// @return MessageType if the value is in the channel and it hasn't yet
	/// been acquired, std::nullopt otherwise.
	///
	Optional<MessageType> try_receive() noexcept(std::is_nothrow_move_constructible_v<MessageType>) {
		State expected = State::Fired;
		if (!state_.compare_exchange_strong(expected, State::Acquired, std::memory_order_acq_rel)) {
			return {};
		}

		MessageType msg = std::move(value_.value());
		value_ = {};
		return msg;
	}

	/// @brief Blocks until it has received a message from the channel or
	/// throws if the channel is exhausted.
	///
	/// @return MessageType if the value is in the channel and it hasn't yet
	/// been acquired, exception otherwise.
	///
	/// @remark Throws if the channel is exhausted.
	/// Prefer `try_receive()` instead.
	///
	MessageType receive() {
		// If the loop ends without returning from the body, that means
		// that someone else already acquired the value
		do {
			Optional<MessageType> msg = this->try_receive();

			if (msg.has_value()) {
				return msg.value();
			}
		}
		while (State::Acquired != state_.load(std::memory_order_acquire));

		throw std::runtime_error("Channel is exhausted.");
	}
};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_COMMUNICATION_ONESHOTCHANNEL_HXX
