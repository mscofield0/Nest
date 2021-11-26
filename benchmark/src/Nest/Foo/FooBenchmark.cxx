#include <benchmark/benchmark.h>

static void BM_FOO(benchmark::State& state) {
	int count = 0;
	for (auto _ : state) ++count;
}

// Register the function as a benchmark
BENCHMARK(BM_FOO);