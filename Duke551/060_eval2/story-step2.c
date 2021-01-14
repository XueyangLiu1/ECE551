#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    error("argc not correct!");
  }
  catarray_t * cats = readCats(argv[1]);
  printWords(cats);
  freeArr(cats);
  return EXIT_SUCCESS;
}
