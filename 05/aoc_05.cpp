#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>

#include "../common/string_utils.h"

typedef enum _cmds {
  MOVE = 1,
  FROM = 3,
  TO = 5
} cmds_t;

std::array<std::stack<char>, 9> stacks;

void init_stacks() {
  for (int i = 0; i < 9; i++) {
    while (!stacks[i].empty()) {
      stacks[i].pop();
    }
  }

  stacks[8].push('J');
  stacks[8].push('S');
  stacks[8].push('Q');
  stacks[8].push('C');
  stacks[8].push('W');
  stacks[8].push('D');
  stacks[8].push('M');
  stacks[7].push('G');
  stacks[7].push('T');
  stacks[7].push('R');
  stacks[7].push('C');
  stacks[7].push('J');
  stacks[7].push('Q');
  stacks[7].push('S');
  stacks[7].push('N');
  stacks[6].push('L');
  stacks[6].push('N');
  stacks[6].push('Q');
  stacks[6].push('B');
  stacks[6].push('J');
  stacks[6].push('V');
  stacks[5].push('F');
  stacks[5].push('W');
  stacks[5].push('J');
  stacks[4].push('M');
  stacks[4].push('P');
  stacks[4].push('D');
  stacks[4].push('V');
  stacks[4].push('F');
  stacks[3].push('L');
  stacks[3].push('G');
  stacks[3].push('W');
  stacks[3].push('S');
  stacks[3].push('Z');
  stacks[3].push('J');
  stacks[3].push('D');
  stacks[3].push('N');
  stacks[2].push('F');
  stacks[2].push('W');
  stacks[2].push('R');
  stacks[2].push('T');
  stacks[2].push('S');
  stacks[2].push('Q');
  stacks[2].push('B');
  stacks[1].push('W');
  stacks[1].push('D');
  stacks[1].push('B');
  stacks[1].push('G');
  stacks[0].push('B');
  stacks[0].push('V');
  stacks[0].push('S');
  stacks[0].push('N');
  stacks[0].push('T');
  stacks[0].push('C');
  stacks[0].push('H');
  stacks[0].push('Q');  
}

void solve_part_one() {
  std::ifstream file("input_05.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  init_stacks();

  std::string line;
  while(std::getline(file, line)) {
    auto cmds = split(line, ' ');
    int64_t move = asInt(cmds[MOVE]);
    int64_t from = asInt(cmds[FROM]);
    int64_t to = asInt(cmds[TO]);

    // Our stacks array is zero-based.
    from--;
    to--;

    for (int i = 0; i < move; i++) {
      stacks[to].push(stacks[from].top());
      stacks[from].pop();
    }
  }

  std::string result;
  for (int i = 0; i < stacks.size(); i++) {
    result += stacks[i].top();
  }

  std::cout << "1: top items are: " << result << std::endl;

  file.close();
}

void solve_part_two() {
  std::ifstream file("input_05.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  init_stacks();

  std::stack<char> crane;
  std::string line;
  while(std::getline(file, line)) {
    auto cmds = split(line, ' ');
    int64_t move = asInt(cmds[MOVE]);
    int64_t from = asInt(cmds[FROM]);
    int64_t to = asInt(cmds[TO]);    

    // Our stacks array is zero-based.
    from--;
    to--;

    for (int i = 0; i < move; i++) {
      crane.push(stacks[from].top());
      stacks[from].pop();
    }
    for (int i = 0; i < move; i++) {
      stacks[to].push(crane.top());
      crane.pop();
    }    
  }

  std::string result;
  for (int i = 0; i < stacks.size(); i++) {
    result += stacks[i].top();
  }

  std::cout << "2: top items are: " << result << std::endl;

  file.close();
}

int main(int argc, char *argv[]) { 
  solve_part_one();
  solve_part_two();
}