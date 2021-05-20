#include "benchmarks/common.h"
#include "benchmarks/benchmark_cht.h"
#include "benchmark.h"
#include "competitors/cht.h"

template<template<typename> typename Searcher>
void benchmark_32_cht(sosd::Benchmark<uint32_t, Searcher>& benchmark, bool pareto) {
  benchmark.template Run<CHT<uint32_t, 1>>();
  if (pareto) {
    benchmark.template Run<CHT<uint32_t, 2>>();
    benchmark.template Run<CHT<uint32_t, 3>>();
    benchmark.template Run<CHT<uint32_t, 4>>();
    benchmark.template Run<CHT<uint32_t, 5>>();
    benchmark.template Run<CHT<uint32_t, 6>>();
    benchmark.template Run<CHT<uint32_t, 7>>();
    benchmark.template Run<CHT<uint32_t, 8>>();
    benchmark.template Run<CHT<uint32_t, 9>>();
    benchmark.template Run<CHT<uint32_t, 10>>();
  }
}


template<template<typename> typename Searcher>
void benchmark_64_cht(sosd::Benchmark<uint64_t, Searcher>& benchmark, bool pareto) {
  benchmark.template Run<CHT<uint64_t, 1>>();
  if (pareto) {
    benchmark.template Run<CHT<uint64_t, 2>>();
    benchmark.template Run<CHT<uint64_t, 3>>();
    benchmark.template Run<CHT<uint64_t, 4>>();
    benchmark.template Run<CHT<uint64_t, 5>>();
    benchmark.template Run<CHT<uint64_t, 6>>();
    benchmark.template Run<CHT<uint64_t, 7>>();
    benchmark.template Run<CHT<uint64_t, 8>>();
    benchmark.template Run<CHT<uint64_t, 9>>();
    benchmark.template Run<CHT<uint64_t, 10>>();
  }
}

INSTANTIATE_TEMPLATES(benchmark_32_cht, uint32_t);
INSTANTIATE_TEMPLATES(benchmark_64_cht, uint64_t);
