#include <Nest/Core/Communication/Tunnel.hxx>
#include <Nest/Core/Communication/Concepts/Transmitter.hxx>
#include <Nest/Core/Communication/Concepts/Receiver.hxx>
#include <doctest/doctest.h>

#include <thread>
#include <chrono>

using namespace Nest;
using namespace std::chrono_literals;

TEST_CASE("TunnelCommunicationWorks") {
	auto [tx, rx] = Core::Tunnel<i32>::create(128);

	i32 sent = 42;
	tx.send(sent);
	i32 received = rx.receive();
	CHECK_EQ(sent, received);
}

void sender(Core::Concepts::Transmitter auto tx) {
	for (int i = 0; i < 100; ++i) {
		tx.send(i);
	}
}

void receiver(Core::Concepts::Receiver auto rx) {
	for (int i = 0; i < 100; ++i) {
		rx.receive();
		std::this_thread::sleep_for(500us);
	}
}

TEST_CASE("TunnelCommunicationBetween2Threads") {
	auto [tx, rx] = Core::Tunnel<i32>::create(50);

	std::thread producer([tx = std::move(tx)] () mutable { sender(std::move(tx)); });
	std::thread consumer([rx = std::move(rx)] () mutable { receiver(std::move(rx)); });

	producer.join();
	consumer.join();
}

