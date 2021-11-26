#include <unordered_map>

#include "benchmark.hpp"
#include "fancy_index.hpp"

int main() {
  using FancyIndex = FancyMap<uint64_t>;

  std::vector<uint64_t> insert_keys = generate_insert_keys();
  std::vector<uint64_t> find_keys = generate_find_keys();

  run_index<FancyIndex>("FancyIndex", insert_keys, find_keys);
}
