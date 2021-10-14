#include <Nest/Foo.hxx>
#include <fmt/core.h>


using namespace Nest;

namespace Nest {

void hello(std::string const& name) {
	fmt::print("Hello {}\n", name);
}

}	 // namespace Nest