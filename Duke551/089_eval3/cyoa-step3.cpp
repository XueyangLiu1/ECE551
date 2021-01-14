#include "function.h"
#include "page.h"
#include "story.h"

//check argument,read story,checkif it's valid,generate a reachable set,print ou the not reachable pages
int main(int argc, char ** argv) {
  try {
    if (argc != 2) {
      throw argErr();
    }
  }
  catch (std::exception & e) {
    std::cerr << "./cyoa-step3 directoryName" << std::endl;
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
    printNotReachable(reachable, pages);
  }
  return EXIT_SUCCESS;
}
