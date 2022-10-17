#pragma once

#include <vector>

#include "base.h"
#include "xindex/XIndex-R/xindex.h"
#include "xindex/XIndex-R/xindex_impl.h"

template <class SOSDKey, int size_scale>
class XIndexR : public Competitor {
  class XIndexKey {
    typedef std::array<double, 1> model_key_t;

   public:
    static constexpr size_t model_key_size() { return 1; }

    static XIndexKey max() {
      static XIndexKey max_key(std::numeric_limits<SOSDKey>::max());
      return max_key;
    }

    static XIndexKey min() {
      static XIndexKey min_key(std::numeric_limits<SOSDKey>::min());
      return min_key;
    }

    XIndexKey() : key(0) {}
    XIndexKey(SOSDKey key) : key(key) {}
    XIndexKey(const XIndexKey& other) { key = other.key; }
    XIndexKey& operator=(const XIndexKey& other) {
      key = other.key;
      return *this;
    }

    model_key_t to_model_key() const {
      model_key_t model_key;
      model_key[0] = key;
      return model_key;
    }

    friend bool operator<(const XIndexKey& l, const XIndexKey& r) {
      return l.key < r.key;
    }
    friend bool operator>(const XIndexKey& l, const XIndexKey& r) {
      return l.key > r.key;
    }
    friend bool operator>=(const XIndexKey& l, const XIndexKey& r) {
      return l.key >= r.key;
    }
    friend bool operator<=(const XIndexKey& l, const XIndexKey& r) {
      return l.key <= r.key;
    }
    friend bool operator==(const XIndexKey& l, const XIndexKey& r) {
      return l.key == r.key;
    }
    friend bool operator!=(const XIndexKey& l, const XIndexKey& r) {
      return l.key != r.key;
    }

    SOSDKey key;
  } PACKED;

  using XIndexType = xindex::XIndex<XIndexKey, size_t>;
  std::unique_ptr<XIndexType> xindex_ptr_;

  size_t data_size_;

 public:
  XIndexR() {}

  uint64_t Build(const std::vector<KeyValue<SOSDKey>>& data) {
    const auto N = data.size() / size_scale;
    std::vector<XIndexKey> keys;
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

      // The interface we're using suggests that it does a batch insert. Ideally
      // we'd want to force adjustment just to be sure we have the optimal
      // xindex setup. Unfortunately however, this seems to take exponentially
      // longer than the construction itself. (never observed to finish on a
      // 200M item data set)
      // xindex_ptr_->force_adjustment_sync();
    });
  }

  SearchBound EqualityLookup(const SOSDKey lookup_key) const {
    std::vector<std::pair<XIndexKey, size_t>> result;
    if (xindex_ptr_->scan(lookup_key, 1, result, 0) != 0)
      return (SearchBound){0, data_size_};
    const auto pred = result.front().second;

    const uint64_t error = size_scale - 1;
    const uint64_t start = pred - std::min(pred, error);
    // +1 since stop is exclusive
    const uint64_t stop = std::min(pred + error + 1, data_size_);

    return (SearchBound){start, stop};
  }

  std::string name() const { return "XIndex-R"; }

  std::size_t size() const {
    const auto size = xindex_ptr_->byte_size();

    std::cout << "ALLOCATED: " << xindex::_::allocated_bytes << std::endl;
    std::cout << "ACTIVE: " << size.allocated << std::endl;
    std::cout << "USED: " << size.used << std::endl;

    return size.allocated;
  }

  int variant() const { return size_scale; }
};
