#include <Nest/Core/Communication/Concepts/Receiver.hxx>
#include <Nest/Core/Communication/Concepts/Transmitter.hxx>
#include <Nest/Core/Communication/Oneshot.hxx>
#include <doctest/doctest.h>

#include <future>
#include <thread>
#include <chrono>

using namespace Nest;
using namespace std::chrono_literals;

TEST_CASE("OneshotCommunicationWorks") {
	auto [tx, rx] = Core::Oneshot<i32>::create();

	i32 sent = 42;
	tx.send(sent);
	i32 received = rx.receive();
	CHECK_EQ(sent, received);
}

void sender(Core::Concepts::Transmitter auto tx) {
	// Sleep so that the receiver blocks for a bit
	std::this_thread::sleep_for(200ms);
	tx.send(42);

	// Check return-value correctness for already fired channel
	CHECK(!tx.try_send(1));

	// Check throw correctness with already fired channel
	CHECK_THROWS_WITH(tx.send(2), "Already sent a message to the Oneshot channel.");
}

void receiver(Core::Concepts::Receiver auto rx) {
	// Check receive correctness with non-exhausted channel
	auto msg = rx.receive();
	CHECK_EQ(msg, 42);

	// Check return-value correctness with exhausted channel
	auto invalid_msg = rx.try_receive();
	CHECK(!invalid_msg.has_value());

	// Check throw correctness with exhausted channel
	CHECK_THROWS_WITH(rx.receive(), "Channel is exhausted.");
}

TEST_CASE("OneshotCommunicationBetween2Threads") {
	auto [tx, rx] = Core::Oneshot<i32>::create();

	std::thread producer(
	  [tx = std::move(tx)]() mutable { sender(std::move(tx)); });
	std::thread consumer(
	  [rx = std::move(rx)]() mutable { receiver(std::move(rx)); });

	producer.join();
	consumer.join();
}
