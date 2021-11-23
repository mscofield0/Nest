# =========== Source files
foo_test_src = files(
  'FooTest.cxx',
)

# =========== Dependencies
foo_test_deps = []
foo_test_lib_deps = []

# =========== Generate executable
foo_test = executable('Foo_test', 
  sources: [test_bootstrap, foo_test_src], 
  include_directories: lib_include_dirs,
  dependencies: [test_deps, foo_test_deps],
  link_with: [test_dep_libs, foo_test_lib_deps],
)

# =========== Generate test
test('Foo test', foo_test)