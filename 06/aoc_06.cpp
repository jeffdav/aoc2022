#include <iostream>
#include <fstream>
#include <set>
#include <string>

void solve_part_one() {
  std::ifstream file("input_06.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  std::string line;
  std::getline(file, line);

  int64_t count = 0;
  std::deque<char> d;
  for (auto it = line.begin(); it != line.end(); ++it) {
    d.push_back(*it);
    count++;
    if (d.size() > 4) { d.pop_front(); }

    if (d.size() < 4) continue;

    bool found = true;
    std::set<char> chars;
    for (int i = 0; i < d.size(); i++) {
      auto result = chars.insert(d[i]);
      if (!result.second) {
        found = false; 
        break;
      }
    }

    if (found) {
      break;
    }
  }
  
  std::cout << "1: " << count << std::endl;

  file.close();
}

void solve_part_two() {
  std::ifstream file("input_06.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  std::string line;
  std::getline(file, line);

  int64_t count = 0;
  std::deque<char> d;
  for (auto it = line.begin(); it != line.end(); ++it) {
    d.push_back(*it);
    count++;
    if (d.size() > 14) { d.pop_front(); }

    if (d.size() < 14) continue;

    bool found = true;
    std::set<char> chars;
    for (int i = 0; i < d.size(); i++) {
      auto result = chars.insert(d[i]);
      if (!result.second) {
        found = false; 
        break;
      }
    }

    if (found) {
      break;
    }
  }

  std::cout << "2: " << count << std::endl;

  file.close();
}

int main(int argc, char *argv[]) { 
  solve_part_one();
  solve_part_two();
}
