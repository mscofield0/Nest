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

# =========== Source files
lib_src = []
lib_headers = []

lib_include_dir = include_directories('include')
lib_include_dirs = [lib_include_dir]

subdir('src')
subdir('include')

# =========== Dependencies
lib_deps = []

subdir('deps')

# =========== Project definitions
lib_args = ['-DBUILDING_NEST']

# =========== Libraries
lib = library(
  meson.project_name(), 
  sources: lib_src,
  include_directories: lib_include_dirs,
  dependencies: lib_deps,
  install: true,
  cpp_args: lib_args,
)

libs = [lib]

# =========== Library export
lib_dep = declare_dependency(
  include_directories: lib_include_dirs,
  link_with: libs,
)

if get_option('BUILD_WITH_INSTALLED')
  lib_dep_for_tests = dependency(meson.project_name(), allow_fallback: false)
else
  lib_dep_for_tests = lib_dep
endif

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
if not meson.is_subproject()
  subdir('test')
  subdir('app')
  subdir('benchmark')
  subdir('examples')
  subdir('docs')
endif

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