#include <iostream>
#include <fstream>
#include <string>

void solve_part_one() {
  std::ifstream file("input_07.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  std::string line;
  while(std::getline(file, line)) {
  }

  std::cout << "1: " << std::endl;

  file.close();
}

void solve_part_two() {
  std::ifstream file("input_07.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  std::string line;
  while(std::getline(file, line)) {
  }

  std::cout << "2: " << std::endl;

  file.close();
}

int main(int argc, char *argv[]) { 
  solve_part_one();
  solve_part_two();
}