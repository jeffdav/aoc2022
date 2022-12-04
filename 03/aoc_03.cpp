#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

void solve_part_one() {
  std::ifstream file("input_03.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  int64_t sum = 0;
  std::string line;
  while(std::getline(file, line)) {
    auto len = line.length() / 2;

    std::sort(line.begin(), line.begin() + len);
    std::sort(line.begin() + len, line.end());

    std::vector<char> intersection;
    std::set_intersection(line.begin(), line.begin() + len, line.begin() + len, line.end(), std::back_inserter(intersection));

    char val = intersection.front();
    if (islower(val)) {
      sum += val - 'a' + 1;
    } else {
      sum += val - 'A' + 27;
    }
  }

  std::cout << "1: Sum is: " << sum << std::endl;

  file.close();
}

void solve_part_two() {
  std::ifstream file("input_03.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  int64_t sum = 0;
  std::string line1;
  std::string line2;
  std::string line3;
  while(std::getline(file, line1)) {
    std::getline(file, line2);
    std::getline(file, line3);

    std::sort(line1.begin(), line1.end());
    std::sort(line2.begin(), line2.end());
    
    std::vector<char> intersection;
    std::set_intersection(line1.begin(), line1.end(), line2.begin(), line2.end(), std::back_inserter(intersection));

    std::sort(line3.begin(), line3.end());
    std::vector<char> intersection2;
    std::set_intersection(intersection.begin(), intersection.end(), line3.begin(), line3.end(), std::back_inserter(intersection2));

    char val = intersection2.front();
    if (islower(val)) {
      sum += val - 'a' + 1;
    } else {
      sum += val - 'A' + 27;
    }
  }

  std::cout << "2: Sum is: " << sum << std::endl;

  file.close();
}

int main(int argc, char *argv[]) { 
  solve_part_one();
  solve_part_two();
}