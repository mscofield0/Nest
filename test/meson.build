# =========== Test bootstrap
test_bootstrap = files('Bootstrap.cxx')

# =========== Dependencies
test_deps = [
  lib_dep,
]

test_dep_libs = [
  lib,
]

doctest_dep = dependency('onqtam-doctest', 
  version: '2.4.0',
  fallback: ['onqtam-doctest', 'doctest_dep'],
)

test_deps += doctest_dep

# =========== Include the tests 
subdir('src')