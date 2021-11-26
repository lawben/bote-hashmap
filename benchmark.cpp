#include "benchmark.hpp"
#include <random>
#include <algorithm>

std::vector<uint64_t> generate_find_keys() {
  std::random_device dev;
  std::mt19937 rng{dev()};
  std::uniform_int_distribution<std::mt19937::result_type> dist(1, NUM_INSERTS);

  std::vector<uint64_t> find_keys{};
  find_keys.reserve(NUM_FINDS);
  for (uint64_t i = 0; i < NUM_FINDS; ++i) {
    find_keys.emplace_back(dist(rng));
  }
  return find_keys;
}

std::vector<uint64_t> generate_insert_keys() {
  std::random_device dev;
  std::mt19937 rng{dev()};
  std::uniform_int_distribution<std::mt19937::result_type> dist(1, NUM_INSERTS);

  std::vector<uint64_t> insert_keys{};
  insert_keys.resize(NUM_INSERTS);
  for (uint64_t i = 1; i <= NUM_INSERTS; ++i) {
    insert_keys[i] = i;
  }
  std::shuffle(insert_keys.begin(), insert_keys.end(), rng);
  return insert_keys;
}

uint64_t ops_per_s(uint64_t total_dur, uint64_t num_ops_per_run) {
  const double dur_in_s = (double) total_dur / 1000;
  const uint64_t total_ops = NUM_RUNS * num_ops_per_run;
  return static_cast<uint64_t>(total_ops / dur_in_s);
}
