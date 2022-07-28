#pragma once

#include <vector>

#include "base.h"
#include "xindex/XIndex-R/xindex.h"
#include "xindex/XIndex-R/xindex_impl.h"

template <class KeyType, int size_scale>
class XIndexR : public Competitor {
  using XIndexType = xindex::XIndex<KeyType, size_t>;
  std::unique_ptr<XIndexType> xindex_ptr_;

  size_t data_size_;

 public:
  XIndexR() {}

  uint64_t Build(const std::vector<KeyValue<KeyType>>& data) {
    const auto N = data.size() / size_scale;
    std::vector<KeyType> keys;
    std::vector<size_t> indices;

    keys.reserve(N);
    indices.reserve(N);

    for (const auto& iter : data) {
      uint64_t idx = iter.value;
      if (size_scale > 1 && idx % size_scale != 0) continue;

      keys.push_back(iter.key);
      indices.push_back(idx);
    }
    data_size_ = data.size();

    return util::timing([&]() {
      xindex_ptr_ = std::make_unique<XIndexType>(keys, indices,
                                                 /*worker_num=*/1, /*bg_n=*/0);
    });
  }

  SearchBound EqualityLookup(const KeyType lookup_key) const {
    KeyType key;
    size_t index;
    if (!xindex_ptr_->get(key, index, 0)) return (SearchBound){0, data_size_};

    const uint64_t error = size_scale - 1;

    const uint64_t start = index < error ? 0 : index - error;
    const uint64_t stop = index + 1 > data_size_
                              ? data_size_
                              : index + 1;  // stop is exclusive (that's why +1)

    return (SearchBound){start, stop};
  }

  std::string name() const { return "XIndex-R"; }

  std::size_t size() const {
    // TODO(dominik): implement. This will require patching XIndex-R's source
    // code unfortunately
    return -1;
  }
}
