#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    error("argc not correct!");
  }
  //read catarray and temp from file
  catarray_t * cats = readCats(argv[1]);
  text * t = readTemp(argv[2]);
  //initialize a cat_t to store previous word
  category_t previous;
  previous.name = strdup("previous");
  //use strdup to avoid invalid free since other name read from file are all strdup-ed.
  previous.words = NULL;
  previous.n_words = 0;
  //process the temp into story
  //with parameters catarray==cats and previous words
  //0 indicates that repeated words are allowed
  processTemp(t, cats, &previous, 0);
  //print the story, free things on the heap and exit
  for (size_t i = 0; i < t->textSZ; i++) {
    printf("%s", t->lines[i]);
  }
  freeT(t);
  freeArr(cats);
  freeCT(&previous);
  return EXIT_SUCCESS;
}
