#pragma once

#include <string.h>

#include <algorithm>
#include <exotic_hashing.hpp>

#include "../util.h"
#include "base.h"

template <class KeyType, size_t Shift>
class SFMWHC : public Competitor {
  exotic_hashing::CompressedSFMWHC<KeyType> mwhc;
  size_t error = 0;

 public:
  uint64_t Build(const std::vector<KeyValue<KeyType>>& data) {
    assert(data.size() > 0);

    return util::timing([&] {
      // we only need the keys
      std::vector<KeyType> keys;
      std::vector<size_t> offsets;

      size_t prev_ind = 0;
      keys.push_back(data[prev_ind].key >> Shift);
      offsets.push_back(prev_ind);
      for (size_t i = prev_ind + 1; i < data.size(); i++) {
        const auto key = data[i].key >> Shift;
        const auto prev_key = data[prev_ind].key >> Shift;
        if (key == prev_key) continue;

        error = std::max(error, i - prev_ind);

        prev_ind = i;
        keys.push_back(key);
        offsets.push_back(prev_ind);
      }
      error = std::max(error, data.size() - prev_ind);

      // TODO: tmp
      std::cout << "Found error: " << error << ", using shift: " << Shift
                << ", skipped: " << (data.size() - keys.size()) << " keys"
                << std::endl;

      mwhc.construct(keys.begin(), keys.end(), offsets.begin());
    });
  }

  SearchBound EqualityLookup(const KeyType lookup_key) const {
    const auto rank = mwhc(lookup_key >> Shift);
    return {rank, rank + error};
  }

  std::string name() const { return "SFMWHC"; }

  std::size_t size() const { return mwhc.byte_size(); }

  bool applicable(bool _unique, const std::string& data_filename) {
    return true;
  }

  int variant() const { return Shift; }
};
