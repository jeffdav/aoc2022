#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main(int argc, char *argv[]) { 
  std::ifstream file("input_01.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  std::vector<int64_t> elf_calories;
  std::string line;
  int64_t sum = 0;
  while(std::getline(file, line)) {
    if (std::all_of(line.begin(), line.end(), isspace)) {
      elf_calories.emplace_back(sum);
      sum = 0;
    } else {
      std::stringstream ss;
      int64_t number;
      ss << line;
      ss >> number;
      sum += number;
    }
  }

  std::cout << "Max value is: " << *std::max_element(elf_calories.begin(), elf_calories.end()) << std::endl;

  std::sort(elf_calories.begin(), elf_calories.end());

  // assert(elf_calories.length >= 3);

  int64_t top_three_sum = 0;
  std::reverse_iterator rit = elf_calories.rbegin();
  for (int i = 0; i < 3; i++) {
    top_three_sum += *rit;
    rit++;
  }

  std::cout << "Top three sum is: " << top_three_sum << std::endl;

  file.close();
}