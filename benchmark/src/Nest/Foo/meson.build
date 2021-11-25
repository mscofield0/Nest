# =========== Source files
foo_benchmark_src = files(
  'FooTest.cxx',
)

# =========== Dependencies
foo_test_deps = []
foo_test_lib_deps = []

subdir('deps')

# =========== Generate executable
foo_benchmark = executable('Foo_test', 
  sources: [benchmark_bootstrap, foo_benchmark_src], 
  include_directories: lib_include_dirs,
  dependencies: [benchmark_deps, foo_benchmark_deps],
  link_with: [benchmark_dep_libs, foo_benchmark_lib_deps],
)

# =========== Generate test
benchmark('Foo', foo_benchmark)