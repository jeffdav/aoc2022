#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "../common/string_utils.h"

const int64_t relief = 3;

typedef struct Monkey {
  std::deque<int64_t> items;
  std::function<int64_t(int64_t)> operation;
  std::function<int64_t(int64_t)> test;

  bool enable_relief = true;
  int64_t inspection_count = 0;

  void inspect_next();
} monkey_t;

std::array<monkey_t, 8> monkeys;

void Monkey::inspect_next() {
  int64_t worry = items.front();
  items.pop_front();
  
  worry = operation(worry);
  inspection_count++;

  if (enable_relief) {
    worry /= relief;
  } else {
    constexpr int64_t prime_product = 13 * 7 * 19 * 2 * 5 * 3 * 11 * 17;
    worry %= prime_product;
  }
  int64_t target = test(worry);

  monkeys[target].items.push_back(worry);
}

void init_monkeys(bool enable_relief) {
  monkeys[0] = monkey_t{
    { 52, 60, 85, 69, 75, 75 },
    [](int64_t old) {
      return old * 17;
    },
    [](int64_t num) {
      return num % 13 == 0 ? 6 : 7;
    },
    enable_relief
  };

  monkeys[1] = monkey_t{
    { 96, 82, 61, 99, 82, 84, 85 },
    [](int64_t old) {
      return old + 8;
    },
    [](int64_t num) {
      return num % 7 == 0 ? 0 : 7;
    },
    enable_relief
  };

  monkeys[2] = monkey_t{
    { 95, 79 },
    [](int64_t old) {
      return old + 6;
    },
    [](int64_t num) {
      return num % 19 == 0 ? 5 : 3;
    },
    enable_relief
  };

  monkeys[3] = monkey_t{
    { 88, 50, 82, 65, 77 },
    [](int64_t old) {
      return old * 19;
    },
    [](int64_t num) {
      return num % 2 == 0 ? 4 : 1;
    },
    enable_relief
  };

  monkeys[4] = monkey_t{
    { 66, 90, 59, 90, 87, 63, 53, 88 },
    [](int64_t old) {
      return old + 7;
    },
    [](int64_t num) {
      return num % 5 == 0 ? 1 : 0;
    },
    enable_relief
  };

  monkeys[5] = monkey_t{
    { 92, 75, 62 },
    [](int64_t old) {
      return old * old;
    },
    [](int64_t num) {
      return num % 3 == 0 ? 3 : 4;
    },
    enable_relief
  };

  monkeys[6] = monkey_t{
    { 94, 86, 76, 67 },
    [](int64_t old) {
      return old + 1;
    },
    [](int64_t num) {
      return num % 11 == 0 ? 5 : 2;
    },
    enable_relief
  };

  monkeys[7] = monkey_t{
    { 57 },
    [](int64_t old) {
      return old + 2;
    },
    [](int64_t num) {
      return num % 17 == 0 ? 6 : 2;
    },
    enable_relief
  };
}

int64_t monkey_business() {
  std::array<int64_t, 8> inspections;
  for (int i = 0; i < inspections.size(); i++) {
    inspections[i] = monkeys[i].inspection_count;
  }

  std::sort(inspections.begin(), inspections.end(), std::greater<int64_t>());

  return inspections[0] * inspections[1];
}

void solve_part_one() {
  init_monkeys(true);

  constexpr int64_t rounds = 20;

  for (int r = 0; r < rounds; r++) {
    for (int m = 0; m < monkeys.size(); m++) {
      while (!monkeys[m].items.empty()) {
        monkeys[m].inspect_next();
      }
    }
  }

  std::cout << "1: monkey_business = " << monkey_business() << std::endl;
}

void solve_part_two() {
  init_monkeys(false);

  constexpr int64_t rounds = 10000;

  for (int r = 0; r < rounds; r++) {
    for (int m = 0; m < monkeys.size(); m++) {
      while (!monkeys[m].items.empty()) {
        monkeys[m].inspect_next();
      }
    }
  }

  std::cout << "2: monkey_business = " << monkey_business() << std::endl;
}

int main(int argc, char *argv[]) { 
  solve_part_one();
  solve_part_two();
}
