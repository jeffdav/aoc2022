#include <array>
#include <deque>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "../common/string_utils.h"

constexpr int64_t invalid = std::numeric_limits<int64_t>::max();

typedef struct _signal {
  int64_t strength = invalid;
  std::vector<_signal>* signals = nullptr;

  bool is_vector() { 
    return strength == invalid && signals != nullptr; 
  }

  bool is_vector_of_one() {
    return strength == invalid && signals != nullptr && signals->size() == 1;
  }

  bool is_number() {
    return strength != invalid && signals == nullptr;
  }

  bool is_divider() {
    if (is_vector_of_one() && signals->front().is_vector_of_one()) {
      auto s = signals->front().signals->front().strength;
      return s == 2 || s == 6;
    }
    return false;
  }

  static _signal parse(const std::string& str);
} signal_t;

int64_t parse_num(const std::string& str, size_t& pos) {
  size_t len = 0;
  int64_t val = 0;
  while (std::isdigit(str[pos])) {
    val *= 10;
    val += str[pos] - '0';
    len++;
    pos++;
  }
  return val;
}

void parse_helper(const std::string& str, size_t pos, std::deque<signal_t>& d) {
  while (pos < str.length() - 1) {
    auto c = str[pos];
    if (c == ',') {
      pos++;
    } else if (c == '[') {
      pos++;
      signal_t signal{};
      signal.signals = new std::vector<signal_t>{};
      d.back().signals->push_back(signal);
      d.push_back(signal);
    } else if (c == ']') {
      pos++;
      d.pop_back();
    } else if (std::isdigit(c)) {
      auto num = parse_num(str, pos);
      signal_t signal{num};
      d.back().signals->push_back(signal);
    } 
  }
}

signal_t signal_t::parse(const std::string& str) {
  std::deque<signal_t> d;
  signal_t signal{};
  signal.signals = new std::vector<signal_t>{};
  d.push_back(signal);
  parse_helper(str, 1, d);
  return d.front();
}

typedef enum _ordering {
  LESS_THAN,
  EQUAL,
  GREATER_THAN,
} ordering_t;

ordering_t check_sorted(std::vector<signal_t>* left, std::vector<signal_t>* right) {
  auto lit = left->begin();
  auto rit = right->begin();
  while (lit < left->end() && rit < right->end()) {
    if (lit->is_number() && rit->is_number()) {
      if (lit->strength > rit->strength) {
        return GREATER_THAN;
      } else if (lit->strength == rit->strength) {
        lit++;
        rit++;
      } else {
        return LESS_THAN;
      }
    } else {
      ordering_t ordering;
      if (lit->is_vector() && rit->is_vector()) {
        ordering = check_sorted(lit->signals, rit->signals);
      } else if (lit->is_number() && rit->is_vector()) {
        auto lvec = new std::vector<signal_t>{{lit->strength}};
        ordering = check_sorted(lvec, rit->signals);      
      } else if (lit->is_vector() && rit->is_number()) {
        auto rvec = new std::vector<signal_t>{{rit->strength}};
        ordering = check_sorted(lit->signals, rvec);
      }

      if (ordering == EQUAL) {
        lit++;
        rit++;
      } else {
        return ordering;
      }
    }
  }

  if (lit == left->end() && rit == right->end()) {
    return EQUAL;
  } else if (lit == left->end() && rit < right->end()) {
    return LESS_THAN;
  } else {
    return GREATER_THAN;
  }
}

void solve_part_one() {
  std::ifstream file("input_13.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  int64_t index = 1;
  int64_t sum = 0;
  std::string left;
  while(std::getline(file, left)) {
    std::string right;
    std::getline(file, right);

    std::string blank;
    std::getline(file, blank);

    signal_t lsig = signal_t::parse(left);
    signal_t rsig = signal_t::parse(right);

    ordering_t order = check_sorted(lsig.signals, rsig.signals);
    if (order == LESS_THAN) {
      sum += index;
    }

    index++;
  }

  std::cout << "1: sum = " << sum << std::endl;

  file.close();
}

void solve_part_two() {
  std::ifstream file("input_13.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  std::vector<signal_t> signals;
  std::string line;
  while(std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    signal_t signal = signal_t::parse(line);
    signals.push_back(signal);
  }

  signals.push_back(signal_t::parse("[[2]]"));
  signals.push_back(signal_t::parse("[[6]]"));

  std::sort(signals.begin(), signals.end(), [](const signal_t& left, const signal_t& right) {
    return check_sorted(left.signals, right.signals) == LESS_THAN;
  });

  int64_t product = 1;
  for (int i = 0; i < signals.size(); i++) {
    if (signals[i].is_divider()) {
      product *= i + 1;
    }
  }

  std::cout << "2: product = " << product << std::endl;

  file.close();
}

int main(int argc, char *argv[]) {
  solve_part_one();
  solve_part_two();
}
