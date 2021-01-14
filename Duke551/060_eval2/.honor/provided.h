#ifndef __PROVIDED_H__
#define __PROVIDED_H__

#include <stdlib.h>

struct category_tag {
  char * name;
  char ** words;
  size_t n_words;
};
typedef struct category_tag category_t;

struct catarray_tag {
  category_t * arr;
  size_t n;
};
typedef struct catarray_tag catarray_t;

const char * chooseWord(char * category, catarray_t * cats);
void printWords(catarray_t * cats);

#endif
