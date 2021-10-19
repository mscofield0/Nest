#include <Nest/Version.hxx>
#include <Nest/Core/Communication/Tunnel.hxx>
#include <fmt/core.h>

void print_version() {
	fmt::print("{}", NEST_VERSION);

    auto [tx, rx] = Nest::Core::Tunnel<int>::create(128);
}