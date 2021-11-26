# =========== Source files
example_foo_main = files('Main.cxx')

examples_src += example_foo_main

# =========== Dependencies
example_foo_deps = []
example_foo_dep_libs = []

subdir('deps')

# =========== Build app
example_foo = executable('foo', 
  sources: example_foo_main, 
  dependencies: example_foo_deps, 
  link_with: example_foo_dep_libs
)