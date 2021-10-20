#include <Nest/Core/Communication/Channel.hxx>
#include <Nest/Core/Communication/Transmitter.hxx>
#include <doctest/doctest.h>

#include <memory>

using namespace Nest;

TEST_CASE("TransmitterSendWorks") {
	auto channel = std::make_shared<Core::Channel<i32>>(20);

	Core::Transmitter<i32> tx(channel);
	i32 sent = 42;
	tx.send(sent);
	i32 received = channel->receive();
	CHECK_EQ(sent, received);
}

TEST_CASE("TransmitterTrySendWorks") {
	auto channel = std::make_shared<Core::Channel<i32>>(20);

	Core::Transmitter<i32> tx(channel);
	i32 sent = 42;
	tx.try_send(sent);
	i32 received = channel->receive();
	CHECK_EQ(sent, received);
}
