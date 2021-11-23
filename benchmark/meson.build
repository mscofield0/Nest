# =========== Source files
benchmark_src = []
benchmark_bootstrap = files('Bootstrap.cxx')

benchmark_src += benchmark_bootstrap

subdir('src')

# =========== Dependencies
benchmark_deps = []
benchmark_dep_libs = []

benchmark_dep = dependency('google-benchmark', 
  version: '1.5.2',
  fallback: ['google-benchmark', 'google_benchmark_main_dep']
)

thread_dep = dependency('threads')

benchmark_deps += [
    benchmark_dep,
    thread_dep
]

# =========== Build benchmark
all_benchmarks = executable('all_benchmarks',
  sources: benchmark_src,
  include_directories: lib_include_dirs,
  dependencies: benchmark_deps,
  link_with: benchmark_dep_libs
)