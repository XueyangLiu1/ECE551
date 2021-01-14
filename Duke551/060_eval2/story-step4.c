#include "rand_story.h"
#define OPTION "-n"

int main(int argc, char ** argv) {
  //check argc
  if (argc != 3 && argc != 4) {
    error("argc not correct!");
  }
  if (argc == 3) {
    //completely same with story-step3
    catarray_t * cats = readCats(argv[1]);
    text * t = readTemp(argv[2]);
    category_t previous;
    previous.name = strdup("previous");
    previous.words = NULL;
    previous.n_words = 0;
    processTemp(t, cats, &previous, 0);
    for (size_t i = 0; i < t->textSZ; i++) {
      printf("%s", t->lines[i]);
    }
    freeT(t);
    freeArr(cats);
    freeCT(&previous);
    return EXIT_SUCCESS;
  }
  if (argc == 4) {
    //check if the 2nd argv is "-n"
    if (strcmp(OPTION, argv[1]) != 0) {
      error("Only accept filenames and '-n' option!");
    }
    catarray_t * cats = readCats(argv[2]);
    text * t = readTemp(argv[3]);
    category_t previous;
    previous.name = strdup("previous");
    previous.words = NULL;
    previous.n_words = 0;
    //process the temp into story
    //1 indicates that repeated words are not allowed
    processTemp(t, cats, &previous, 1);
    for (size_t i = 0; i < t->textSZ; i++) {
      printf("%s", t->lines[i]);
    }
    freeT(t);
    freeArr(cats);
    freeCT(&previous);
    return EXIT_SUCCESS;
  }
}
