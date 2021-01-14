#include "function.h"
#include "story.h"
//check arguments,read the story,check if the story is valid,then start the adventure!
int main(int argc, char ** argv) {
  try {
    if (argc != 2) {
      throw argErr();
    }
  }
  catch (std::exception & e) {
    std::cerr << "./cyoa-step2 directoryName" << std::endl;
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
    startStory(pages);
  }
  return EXIT_SUCCESS;
}
