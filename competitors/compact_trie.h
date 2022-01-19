#pragma once

#include <algorithm>
#include <exotic_hashing.hpp>
#include <string>

#include "../util.h"
#include "base.h"

template <class KeyType>
class CompactTrie : public Competitor {
  exotic_hashing::CompactTrie<
      KeyType, exotic_hashing::support::FixedBitConverter<KeyType>>
      compact_trie;

 public:
  uint64_t Build(const std::vector<KeyValue<KeyType>>& data) {
    // we only need the keys
    std::vector<KeyType> keys;
    keys.reserve(data.size());
    std::transform(data.begin(), data.end(), std::back_inserter(keys),
                   [](const KeyValue<KeyType>& kv) { return kv.key; });

    return util::timing(
        [&] { compact_trie.construct(keys.begin(), keys.end()); });
  }

  SearchBound EqualityLookup(const KeyType lookup_key) const {
    const auto rank = compact_trie(lookup_key);
    return {rank, rank};
  }

  std::string name() const { return "CompactTrie"; }

  std::size_t size() const { return compact_trie.byte_size(); }

  bool applicable(bool _unique, const std::string& data_filename) {
    return true;
  }

  int variant() const { return 0; }
};
