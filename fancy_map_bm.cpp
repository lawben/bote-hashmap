#include "benchmark.hpp"
#include "fancy_index.hpp"

int main() {
  using FancyMap = FancyMap<MyValue>;

  std::vector<uint64_t> insert_keys = generate_insert_keys();
  std::vector<uint64_t> find_keys = generate_find_keys();

  run_map<FancyMap>("FancyMap  ", insert_keys, find_keys);
}
