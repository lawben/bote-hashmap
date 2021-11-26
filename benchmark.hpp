#include <iostream>
#include <unordered_map>
#include <random>

#include "fancy_index.hpp"

#define KEEP(x) asm volatile("" : : "g"(x) : "memory")

struct MyValue {
  uint64_t a;
  uint64_t b;
  uint64_t c;
  uint64_t d;

  MyValue() : a{0}, b{0}, c{0}, d{0} {}
  MyValue(uint64_t a, uint64_t b, uint64_t c, uint64_t d) : a{a}, b{b}, c{c}, d{d} {}
};

constexpr uint64_t NUM_RUNS = 3;
constexpr uint64_t NUM_INSERTS = 10000000;
constexpr uint64_t NUM_FINDS = NUM_INSERTS / 2;
constexpr uint64_t INITIAL_CAPACITY = NUM_INSERTS * 2;

uint64_t ops_per_s(uint64_t total_dur, uint64_t num_ops_per_run);

template <typename MapT>
void run_map( const std::string& name, const std::vector<uint64_t>& insert_keys, const std::vector<uint64_t>& find_keys) {
  uint64_t insert_dur = 0;
  uint64_t find_dur = 0;

  for (int run = 0; run < NUM_RUNS; ++run) {
    MapT map{INITIAL_CAPACITY};

    const auto insert_start = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < NUM_INSERTS; ++i) {
      const uint64_t key = insert_keys[i];
      map.insert({key, MyValue{key, key * 10, key * 100, key * 1000}});
    }
    const auto insert_end = std::chrono::steady_clock::now();
    insert_dur += std::chrono::duration_cast<std::chrono::milliseconds>(insert_end - insert_start).count();

    MyValue value{};
    uint64_t sum = 0;
    const auto find_start = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < NUM_FINDS; ++i) {
      const uint64_t key = find_keys[i];
      value = map[key];
      sum += (value.a + value.b + value.c + value.d);
    }
    const auto find_end = std::chrono::steady_clock::now();
    find_dur += std::chrono::duration_cast<std::chrono::milliseconds>(find_end - find_start).count();

    KEEP(sum);
  }

  std::cout << name << " average insert/s: " << ops_per_s(insert_dur, NUM_INSERTS) << " |"
            << " average find/s: " << ops_per_s(find_dur, NUM_FINDS) << std::endl;
}

template <typename IndexT>
void run_index( const std::string& name, const std::vector<uint64_t>& insert_keys, const std::vector<uint64_t>& find_keys) {
  uint64_t insert_dur = 0;
  uint64_t find_dur = 0;

  for (int run = 0; run < NUM_RUNS; ++run) {
    IndexT index{INITIAL_CAPACITY};

    const auto insert_start = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < NUM_INSERTS; ++i) {
      const uint64_t key = insert_keys[i];
      index.insert({key, key * 10});
    }
    const auto insert_end = std::chrono::steady_clock::now();
    insert_dur += std::chrono::duration_cast<std::chrono::milliseconds>(insert_end - insert_start).count();

    uint64_t sum = 0;
    const auto find_start = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < NUM_FINDS; ++i) {
      const uint64_t key = find_keys[i];
      sum += index[key];
    }
    const auto find_end = std::chrono::steady_clock::now();
    find_dur += std::chrono::duration_cast<std::chrono::milliseconds>(find_end - find_start).count();

    KEEP(sum);
  }

  std::cout << name << " average insert/s: " << ops_per_s(insert_dur, NUM_INSERTS) << " |"
            << " average find/s: " << ops_per_s(find_dur, NUM_FINDS) << std::endl;
};

std::vector<uint64_t> generate_find_keys();
std::vector<uint64_t> generate_insert_keys();
