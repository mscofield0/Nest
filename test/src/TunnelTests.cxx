#include <Nest/Core/Communication/Tunnel.hxx>
#include <doctest/doctest.h>

using namespace Nest;

TEST_CASE("TunnelCommunicationWorks") {
	auto [tx, rx] = Core::Tunnel<i32>::create(128);

	i32 sent = 42;
	tx.send(sent);
	i32 received = rx.receive();
	CHECK_EQ(sent, received);
}
