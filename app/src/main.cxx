#include <Nest/Foo.hxx>
#include <Nest/Version.hxx>

int main(int argc, char** argv) {
	Nest::hello(argv[1]);

	int* ptr = new int(42);
}
