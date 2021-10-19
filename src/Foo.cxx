#include <Nest/Version.hxx>
#include <fmt/core.h>

void print_version() {
	fmt::print("{}", NEST_VERSION);
}