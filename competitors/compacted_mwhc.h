#pragma once

#include <algorithm>
#include <exotic_hashing.hpp>
#include <string>

#include "../util.h"
#include "base.h"

template <class KeyType>
class CompactedMWHC : public Competitor {
  exotic_hashing::CompactedMWHC<KeyType> mwhc;

 public:
  uint64_t Build(const std::vector<KeyValue<KeyType>>& data) {
    // we only need the keys
    std::vector<KeyType> keys;
    keys.reserve(data.size());
    std::transform(data.begin(), data.end(), std::back_inserter(keys),
                   [](const KeyValue<KeyType>& kv) { return kv.key; });

    return util::timing([&] { mwhc.construct(keys.begin(), keys.end()); });
  }

  SearchBound EqualityLookup(const KeyType lookup_key) const {
    const auto rank = mwhc(lookup_key);
    return {rank, rank};
  }

  std::string name() const { return "CompactedMWHC"; }

  std::size_t size() const { return mwhc.byte_size(); }

  bool applicable(bool _unique, const std::string& data_filename) {
    return _unique;
  }

  int variant() const { return 0; }
};
