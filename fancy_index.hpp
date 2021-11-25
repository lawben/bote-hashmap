#pragma once

#include <cstdint>
#include <vector>

using KeyT = uint64_t;

template <typename ValueT>
struct FancyEntry {
  KeyT key;
  ValueT value;

  FancyEntry() {
    key = 0;
    value = ValueT{};
  }
};


template <typename ValueT>
class FancyMap {
 public:
  using EntryT = FancyEntry<ValueT>;

  explicit FancyMap(size_t initial_size) : num_buckets_{initial_size}, buckets_{initial_size} {}

  void insert(std::pair<KeyT, ValueT> record);
  const ValueT& operator[](KeyT key) const;

  size_t get_memory_consumption() const { return num_buckets_ * sizeof(EntryT); }

 private:
  size_t num_buckets_;
  std::vector<EntryT> buckets_;
};

template <typename ValueT>
void FancyMap<ValueT>::insert(std::pair<KeyT, ValueT> record) {
  auto& [key, value] = record;
  const uint64_t hash = std::hash<KeyT>{}(key);
  const uint64_t bucket_position = hash % num_buckets_;

  EntryT& entry = buckets_[bucket_position];
  if (entry.key == 0) {
    // Bucket is empty. Insert record here.
    entry.key = key;
    entry.value = value;
    return;
  }

  // Bucket is not free. Need to do linear scan.
  uint64_t offset = 1;
  EntryT* next_entry = &buckets_[(bucket_position + offset) % num_buckets_];
  while (next_entry->key != 0 && offset < num_buckets_) {
    next_entry = &buckets_[(bucket_position + offset) % num_buckets_];
    offset++;
  }

  if (offset == num_buckets_) {
    // No free bucket found :(
    throw std::runtime_error("No free bucket found!");
  }

  // Found free bucket :)
  next_entry->key = key;
  next_entry->value = value;
}

template <typename ValueT>
const ValueT& FancyMap<ValueT>::operator[](KeyT key) const {
  const uint64_t hash = std::hash<KeyT>{}(key);
  const uint64_t bucket_position = hash % num_buckets_;

  const EntryT& entry = buckets_[bucket_position];
  if (entry.key == key) {
    // Found record in bucket.
    return entry.value;
  }

  if (entry.key == 0) {
    // Record not in map
    throw std::runtime_error("Key " + std::to_string(key) + " not found!");
  }

  // Record not found. Need to do linear scan.
  uint64_t offset = 1;
  const EntryT* next_entry = &buckets_[(bucket_position + offset) % num_buckets_];
  while (next_entry->key != 0 && next_entry->key != key && offset < num_buckets_) {
    next_entry = &buckets_[(bucket_position + offset) % num_buckets_];
    offset++;
  }

  if (next_entry->key == 0 || offset == num_buckets_) {
    // Key not in map
    throw std::runtime_error("Key " + std::to_string(key) + " not found!");
  }

  // Found record :)
  return entry.value;
}
