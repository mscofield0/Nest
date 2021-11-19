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

lib_include_dir = 'include'
lib_include_dirs = [lib_include_dir]

subdir('src')
subdir('include')

# =========== Dependencies
all_lib_deps = []

spdlog_dep = subproject('spdlog')
fmt_dep = subproject('fmt')

all_lib_deps += spdlog_dep
all_lib_deps += fmt_dep

# =========== Libraries
lib = library(
  meson.project_name(), 
  sources: all_lib_src,
  include_directories: lib_include_dirs,
  dependencies: app_lib_deps,
  install: true
)

libs = [lib]

# =========== Library export
lib_dep = declare_dependency(
  include_directories: lib_include_dirs,
  link_with: libs
)

install_headers(
  all_lib_headers, 
  subdir: lib_include_dir
)

pkg = import('pkgconfig')
pkg.generate(
  name: 'Nest',
  filebase: 'Nest',
  description: 'A C++ NES emulator library.',
  subdirs: lib_include_dirs,
  libraries: libs,
  version: meson.version(),
)

# =========== Test, benchmark and app enabling
if get_option('build-app')
  subdir('app')
endif
if get_option('enable-tests')
  doctest_dep = subproject('onqtam-doctest')
  subdir('tests')
endif
if get_option('enable-benchmark')
  benchmark = subproject('benchmark')
  subdir('benchmark')
endif
# if get_option('run-examples')
#   subdir('examples')
# endif

subdir('docs')

# =========== Generated headers
cdata = configuration_data()
cdata.set('PROJECT_NAME', meson.project_name())
cdata.set('UPPERCASE_PROJECT_NAME', meson.project_name().to_upper())
cdata.set('VERSION', meson.version())
cdata.set('VERSION_MAJOR', meson.version().get(0))
cdata.set('VERSION_MINOR', meson.version().get(1))
cdata.set('VERSION_PATCH', meson.version().get(2))
cdata.set('VERSION_TWEAK', meson.version().get(3))

configure_file(
  input: 'include/Version.hxx.in',
  output: 'include/Nest/Version.hxx',
  configuration: cdata,
	copy: true
)

configure_file(
  input: 'include/Export.hxx.in',
  output: 'include/Nest/Export.hxx',
  configuration: cdata,
	copy: true
)

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
    all_lib_headers
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
    'run-clang-tidy.py',
    '-fix', 
    '-j', '8', 
    'files', 
    '^((?!(third_party|tests|benchmarks|gtest)).)*$', 
    '-format', 
    '-p=' + meson.build_root()
  ]
)