#pragma once

#include <algorithm>
#include <exotic_hashing.hpp>
#include <string>

#include "../util.h"
#include "base.h"

template <class KeyType, int size_scale>
class CompactedCompactTrie : public Competitor {
  exotic_hashing::CompactedCompactTrie<
      KeyType, exotic_hashing::support::FixedBitConverter<KeyType>>
      compact_trie;
  size_t keycnt;

 public:
  uint64_t Build(const std::vector<KeyValue<KeyType>>& data) {
    // we only need the keys
    std::vector<KeyType> keys;
    keys.reserve(data.size() / size_scale);

    for (const auto& kv : data) {
      if (size_scale > 1 && kv.value % size_scale != 0) continue;
      keys.push_back(kv.key);
    }

    keycnt = keys.size();

    return util::timing(
        [&] { compact_trie.construct(keys.begin(), keys.end()); });
  }

  SearchBound EqualityLookup(const KeyType lookup_key) const {
    // special case, constexpr ensures that the compiler evaluates this
    // expression
    if constexpr (size_scale == 1) {
      const auto rank = compact_trie(lookup_key);
      return {rank, rank};
    } else {
      const auto guess = compact_trie(lookup_key) * size_scale;

      const size_t error = size_scale;
      const size_t start = (guess >= error) * (guess - error);
      const size_t stop = std::min(guess + error + 1, keycnt);

      return {start, stop};
    }
  }

  std::string name() const { return "CompactTrie"; }

  std::size_t size() const { return compact_trie.byte_size(); }

  bool applicable(bool _unique, const std::string& data_filename) {
    return true;
  }

  int variant() const { return 0; }
};
