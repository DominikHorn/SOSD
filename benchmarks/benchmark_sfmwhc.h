#pragma once

#include "benchmark.h"
#include "common.h"
#include "competitors/sf_mwhc.h"

template <template <typename> typename Searcher>
void benchmark_32_sfmwhc(sosd::Benchmark<uint32_t, Searcher>& benchmark,
                         bool pareto) {
  benchmark.template Run<SFMWHC<uint32_t, 0>>();
  if (pareto) {
    benchmark.template Run<SFMWHC<uint32_t, 1>>();
    benchmark.template Run<SFMWHC<uint32_t, 2>>();
    benchmark.template Run<SFMWHC<uint32_t, 4>>();
    benchmark.template Run<SFMWHC<uint32_t, 8>>();
    benchmark.template Run<SFMWHC<uint32_t, 16>>();
    benchmark.template Run<SFMWHC<uint32_t, 18>>();
    benchmark.template Run<SFMWHC<uint32_t, 20>>();
  }
}

template <template <typename> typename Searcher>
void benchmark_64_sfmwhc(sosd::Benchmark<uint64_t, Searcher>& benchmark,
                         bool pareto) {
  benchmark.template Run<SFMWHC<uint64_t, 0>>();
  if (pareto) {
    benchmark.template Run<SFMWHC<uint64_t, 1>>();
    benchmark.template Run<SFMWHC<uint64_t, 2>>();
    benchmark.template Run<SFMWHC<uint64_t, 4>>();
    benchmark.template Run<SFMWHC<uint64_t, 8>>();
    benchmark.template Run<SFMWHC<uint64_t, 16>>();
    benchmark.template Run<SFMWHC<uint64_t, 18>>();
    benchmark.template Run<SFMWHC<uint64_t, 20>>();
    benchmark.template Run<SFMWHC<uint64_t, 22>>();
    benchmark.template Run<SFMWHC<uint64_t, 24>>();
    benchmark.template Run<SFMWHC<uint64_t, 26>>();
    benchmark.template Run<SFMWHC<uint64_t, 28>>();
    benchmark.template Run<SFMWHC<uint64_t, 30>>();
    benchmark.template Run<SFMWHC<uint64_t, 32>>();
    benchmark.template Run<SFMWHC<uint64_t, 34>>();
    benchmark.template Run<SFMWHC<uint64_t, 36>>();
    benchmark.template Run<SFMWHC<uint64_t, 38>>();
    benchmark.template Run<SFMWHC<uint64_t, 40>>();
    benchmark.template Run<SFMWHC<uint64_t, 42>>();
    benchmark.template Run<SFMWHC<uint64_t, 44>>();
    benchmark.template Run<SFMWHC<uint64_t, 46>>();
    benchmark.template Run<SFMWHC<uint64_t, 48>>();
  }
}

INSTANTIATE_TEMPLATES(benchmark_32_sfmwhc, uint32_t);
INSTANTIATE_TEMPLATES(benchmark_64_sfmwhc, uint64_t);
