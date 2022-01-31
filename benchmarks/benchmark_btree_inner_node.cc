#include "benchmarks/benchmark_btree_inner_node.h"

#include "benchmark.h"
#include "common.h"
#include "competitors/btree_inner_node.h"

template <template <typename> typename Searcher>
void benchmark_32_btree_inner_node(
    sosd::Benchmark<uint32_t, Searcher>& benchmark, bool pareto) {
  benchmark.template Run<BTreeInnerNode<uint32_t, 2>>();
  if (pareto) {
    benchmark.template Run<BTreeInnerNode<uint32_t, 4>>();
    benchmark.template Run<BTreeInnerNode<uint32_t, 8>>();
    benchmark.template Run<BTreeInnerNode<uint32_t, 16>>();
    benchmark.template Run<BTreeInnerNode<uint32_t, 32>>();
    benchmark.template Run<BTreeInnerNode<uint32_t, 64>>();
    benchmark.template Run<BTreeInnerNode<uint32_t, 128>>();
    benchmark.template Run<BTreeInnerNode<uint32_t, 256>>();
    benchmark.template Run<BTreeInnerNode<uint32_t, 512>>();
    benchmark.template Run<BTreeInnerNode<uint32_t, 1024>>();
    benchmark.template Run<BTreeInnerNode<uint32_t, 2048>>();
    benchmark.template Run<BTreeInnerNode<uint32_t, 4096>>();
    benchmark.template Run<BTreeInnerNode<uint32_t, 8192>>();
    benchmark.template Run<BTreeInnerNode<uint32_t, 16384>>();
  }
}

template <template <typename> typename Searcher>
void benchmark_64_btree_inner_node(
    sosd::Benchmark<uint64_t, Searcher>& benchmark, bool pareto) {
  benchmark.template Run<BTreeInnerNode<uint64_t, 2>>();
  if (pareto) {
    benchmark.template Run<BTreeInnerNode<uint64_t, 4>>();
    benchmark.template Run<BTreeInnerNode<uint64_t, 8>>();
    benchmark.template Run<BTreeInnerNode<uint64_t, 16>>();
    benchmark.template Run<BTreeInnerNode<uint64_t, 32>>();
    benchmark.template Run<BTreeInnerNode<uint64_t, 64>>();
    benchmark.template Run<BTreeInnerNode<uint64_t, 128>>();
    benchmark.template Run<BTreeInnerNode<uint64_t, 256>>();
    benchmark.template Run<BTreeInnerNode<uint64_t, 512>>();
    benchmark.template Run<BTreeInnerNode<uint64_t, 1024>>();
    benchmark.template Run<BTreeInnerNode<uint64_t, 2048>>();
    benchmark.template Run<BTreeInnerNode<uint64_t, 4096>>();
    benchmark.template Run<BTreeInnerNode<uint64_t, 8192>>();
    benchmark.template Run<BTreeInnerNode<uint64_t, 16384>>();
  }
}

INSTANTIATE_TEMPLATES(benchmark_32_btree_inner_node, uint32_t);
INSTANTIATE_TEMPLATES(benchmark_64_btree_inner_node, uint64_t);
