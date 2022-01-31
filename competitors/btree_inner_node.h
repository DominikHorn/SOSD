#pragma once

#include <algorithm>

#include "base.h"

/**
 * Inner node of a btree, i.e., only partially indexes keys
 * and utilizes binary search to find lower bound
 *
 * KeyType: type of key
 * size_scale: only every size_scale-th parameter will be indexed
 */
template <class KeyType, int size_scale>
class BTreeInnerNode : public Competitor {
  std::vector<KeyType> repr;
  size_t data_size;

 public:
  uint64_t Build(const std::vector<KeyValue<KeyType>>& data) {
    data_size = data.size();

    return util::timing([&] {
      repr.reserve((data.size() + 1) / size_scale);

      for (size_t i = 0; i < data.size(); i += size_scale)
        repr.push_back(data[i].key);
    });
  }

  SearchBound EqualityLookup(const KeyType lookup_key) const {
    const auto lb_iter = std::lower_bound(repr.begin(), repr.end(), lookup_key);
    if (lb_iter == repr.end()) return {0, data_size};

    const size_t lb = std::distance(repr.begin(), lb_iter) * size_scale;

    // Option 1: lookup_key is exactly at lb
    if (*lb_iter == lookup_key) return {lb, lb + 1};

    // Option 2: lookup_key is in the size_scale interval before (including) lb
    // (lb points to first elem greater than)
    return {lb - size_scale, lb};
  }

  std::string name() const { return "BTreeInnerNode"; }

  std::size_t size() const {
    return repr.size() * sizeof(typename decltype(repr)::value_type);
  }

  bool applicable(bool unique, const std::string& data_filename) {
    return true;
  }

  int variant() const { return size_scale; }
};
