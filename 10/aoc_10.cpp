#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "../common/string_utils.h"

typedef enum _command {
  CMD,
  OP1,
} command_t;

typedef enum _instruction {
  NOOP,
  ADDX,
} instruction_t;

std::map<int64_t, int64_t> cycles = {
  { NOOP, 1 },
  { ADDX, 2 },
};

std::map<std::string, instruction_t> instructions = {
  { "noop", NOOP },
  { "addx", ADDX },
};

void solve_part_one() {
  std::ifstream file("input_10.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  std::array<int64_t, 6> interesting = { 20, 60, 100, 140, 180, 220 };

  int64_t cycle = 0;
  int64_t reg1ster = 1;
  int64_t interesting_sum = 0;

  std::string line;
  while(std::getline(file, line)) {
    auto cmd = split(line, ' ');
    instruction_t ins = instructions[cmd[CMD]];

    for (int i = 0; i < cycles[ins]; i++) {
      cycle++;  

      if (std::find(interesting.begin(), interesting.end(), cycle) != interesting.end()) {
        int64_t signal_strength = cycle * reg1ster;
        std::cout << "1: interesting cycle (" << cycle << ") = " << signal_strength << std::endl;
        interesting_sum += signal_strength;
      }

      // Last cycle for instruction, so do whatever needs doing.
      if (i == cycles[ins] - 1) {
        switch (ins) {
          case NOOP:
            break;

          case ADDX:
            reg1ster += asInt(cmd[OP1]);
            break;
        }
      }
    }
  }

  std::cout << "1: total sum = " << interesting_sum << std::endl;

  file.close();
}

bool isLit(int64_t sprite_pos, int64_t pixel) {
  return pixel >= sprite_pos - 1 && pixel <= sprite_pos + 1;
}

void solve_part_two() {
  std::ifstream file("input_10.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  int64_t cycle = 0;
  int64_t reg1ster = 1;
  int64_t curr_pixel = 0;

  std::string line;
  while(std::getline(file, line)) {
    auto cmd = split(line, ' ');
    instruction_t ins = instructions[cmd[CMD]];


    for (int i = 0; i < cycles[ins]; i++) {
      cycle++;

      std::cout << (isLit(reg1ster, curr_pixel) ? "#" : ".");
      curr_pixel++;
      if (curr_pixel == 40) {
        std::cout << std::endl;
        curr_pixel = 0;
      }

      // Last cycle for instruction, so do whatever needs doing.
      if (i == cycles[ins] - 1) {
        switch (ins) {
          case NOOP:
            break;

          case ADDX:
            reg1ster += asInt(cmd[OP1]);
            break;
        }
      }
    }
  }

  std::cout << std::endl << "2: curr_pixel = " << curr_pixel << std::endl;

  file.close();
}

int main(int argc, char *argv[]) { 
  solve_part_one();
  solve_part_two();
}