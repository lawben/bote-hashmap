#include <unordered_map>

#include "benchmark.hpp"
#include "fancy_index.hpp"

int main() {
  using StdIndex = std::unordered_map<KeyT, uint64_t>;

  std::vector<uint64_t> insert_keys = generate_insert_keys();
  std::vector<uint64_t> find_keys = generate_find_keys();

  run_index<StdIndex>("StdIndex  ", insert_keys, find_keys);
}
