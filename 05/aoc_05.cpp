#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void solve_part_one() {
  std::ifstream file("input_05.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  std::string line;
  while(std::getline(file, line)) {
  }

  file.close();
}

void solve_part_two() {
  std::ifstream file("input_05.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  std::string line;
  while(std::getline(file, line)) {
  }

  file.close();
}

int main(int argc, char *argv[]) { 
  solve_part_one();
  solve_part_two();
}