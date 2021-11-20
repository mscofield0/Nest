project(
  'Nest', 
  'cpp',
  version: '0.1.0.0',
  default_options: [
    'default_library=shared',
    'buildtype=debugoptimized',
    'warning_level=3', 
    'cpp_std=c++2a'
  ]
)

# =========== Project definitions
lib_args = ['-DBUILDING_NEST']

# =========== Source files
all_lib_src = []
all_lib_headers = []
all_test_src  = []
all_benchmark_src = []

lib_include_dir = include_directories('include')
lib_include_dirs = [lib_include_dir]

subdir('src')
subdir('include')

# =========== Dependencies
all_lib_deps = []

spdlog_dep = dependency('spdlog', 
  version: '1.9.2',
  fallback: ['spdlog', 'spdlog_dep']
)

fmt_dep = dependency('fmt',
  version: '8.0.1',
  fallback: ['fmt', 'fmt_dep']
)

all_lib_deps += spdlog_dep
all_lib_deps += fmt_dep

# =========== Libraries
lib = library(
  meson.project_name(), 
  sources: all_lib_src,
  include_directories: lib_include_dirs,
  dependencies: all_lib_deps,
  install: true,
)

libs = [lib]

# =========== Library export
lib_dep = declare_dependency(
  include_directories: lib_include_dirs,
  link_with: libs,
)

install_headers(
  all_lib_headers, 
  subdir: 'include',
)

pkg = import('pkgconfig')
pkg.generate(
  name: 'Nest',
  filebase: 'Nest',
  description: 'A C++ NES emulator library.',
  subdirs: 'Nest',
  libraries: libs,
  version: meson.project_version(),
)

# =========== Test, benchmark and app enabling
subdir('app')
subdir('test')
subdir('benchmark')
# if get_option('run-examples')
#   subdir('examples')
# endif

subdir('docs')

# =========== Formatting target
configure_file(
  input: '.clang-format',
  output: '.clang-format',
	copy: true
)

run_target('format',
  command: [
    'clang-format', '-i', '-style=file',
    all_lib_src,
    all_lib_headers,
    all_test_src,
    all_benchmark_src,
  ]
)

# =========== clang-tidy target
configure_file(
  input: '.clang-tidy',
  output: '.clang-tidy',
  copy: true
)

run_target('tidy',
  command: [
    'run-clang-tidy',
    '-fix', 
    '-j', '8', 
    'files', 
    '^((?!(third_party|tests|benchmarks|gtest)).)*$', 
    '-format', 
    '-p=' + meson.build_root()
  ]
)