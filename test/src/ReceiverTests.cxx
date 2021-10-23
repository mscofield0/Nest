#include <Nest/Core/Communication/Channel.hxx>
#include <Nest/Core/Communication/Transmitter.hxx>
#include <Nest/Core/Communication/Receiver.hxx>
#include <doctest/doctest.h>

#include <memory>

using namespace Nest;

TEST_CASE("ReceiverReceiveWorks") {
	auto channel = std::make_shared<Core::Channel<i32>>(20);

	Core::Transmitter tx(channel);
	i32 sent = 42;
	tx.send(sent);
	Core::Receiver rx(channel);
	i32 received = rx.receive();
	CHECK_EQ(sent, received);
}

TEST_CASE("ReceiverTryReceiveWorks") {
	auto channel = std::make_shared<Core::Channel<i32>>(20);

	Core::Transmitter tx(channel);
	i32 sent = 42;
	tx.send(sent);
	Core::Receiver rx(channel);
	i32 received = rx.receive();
	CHECK_EQ(sent, received);
}
