# =========== Source files
app_src = []
app_headers = []
app_bootstrap = files('Bootstrap.cxx')

app_src += app_bootstrap

app_include_dir = include_directories('include')
app_include_dirs = [lib_include_dirs, app_include_dir]

subdir('src')
subdir('include')

# =========== Dependencies
app_deps = []
app_dep_libs = []

# =========== Build app
app = executable(meson.project_name(), 
  sources: app_src, 
  include_directories: app_include_dirs, 
  dependencies: app_deps, 
  link_with: app_dep_libs
)