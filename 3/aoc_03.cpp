#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main(int argc, char *argv[]) { 
  std::ifstream file("input_03.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  file.close();
}