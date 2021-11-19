# =========== Source files
all_app_src = []
all_app_headers = []
app_bootstrap = files('Bootstrap.cxx')

all_app_src += app_bootstrap

app_include_dir = 'include'
app_include_dirs = [lib_include_dirs, app_include_dir]

subdir('src')
subdir('include')

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
  include_directories: app_include_dirs, 
  dependencies: all_test_deps, 
  link_with: all_test_dep_libs
)