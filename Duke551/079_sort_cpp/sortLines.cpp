#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::string aString;
    std::vector<std::string> strings;
    while (!std::cin.eof()) {
      std::getline(std::cin, aString);
      strings.push_back(aString);
    }
    std::sort(strings.begin(), strings.end());
    std::vector<std::string>::iterator it = strings.begin();
    while (it != strings.end()) {
      std::cout << *it << std::endl;
      it++;
    }
    strings.clear();
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream read(argv[i]);
      if (read.fail()) {
        std::cerr << "Can't open file: " << argv[i] << std::endl;
        exit(EXIT_FAILURE);
      }
      std::string aString;
      std::vector<std::string> strings;
      while (!read.eof()) {
        std::getline(read, aString);
        strings.push_back(aString);
      }
      std::sort(strings.begin(), strings.end());
      std::vector<std::string>::iterator it = strings.begin();
      while (it != strings.end()) {
        std::cout << *it << std::endl;
        it++;
      }
      strings.clear();
    }
  }
  return EXIT_SUCCESS;
}
