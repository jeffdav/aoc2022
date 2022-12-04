#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

template <class T>
std::vector<T> split(const T& str, char split_char)
{
    std::vector<T> parts;
    typename T::size_type start_index = 0;
    typename T::size_type end_index;

    while ((end_index = str.find_first_of(split_char, start_index)) != T::npos) {
        parts.push_back(str.substr(start_index, end_index - start_index));
        start_index = end_index + 1;
    }
    parts.push_back(str.substr(start_index, T::npos));

    return parts;
}

int64_t asInt(const std::string& str) {
    std::stringstream ss;
    int64_t number;
    ss << str;
    ss >> number;
    return number;
}

void solve_part_one() {
  std::ifstream file("input_04.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  int64_t count = 0;
  std::string line;
  while(std::getline(file, line)) {
    auto parts = split(line, ',');
    auto left = split(parts[0], '-');
    auto right = split(parts[1], '-');

    if (asInt(left[0]) <= asInt(right[0]) && asInt(left[1]) >= asInt(right[1])) {
      count++;
    } else if (asInt(right[0]) <= asInt(left[0]) && asInt(right[1]) >= asInt(left[1])) {
      count++;
    }
  }

  std::cout << "1: Count is: " << count << std::endl;

  file.close();
}

bool between(int64_t x, int64_t a, int64_t b) {
  return x >= a && x <= b;
}

void solve_part_two() {
  std::ifstream file("input_04.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  int64_t count = 0;
  std::string line;
  while(std::getline(file, line)) {
    auto parts = split(line, ',');
    auto left = split(parts[0], '-');
    auto right = split(parts[1], '-');

    if (between(asInt(left[0]), asInt(right[0]), asInt(right[1])) ||
        between(asInt(left[1]), asInt(right[0]), asInt(right[1])) ||
        between(asInt(right[0]), asInt(left[0]), asInt(left[1])) ||
        between(asInt(right[1]), asInt(left[0]), asInt(left[1]))) {
      count++;
    }
  }

  std::cout << "2: Count is: " << count << std::endl;

  file.close();
}

int main(int argc, char *argv[]) { 
  solve_part_one();
  solve_part_two();
}