#include <unordered_map>

#include "benchmark.hpp"

int main() {
  using StdMap = std::unordered_map<KeyT, MyValue>;

  std::vector<uint64_t> insert_keys = generate_insert_keys();
  std::vector<uint64_t> find_keys = generate_find_keys();

  run_map<StdMap>("StdMap", insert_keys, find_keys);
}
