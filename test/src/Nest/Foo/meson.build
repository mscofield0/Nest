# =========== Source files
foo_test_src = files(
  'Foo.cxx',
)

test_src += foo_test_src

# =========== Dependencies
foo_test_deps = []
foo_test_lib_deps = []

subdir('deps')

# =========== Generate executable
foo_test = executable('Foo_test', 
  sources: [test_bootstrap, foo_test_src], 
  include_directories: lib_include_dirs,
  dependencies: [test_deps, foo_test_deps],
  link_with: [test_dep_libs, foo_test_lib_deps],
)

# =========== Generate test
test('Foo', foo_test)