#include "function.h"
#include "story.h"

//check arguments,read a story,check if it's valid, generate a reachable set, find a path to win
int main(int argc, char ** argv) {
  try {
    if (argc != 2) {
      throw argErr();
    }
  }
  catch (std::exception & e) {
    std::cerr << "./cyoa-step4 directoryName" << std::endl;
    errmsg(e.what());
  }
  std::vector<Page> pages = readStory(argv[1]);
  bool valid = false;
  try {
    valid = validStory(pages);
  }
  catch (std::exception & e) {
    errmsg(e.what());
  }
  if (valid) {
    std::set<int> reachable = checkReachability(pages);
    try {
      findPath(reachable, pages);
    }
    catch (std::exception & e) {
      std::cout << e.what() << std::endl;
      //this message is the "no way to win", so it is output by cout
    }
  }
  return EXIT_SUCCESS;
}
