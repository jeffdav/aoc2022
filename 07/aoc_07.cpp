#include <algorithm>
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

typedef struct _file {
  std::string name;
  int64_t size;
} file_t;

typedef struct _directory {
  std::string name;
  std::vector<file_t*> files;
  std::vector<_directory*> dirs;
  int64_t size;
} directory_t;

int64_t calcSize(directory_t* dir) {
  int64_t size = 0;
  for (auto d : dir->dirs) {
    d->size = calcSize(d);
    size += d->size;
  }
  for (auto f : dir->files) {
    size += f->size;
  }
  return size;
}

int64_t sumDirectorySizesLessThan(directory_t* dir, int64_t max) {
  int64_t sum = 0;
  for (auto d : dir->dirs) {
    if (d->size < max) { sum += d->size; }
    sum += sumDirectorySizesLessThan(d, max);
  }
  return sum;
}

directory_t root;
std::stack<directory_t*> cwd;

void initRoot() {
  root.name = "/";
  cwd.push(&root);
}

void solve_part_one() {
  std::ifstream file("input_07.txt");
  if (!file.is_open()) {
    std::cout << "File open failure. :(" << std::endl;
    exit(1);
  }

  std::string line;
  while(std::getline(file, line)) {
    auto parts = split(line, ' ');
    if (parts[0] == "$") {
      if (parts[1] == "cd") {
        if (parts[2] == "/") {
          while (cwd.size() > 1) { cwd.pop(); }
        } else if (parts[2] == "..") {
          cwd.pop();
        } else {
          std::string dirname{parts[2]};
          auto it = std::find_if(cwd.top()->dirs.begin(), cwd.top()->dirs.end(), [&dirname](auto d) {
            return d->name == dirname;
          });
          cwd.push(*it);          
        }
      } else if (parts[1] == "ls") {
        continue;
      }
    } else if (parts[0] == "dir") {
      directory_t* dir = new directory_t;
      dir->name = parts[1];
      cwd.top()->dirs.push_back(dir);
    } else {
      file_t* f = new file_t;
      f->size = asInt(parts[0]);
      f->name = parts[1];
      cwd.top()->files.push_back(f);
    }
  }

  root.size = calcSize(&root);

  std::cout << "1: " << sumDirectorySizesLessThan(&root, 100000) << std::endl;

  file.close();
}

void flatten(std::vector<directory_t*>* flattened, directory_t* dir) {
  for (auto d : dir->dirs) {
    flattened->push_back(d);
    flatten(flattened, d);
  }
}

void solve_part_two() {
  std::vector<directory_t*> flat_dirs;
  flatten(&flat_dirs, &root);

  std::sort(flat_dirs.begin(), flat_dirs.end(), [](auto d1, auto d2){
    return d1->size < d2->size;
  });

  int64_t freeSpace = 70000000 - root.size;
  int64_t sizeNeeded = 30000000 - freeSpace;
  auto it = std::find_if(flat_dirs.begin(), flat_dirs.end(), [&sizeNeeded](auto d){
    return d->size >= sizeNeeded;
  });

  std::cout << "2: " << (*it)->size << std::endl;
}

int main(int argc, char *argv[]) { 
  initRoot(); 
  solve_part_one();
  solve_part_two();
}