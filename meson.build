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
lib_src = []
lib_headers = []

lib_include_dir = include_directories('include')
lib_include_dirs = [lib_include_dir]

subdir('src')
subdir('include')

# =========== Dependencies
lib_deps = []

spdlog_dep = dependency('spdlog', 
  version: '1.9.2',
  fallback: ['spdlog', 'spdlog_dep']
)

fmt_dep = dependency('fmt',
  version: '8.0.1',
  fallback: ['fmt', 'fmt_dep']
)

lib_deps += spdlog_dep
lib_deps += fmt_dep

# =========== Libraries
lib = library(
  meson.project_name(), 
  sources: lib_src,
  include_directories: lib_include_dirs,
  dependencies: lib_deps,
  install: true,
)

libs = [lib]

# =========== Library export
lib_dep = declare_dependency(
  include_directories: lib_include_dirs,
  link_with: libs,
)

install_headers(
  lib_headers, 
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
subdir('test')
subdir('app')
subdir('benchmark')
subdir('examples')
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
    lib_src,
    lib_headers,
    app_src,
    app_headers,
    benchmark_src,
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
    '^((?!(test|benchmark)).)*$', 
    '-format', 
    '-p=' + meson.build_root()
  ]
)