# =========== Source files
all_app_src = []
all_app_headers = []
app_bootstrap = files('Bootstrap.cxx')

all_app_src += app_bootstrap

app_include_dir = include_directories('include')
app_include_dirs = [lib_include_dirs, app_include_dir]

subdir('src')
subdir('include')

# =========== Dependencies
all_app_deps = []
all_app_dep_libs = []

thread_dep = dependency('threads')

all_app_deps += [
  thread_dep
]

# =========== Build app
app = executable(meson.project_name(), 
  sources: all_app_src, 
  include_directories: app_include_dirs, 
  dependencies: all_app_deps, 
  link_with: all_app_dep_libs
)