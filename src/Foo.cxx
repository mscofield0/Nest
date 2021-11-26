#include <Nest/Foo.hxx>
#include <fmt/core.h>

std::string hello(std::string const& name) {
    return fmt::format("Hello {}", name);
}
