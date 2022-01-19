#pragma once

#include "benchmark.h"
#include "common.h"
#include "competitors/compacted_compact_trie.h"

template <template <typename> typename Searcher>
void benchmark_32_compactedcompacttrie(
    sosd::Benchmark<uint32_t, Searcher>& benchmark, bool pareto) {
  benchmark.template Run<CompactedCompactTrie<uint32_t, 128>>();
  if (pareto) {
    benchmark.template Run<CompactedCompactTrie<uint32_t, 256>>();
    benchmark.template Run<CompactedCompactTrie<uint32_t, 512>>();
    benchmark.template Run<CompactedCompactTrie<uint32_t, 1024>>();
    benchmark.template Run<CompactedCompactTrie<uint32_t, 2048>>();
    benchmark.template Run<CompactedCompactTrie<uint32_t, 4096>>();
    benchmark.template Run<CompactedCompactTrie<uint32_t, 8192>>();
  }
}

template <template <typename> typename Searcher>
void benchmark_64_compactedcompacttrie(
    sosd::Benchmark<uint64_t, Searcher>& benchmark, bool pareto) {
  benchmark.template Run<CompactedCompactTrie<uint64_t, 128>>();
  if (pareto) {
    benchmark.template Run<CompactedCompactTrie<uint64_t, 256>>();
    benchmark.template Run<CompactedCompactTrie<uint64_t, 512>>();
    benchmark.template Run<CompactedCompactTrie<uint64_t, 1024>>();
    benchmark.template Run<CompactedCompactTrie<uint64_t, 2048>>();
    benchmark.template Run<CompactedCompactTrie<uint64_t, 4096>>();
    benchmark.template Run<CompactedCompactTrie<uint64_t, 8192>>();
  }
}

INSTANTIATE_TEMPLATES(benchmark_32_compactedcompacttrie, uint32_t);
INSTANTIATE_TEMPLATES(benchmark_64_compactedcompacttrie, uint64_t);
