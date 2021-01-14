#include <fstream>

#include "page.h"

int main(int argc, char ** argv) {
  //check the arguments
  if (argc != 2) {
    errmsg("Use cyoa-step1 filename!");
  }
  //check if file exists
  try {
    std::ifstream file(argv[1]);
    if (!file) {
      throw noFile();
    }
  }
  catch (std::exception & e) {
    std::cerr << argv[1] << std::endl;
    errmsg(e.what());
  }
  //generate a page with the file and page number set as 0 by default
  //print the page
  std::ifstream file(argv[1]);
  int defaultN = 0;
  Page page(file, defaultN);
  page.printPage();
  return EXIT_SUCCESS;
}
