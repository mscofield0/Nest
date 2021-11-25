#include <doctest.h>

#include <Nest/Foo.hxx>

using Nest::hello;

TEST_CASE("FooTest") {
	CHECK_EQ(hello("Bruce"), "Bruce");
}