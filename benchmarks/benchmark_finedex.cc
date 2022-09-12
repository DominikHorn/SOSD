#include "benchmarks/benchmark_finedex.h"

#include "benchmark.h"
#include "common.h"
#include "competitors/finedex.h"

template <template <typename> typename Searcher>
void benchmark_32_finedex(sosd::Benchmark<uint32_t, Searcher>& benchmark,
                          bool pareto) {
  benchmark.template Run<FINEdex<uint32_t, 1>>();
  if (pareto) {
    benchmark.template Run<FINEdex<uint32_t, 4>>();
    benchmark.template Run<FINEdex<uint32_t, 8>>();
    benchmark.template Run<FINEdex<uint32_t, 16>>();
    benchmark.template Run<FINEdex<uint32_t, 32>>();
    benchmark.template Run<FINEdex<uint32_t, 64>>();
    benchmark.template Run<FINEdex<uint32_t, 128>>();
    benchmark.template Run<FINEdex<uint32_t, 256>>();
    benchmark.template Run<FINEdex<uint32_t, 512>>();
    benchmark.template Run<FINEdex<uint32_t, 1024>>();
    benchmark.template Run<FINEdex<uint32_t, 2048>>();
    if (benchmark.uses_binary_search()) {
      benchmark.template Run<FINEdex<uint32_t, 4096>>();
      benchmark.template Run<FINEdex<uint32_t, 8192>>();
    }
  }
}

template <template <typename> typename Searcher>
void benchmark_64_finedex(sosd::Benchmark<uint64_t, Searcher>& benchmark,
                          bool pareto) {
  benchmark.template Run<FINEdex<uint64_t, 1>>();
  if (pareto) {
    benchmark.template Run<FINEdex<uint64_t, 4>>();
    benchmark.template Run<FINEdex<uint64_t, 8>>();
    benchmark.template Run<FINEdex<uint64_t, 16>>();
    benchmark.template Run<FINEdex<uint64_t, 32>>();
    benchmark.template Run<FINEdex<uint64_t, 64>>();
    benchmark.template Run<FINEdex<uint64_t, 128>>();
    benchmark.template Run<FINEdex<uint64_t, 256>>();
    benchmark.template Run<FINEdex<uint64_t, 512>>();
    benchmark.template Run<FINEdex<uint64_t, 1024>>();
    benchmark.template Run<FINEdex<uint64_t, 2048>>();
    if (benchmark.uses_binary_search()) {
      benchmark.template Run<FINEdex<uint64_t, 4096>>();
      benchmark.template Run<FINEdex<uint64_t, 8192>>();
    }
  }
}

INSTANTIATE_TEMPLATES(benchmark_32_finedex, uint32_t);
INSTANTIATE_TEMPLATES(benchmark_64_finedex, uint64_t);
