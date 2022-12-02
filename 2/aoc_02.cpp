#include <iostream>
#include <fstream>
#include <map>
#include <string>

typedef enum _ThrowType {
  ROCK = 1,      // A, X
  PAPER = 2,     // B, Y
  SCISSORS = 3,  // C, Z
} ThrowType;

typedef enum _Result {
  LOSE = 0,
  DRAW = 3,
  WIN = 6,
} Result;

// Part one: X = Rock, Y = Paper, Z = Scissors
// std::map<std::string, int64_t> results = {
//   // Enemy plays Rock:
//   {"A X", DRAW + ROCK },
//   {"A Y", WIN + PAPER },
//   {"A Z", LOSE + SCISSORS },

//   // Enemy plays Paper:
//   {"B X", LOSE + ROCK },
//   {"B Y", DRAW + PAPER },
//   {"B Z", WIN + SCISSORS },

//   // Enemy plays Scissors:
//   {"C X", WIN + ROCK },
//   {"C Y", LOSE + PAPER },
//   {"C Z", DRAW + SCISSORS },
// };

// Part two: X = Lose, Y = Draw, Z = Win
std::map<std::string, int64_t> results = {
  // Enemy plays Rock:
  { "A X", LOSE + SCISSORS },
  { "A Y", DRAW + ROCK },
  { "A Z", WIN + PAPER },

  // Enemy plays Paper:
  { "B X", LOSE + ROCK },
  { "B Y", DRAW + PAPER},
  { "B Z", WIN + SCISSORS },

  // Enemy plays Scissors:
  { "C X", LOSE + PAPER },
  { "C Y", DRAW + SCISSORS },
  { "C Z", WIN + ROCK },
};

int main(int argc, char *argv[]) { 
  std::ifstream file("input_02.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  std::string line;
  int64_t score = 0;
  while(std::getline(file, line)) {
    score += results[line];
  }

  std::cout << "Total score is: " << score << std::endl;

  file.close();
}