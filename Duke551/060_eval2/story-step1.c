
#include "rand_story.h"

int main(int argc, char ** argv) {
  //check the argc
  if (argc != 2) {
    error("argc not correct!");
  }
  //read template from file
  text * t = readTemp(argv[1]);
  //process the temp into story
  //with parameters catarray==NULL and previous words==NULL
  //0 indicates that repeated words are allowed
  processTemp(t, NULL, NULL, 0);
  //print the story, free t and exit
  for (size_t i = 0; i < t->textSZ; i++) {
    printf("%s", t->lines[i]);
  }
  freeT(t);
  return EXIT_SUCCESS;
}
