# =========== Source files
all_benchmark_src = []
benchmark_bootstrap = files('Bootstrap.cxx')

all_benchmark_src += benchmark_bootstrap

subdir('src')

# =========== Dependencies
all_benchmark_deps = []
all_benchmark_dep_libs = []

benchmark_dep = dependency('google-benchmark', fallback: ['google-benchmark', 'google_benchmark_dep'])
thread_dep = dependency('threads')

all_benchmark_deps += [
    benchmark_dep,
    thread_dep
]

# =========== Build benchmark
all_benchmarks = executable('all_benchmarks',
  sources: all_benchmark_src,
  include_directories: lib_include_dirs,
  dependencies: all_benchmark_deps,
  link_with: all_benchmark_dep_libs
)