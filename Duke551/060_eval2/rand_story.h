#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "provided.h"
//any functions you want your main to use

struct text_tag {
  char ** lines;
  size_t textSZ;
};

typedef struct text_tag text;

//print the suitable error msg and exit
void error(const char * errormsg);
//read the story template from file and store it in struct text
text * readTemp(const char * fileName);
//process the substitution
void processTemp(text * t, catarray_t * cats, category_t * previous, int mode);
//decide the word to substitude
const char * judgeWord(char * word, catarray_t * cats, category_t * previous, int mode);
//delete one word from the cat array
void dFrom(catarray_t * cats, size_t i, char * word);
//substitude the blank in the line with word
char * subWord(char * line, catarray_t * cats, category_t * previous, int mode);
//read cats and words from file and store them in cat array
catarray_t * readCats(const char * fileName);
//store one word into the correct category in the catarray
catarray_t * storeOne(char * line, catarray_t * cats);
//free the text template
void freeT(text * t);
//free the cat array
void freeArr(catarray_t * cats);
//free one single category
void freeCT(category_t * cat);
#endif
