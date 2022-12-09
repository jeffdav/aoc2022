#include <array>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#include "../common/string_utils.h"

typedef enum _cmd_t {
  DIR,
  DIST,
} cmd_t;

typedef std::pair<int64_t, int64_t> end_t;

std::set<std::pair<int64_t, int64_t>> tail_locations;

void updateTail(const std::string& dir, const end_t& head, end_t& tail) {
  int64_t dx = head.first - tail.first;
  int64_t dy = head.second - tail.second;

  if (std::abs(dx) <= 1 && std::abs(dy) <= 1) {
    return;
  }

  if (dir == "U") {
    tail.second = head.second - 1;
    tail.first = head.first;
  } else if (dir == "D") {
    tail.second = head.second + 1;
    tail.first = head.first;		
  } else if (dir == "L") {
    tail.first = head.first + 1;
    tail.second = head.second;
  } else if (dir == "R") {
    tail.first = head.first - 1;
    tail.second = head.second;
  }

  tail_locations.insert(tail);
}

void solve_part_one() {
  std::ifstream file("input_09.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  end_t head = {0, 0};
  end_t tail = {0, 0};

  tail_locations.insert(tail);

  std::string line;
  while(std::getline(file, line)) {
    auto r = split(line, ' ');
    auto dir = r[DIR];
    auto dist = asInt(r[DIST]);

    for (int64_t i = 0; i < dist; i++) {
      if (dir == "U") {
        head.second++;
        updateTail(dir, head, tail);
      } else if (dir == "D") {
        head.second--;
        updateTail(dir, head, tail);
      } else if (dir == "L") {
        head.first--;
        updateTail(dir, head, tail);
      } else if (dir == "R") {
        head.first++;
        updateTail(dir, head, tail);
      } 
    }
  }

  std::cout << "1: " << tail_locations.size() << std::endl;

  file.close();
}

void updateSegment(const std::string& dir, const end_t& head, end_t& tail) {
  int64_t dx = head.first - tail.first;
  int64_t dy = head.second - tail.second;

  if (std::abs(dx) <= 1 && std::abs(dy) <= 1) {
    return;
  }

  // From here on this function is total garbage.  But whatever it works
  // and I want to go to bed.
  std::string d{dir};

  if (dx == 2 && dy == 2) {
    tail.first++;
    tail.second++;
  } else if (dx == 2 && dy == -2) {
    tail.first++;
    tail.second--;
  } else if (dx == -2 && dy == 2) {
    tail.first--;
    tail.second++;
  } else if (dx == -2 && dy == -2) {
    tail.first--;
    tail.second--;
  } else {
    if (dx == 2) {
      d = "R";
    } else if (dx == -2) {
      d = "L";
    } else if (dy == 2) {
      d =  "U";
    } else if (dy == -2) {
      d = "D";
    }

    if (d == "U") {
      tail.second = head.second - 1;
      tail.first = head.first;
    } else if (d == "D") {
      tail.second = head.second + 1;
      tail.first = head.first;
    } else if (d == "L") {
      tail.first = head.first + 1;
      tail.second = head.second;
    } else if (d == "R") {
      tail.first = head.first - 1;
      tail.second = head.second;
    }
  }
}

void updateRope(const std::string& dir, std::array<end_t, 10>& r) {
  for (int i = 0; i < r.size() - 1; i++) {
    updateSegment(dir, r[i], r[i + 1]);
  }

  tail_locations.insert(r.back());
}

void solve_part_two() {
  std::ifstream file("input_09.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  tail_locations.clear();

  std::array<end_t, 10> rope;

  for (int i = 0; i < rope.size(); i++) {
    rope[i].first = 0;
    rope[i].second = 0;
  }

  std::string line;
  while(std::getline(file, line)) {
    auto r = split(line, ' ');
    auto dir = r[DIR];
    auto dist = asInt(r[DIST]);

    for (int64_t i = 0; i < dist; i++) {
      if (dir == "U") {
        rope.front().second++;
        updateRope(dir, rope);
      } else if (dir == "D") {
        rope.front().second--;
        updateRope(dir, rope);
      } else if (dir == "L") {
        rope.front().first--;
        updateRope(dir, rope);
      } else if (dir == "R") {
        rope.front().first++;
        updateRope(dir, rope);
      } 
    }
  }

  std::cout << "2: " << tail_locations.size() << std::endl;

  file.close();
}

int main(int argc, char *argv[]) { 
  solve_part_one();
  solve_part_two();
}
