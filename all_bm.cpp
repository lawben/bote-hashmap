#include <unordered_map>

#include "benchmark.hpp"
#include "fancy_index.hpp"

int main() {
  using FancyIndex = FancyMap<uint64_t>;
  using StdIndex = std::unordered_map<KeyT, uint64_t>;
  using FancyMap = FancyMap<MyValue>;
  using StdMap = std::unordered_map<KeyT, MyValue>;

  std::vector<uint64_t> insert_keys = generate_insert_keys();
  std::vector<uint64_t> find_keys = generate_find_keys();

  run_map<StdMap>("StdMap    ", insert_keys, find_keys);
  run_index<StdIndex>("StdIndex  ", insert_keys, find_keys);

  run_map<FancyMap>("FancyMap  ", insert_keys, find_keys);
  run_index<FancyIndex>("FancyIndex", insert_keys, find_keys);
}
