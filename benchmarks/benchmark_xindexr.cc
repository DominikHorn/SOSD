#include "benchmarks/benchmark_xindexr.h"

#include "benchmark.h"
#include "common.h"
#include "competitors/xindex.h"

template <template <typename> typename Searcher>
void benchmark_32_xindex_r(sosd::Benchmark<uint32_t, Searcher>& benchmark,
                           bool pareto) {
  benchmark.template Run<XIndexR<uint32_t>>();
}

template <template <typename> typename Searcher>
void benchmark_64_xindex_r(sosd::Benchmark<uint64_t, Searcher>& benchmark,
                           bool pareto) {
  benchmark.template Run<XIndexR<uint64_t>>();
}

INSTANTIATE_TEMPLATES(benchmark_32_xindex_r, uint32_t);
INSTANTIATE_TEMPLATES(benchmark_64_xindex_r, uint64_t);
