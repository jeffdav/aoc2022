#include <algorithm>
#include <deque>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "../common/string_utils.h"

constexpr int64_t width = 95;
constexpr int64_t height = 41;

int64_t map[width][height];

typedef struct _location {
  int64_t x;
  int64_t y;
} location_t;

location_t start;
location_t finish;

void load_map() {
  std::ifstream file("input_12.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  int y = 0;
  std::string line;
  while(std::getline(file, line)) {
    int x = 0;
    for (const auto& c : line) {
      if (c == 'S') {
        map[x][y] = 0;
        start.x = x;
        start.y = y;
      } else if (c == 'E') {
        map[x][y] = 'z' - 'a';
        finish.x = x;
        finish.y = y;
      } else {
        map[x][y] = c - 'a';
      }
      x++;
    }
    y++;
  }

  file.close();
}

constexpr int64_t unexplored = std::numeric_limits<int64_t>::max();
int64_t paths[width][height];

void init_paths() {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      paths[x][y] = unexplored;
    }
  }
}

inline bool in_bounds(const location_t loc) {
  return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}

inline bool is_unexplored(const location_t loc) {
  return paths[loc.x][loc.y] == unexplored;
}

inline bool is_accessible(const location_t loc, const int64_t curr_height) {
  return map[loc.x][loc.y] <= curr_height + 1;
}

inline void mark_path(const location_t loc, const int64_t depth) {
  paths[loc.x][loc.y] = depth;
}

void explore(const location_t start) {
  paths[start.x][start.y] = 0;
  
  std::deque<location_t> locations;

  int64_t curr_height = map[start.x][start.y];
  location_t loc = start;
  while (!(loc.x == finish.x && loc.y == finish.y)) {
    int64_t next = paths[loc.x][loc.y] + 1;

    location_t left{ loc.x - 1, loc.y };
    if (in_bounds(left) && is_unexplored(left) && is_accessible(left, curr_height)) {
      locations.push_back(left);
      mark_path(left, next);
    }

    location_t right{ loc.x + 1, loc.y };
    if (in_bounds(right) && is_unexplored(right) && is_accessible(right, curr_height)) {
      locations.push_back(right);
      mark_path(right, next);
    }

    location_t up{ loc.x, loc.y - 1 };
    if (in_bounds(up) && is_unexplored(up) && is_accessible(up, curr_height)) {
      locations.push_back(up);
      mark_path(up, next);
    }

    location_t down{ loc.x, loc.y + 1 };
    if (in_bounds(down) && is_unexplored(down) && is_accessible(down, curr_height)) {
      locations.push_back(down);
      mark_path(down, next);
    }

    if (locations.empty()) {
      // You can't get there from here.
      break;
    }

    loc = locations.front();
    locations.pop_front();

    curr_height = map[loc.x][loc.y];
  }
}

void solve_part_one() {
  init_paths();
  explore(start);

  std::cout << "1: " << paths[finish.x][finish.y] << std::endl;
}

void solve_part_two() {
  std::map<int64_t, location_t> results;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (map[x][y] == 0) {
        init_paths();
        explore({ x, y });
        if (paths[finish.x][finish.y] != unexplored) {
          results[paths[finish.x][finish.y]] = { x, y };
        }
      }
    }
  }

  const auto& best = results.begin();
  std::cout << "2: best route = " << best->first << std::endl;  
}

int main(int argc, char *argv[]) { 
  load_map();
  solve_part_one();
  solve_part_two();
}