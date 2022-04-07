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
    benchmark.template Run<SFMWHC<uint32_t, 20>>();
    benchmark.template Run<SFMWHC<uint32_t, 22>>();
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
    benchmark.template Run<SFMWHC<uint64_t, 20>>();
    benchmark.template Run<SFMWHC<uint64_t, 22>>();
  }
}

INSTANTIATE_TEMPLATES(benchmark_32_sfmwhc, uint32_t);
INSTANTIATE_TEMPLATES(benchmark_64_sfmwhc, uint64_t);
