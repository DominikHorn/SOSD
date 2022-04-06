#pragma once

#include "benchmark.h"
#include "common.h"
#include "competitors/compacted_compact_trie.h"

template <template <typename> typename Searcher>
void benchmark_32_compactedcompacttrie(
    sosd::Benchmark<uint32_t, Searcher>& benchmark, bool pareto) {
  benchmark.template Run<CompactedCompactTrie<uint32_t, 1>>();
  if (pareto) {
    benchmark.template Run<CompactedCompactTrie<uint32_t, 2>>();
    benchmark.template Run<CompactedCompactTrie<uint32_t, 4>>();
    benchmark.template Run<CompactedCompactTrie<uint32_t, 8>>();
    benchmark.template Run<CompactedCompactTrie<uint32_t, 16>>();
    benchmark.template Run<CompactedCompactTrie<uint32_t, 32>>();
    benchmark.template Run<CompactedCompactTrie<uint32_t, 64>>();
    benchmark.template Run<CompactedCompactTrie<uint32_t, 128>>();
  }
}

template <template <typename> typename Searcher>
void benchmark_64_compactedcompacttrie(
    sosd::Benchmark<uint64_t, Searcher>& benchmark, bool pareto) {
  benchmark.template Run<CompactedCompactTrie<uint64_t, 1>>();
  if (pareto) {
    benchmark.template Run<CompactedCompactTrie<uint64_t, 2>>();
    benchmark.template Run<CompactedCompactTrie<uint64_t, 4>>();
    benchmark.template Run<CompactedCompactTrie<uint64_t, 8>>();
    benchmark.template Run<CompactedCompactTrie<uint64_t, 16>>();
    benchmark.template Run<CompactedCompactTrie<uint64_t, 32>>();
    benchmark.template Run<CompactedCompactTrie<uint64_t, 64>>();
    benchmark.template Run<CompactedCompactTrie<uint64_t, 128>>();
  }
}

INSTANTIATE_TEMPLATES(benchmark_32_compactedcompacttrie, uint32_t);
INSTANTIATE_TEMPLATES(benchmark_64_compactedcompacttrie, uint64_t);
