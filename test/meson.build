# =========== Source files
all_test_src = []
test_bootstrap = files('Bootstrap.cxx')

all_test_src += test_bootstrap

subdir('src')

# =========== Dependencies
all_test_deps = []
all_test_dep_libs = []

thread_dep = dependency('threads')

all_test_deps += [
    doctest_dep, 
    thread_dep
]

# =========== Build tests
all_tests = executable('all_tests', 
  sources: all_test_src, 
  include_directories: lib_include_dirs, 
  dependencies: all_test_deps, 
  link_with: all_test_dep_libs
)