#include "rand_story.h"

//print the suitable error msg and exit
void error(const char * errormsg) {
  fprintf(stderr, "%s\n", errormsg);
  exit(EXIT_FAILURE);
}

//read the story template from file and store it in struct text
text * readTemp(const char * fileName) {
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    error("No such template file!");
  }
  char * line = NULL;
  size_t sz = 0;
  //initialize a text to store the lines and line numbers
  text * t = malloc(sizeof(*t));
  t->lines = NULL;
  t->textSZ = 0;
  while (getline(&line, &sz, f) >= 0) {
    t->textSZ++;
    t->lines = realloc(t->lines, t->textSZ * sizeof(*t->lines));
    t->lines[t->textSZ - 1] = strdup(line);
    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    error("File cannot be closed!");
  }
  return t;
}

//process the substitution
void processTemp(text * t, catarray_t * cats, category_t * previous, int mode) {
  //for each line in t, perform the substitution
  for (size_t i = 0; i < t->textSZ; i++) {
    t->lines[i] = subWord(t->lines[i], cats, previous, mode);
  }
}

//decide the word to substitude
const char * judgeWord(char * word, catarray_t * cats, category_t * previous, int mode) {
  //mode==0 represents that repeated words are allowed and mode==1 represents not
  if (cats == NULL) {
    //for mode==1, cats will not be NULL so don't need other operations
    return chooseWord(word, cats);
  }
  //check all categories in the catarray to find the match one
  //if no category name is matched with the given one
  //do nothing and go next step
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(word, cats->arr[i].name) == 0) {
      //find the correct category
      //pick a word and put it into the previous words array if one is provided
      const char * result = chooseWord(word, cats);
      if (previous != NULL) {
        previous->n_words++;
        previous->words =
            realloc(previous->words, previous->n_words * sizeof(*previous->words));
        previous->words[previous->n_words - 1] = strdup(result);
      }
      //if no repeated words are allowed
      //delete the selected word from the cat array
      if (mode == 1) {
        //the cat array, the category index i and the selected word are passed into the function
        dFrom(cats, i, previous->words[previous->n_words - 1]);
      }
      //return the selected word
      return previous->words[previous->n_words - 1];
    }
  }
  //check if the given string is actually an integer bigger than 0
  //Note that 0 and negativ integers are not coinsidered as correct references to previous words
  if (atoi(word) >= 1) {
    //if the previous words are provided
    //select the correct one and make a duplicate
    //put the duplicate at the end of the previous words array and return it
    if (previous != NULL) {
      //caculate the index
      int index = previous->n_words - atoi(word);
      //check if the index is suitable
      if (index < 0) {
        error("The integer is too big and there are no enough words to refer to!");
      }
      const char * result = previous->words[index];
      previous->n_words++;
      previous->words =
          realloc(previous->words, previous->n_words * sizeof(*previous->words));
      previous->words[previous->n_words - 1] = strdup(result);
      return result;
    }
    //if no previous words provided but a reference exits, this is an error
    error("Exist _integer_ but no previous words!");
  }
  //if the string between _ _ is neither a category name nor a suitable integer
  //print different error msg for different mode and exit
  else {
    if (mode == 0) {
      error("_ _ contains neither the category word nor an integer!");
    }
    if (mode == 1) {
      error("_ _ contains neither the category word nor an integer or the cats has run "
            "out of words of some categories!");
    }
  }
  //this return should never be executed
  return NULL;
}

//delete one word from the cat array
void dFrom(catarray_t * cats, size_t i, char * word) {
  //cats is the cat array
  //i is the category index where the word is from

  //reduce the number of words of the category
  cats->arr[i].n_words--;
  if (cats->arr[i].n_words == 0) {
    //if the category is then empty
    //go verify if the cat array is then empty
    cats->n--;
    if (cats->n == 0) {
      //if the cat array is empty
      //free the only category in it
      //but do not free cats->arr and cats themselves
      //since they will be freed together at the end of the program
      free(cats->arr[0].words[0]);
      free(cats->arr[0].words);
      free(cats->arr[0].name);
    }
    else {
      //if the category itself is empty but there are other categories left
      //make a deep copy of the cats->arr except the arr[i]
      category_t * newArr = malloc(cats->n * sizeof(*newArr));
      //copy arr from 0 to i-1
      for (size_t j = 0; j < i; j++) {
        category_t one;
        one.name = strdup(cats->arr[j].name);
        one.n_words = cats->arr[j].n_words;
        one.words = malloc(one.n_words * sizeof(*one.words));
        for (size_t o = 0; o < one.n_words; o++) {
          one.words[o] = strdup(cats->arr[j].words[o]);
        }
        newArr[j] = one;
      }
      //deep copy arr from i+1 to n
      //since we have preformed cats->n--,now we need to add 1 back
      //to iterate every arr of the cats->arr
      for (size_t j = i + 1; j < cats->n + 1; j++) {
        category_t one;
        one.name = strdup(cats->arr[j].name);
        one.n_words = cats->arr[j].n_words;
        one.words = malloc(one.n_words * sizeof(*one.words));
        for (size_t o = 0; o < one.n_words; o++) {
          one.words[o] = strdup(cats->arr[j].words[o]);
        }
        newArr[j - 1] = one;
      }
      //manually free the arrs
      //freeCT has some issues here so it cannot be used
      for (size_t j = 0; j < cats->n + 1; j++) {
        if (i == j) {
          free(cats->arr[j].name);
          free(cats->arr[j].words[0]);
          free(cats->arr[j].words);
        }
        else {
          for (size_t n = 0; n < cats->arr[j].n_words; n++) {
            free(cats->arr[j].words[n]);
          }
          free(cats->arr[j].words);
          free(cats->arr[j].name);
        }
      }
      //free cats->arr and assign the deep copy to it
      free(cats->arr);
      cats->arr = newArr;
    }
  }
  else {
    //if the category it self will not be empty either
    //make a deep copy of arr[i].words
    //free things and assign words to newWords
    char ** newWords = malloc(cats->arr[i].n_words * sizeof(*newWords));
    int counter = 0;
    for (size_t j = 0; j < cats->arr[i].n_words + 1; j++) {
      if (strcmp(cats->arr[i].words[j], word) != 0) {
        newWords[counter] = strdup(cats->arr[i].words[j]);
        counter++;
      }
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].words);
    cats->arr[i].words = newWords;
  }
}

//substitude the blank in the line with word
char * subWord(char * line, catarray_t * cats, category_t * previous, int mode) {
  //find the first _ in the line
  //if there's no _ in the line
  //(or no _s 'anymore' because we will keep calling this function
  //and solve the problem of multiple _s recursively)
  char * pos = strchr(line, '_');
  if (pos == NULL) {
    //if there's no _, return the line
    return line;
  }
  //find the second _ in the line
  char * pos2 = strchr(pos + 1, '_');
  if (pos2 == NULL) {
    //if there's no 2nd _, it's an error
    error("No 2nd _ exists!");
  }
  //record the category name's size
  size_t wordSZ = pos2 - pos - 1;
  //get the category name or integer
  //use judgeWord to decide the word for substitution
  char * word = strndup(pos + 1, wordSZ);
  const char * sub = judgeWord(word, cats, previous, mode);
  //we don't need the category naem any more
  free(word);
  //get the size of substitution word, the original line size
  //caculate the result line's size
  size_t subSZ = strlen(sub);
  size_t lineSZ = strlen(line);
  size_t resultLen = lineSZ - wordSZ - 2 + subSZ;
  //we need one more position to put '\0'
  char * result = malloc((resultLen + 1) * sizeof(*result));
  //initialize the result line
  memset(result, '\0', resultLen + 1);
  //find the position where the first difference between original line and result line occurs
  size_t first = pos - line;
  for (size_t i = 0; i < first; i++) {
    //copy the part from original line
    result[i] = line[i];
  }
  for (size_t i = first; i < first + subSZ; i++) {
    //copy the substitution word
    result[i] = sub[i - first];
  }
  for (size_t i = first + subSZ; i < resultLen; i++) {
    //copy the rest of the original line
    result[i] = line[i - subSZ + wordSZ + 2];
  }
  free(line);
  //call the function recursively to see if there is a 2nd, 3rd blank in the same line
  return subWord(result, cats, previous, mode);
}

//read cats and words from file and store them in cat array
catarray_t * readCats(const char * fileName) {
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    error("No such category File!");
  }
  char * line = NULL;
  size_t sz = 0;
  //initialize a cat array
  catarray_t * cats = malloc(sizeof(*cats));
  cats->arr = NULL;
  cats->n = 0;
  while (getline(&line, &sz, f) >= 0) {
    //use storeOne function to pick information from one line
    //store the word into the correct category in the cat array
    cats = storeOne(line, cats);
    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    error("File cannot be closed!");
  }
  return cats;
}

//store one word into the correct category in the catarray
catarray_t * storeOne(char * line, catarray_t * cats) {
  //find the colon and the nextline to make sure the format is correct
  char * colon = strchr(line, ':');
  char * nextLine = strchr(line, '\n');
  if (nextLine == NULL || colon == NULL) {
    error("format not correct!");
  }
  //caculate the length of category name and word
  //and copy them from the line
  size_t catLen = colon - line;
  char * catWord = strndup(line, catLen);
  size_t wordLen = nextLine - colon - 1;
  char * word = strndup(colon + 1, wordLen);
  //check each category in the car array to see if the category already exists
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(catWord, cats->arr[i].name) == 0) {
      //if exists, resize the char ** words
      //and add the word in this category
      cats->arr[i].n_words++;
      cats->arr[i].words =
          realloc(cats->arr[i].words, cats->arr[i].n_words * sizeof(*cats->arr[i].words));
      cats->arr[i].words[cats->arr[i].n_words - 1] = word;
      free(catWord);
      return cats;
    }
  }
  //if not exists such category
  //add such one, and add the word to it
  cats->n++;
  cats->arr = realloc(cats->arr, cats->n * sizeof(*cats->arr));
  category_t one;
  one.name = catWord;
  one.n_words = 1;
  one.words = malloc(sizeof(*one.words));
  one.words[0] = word;
  cats->arr[cats->n - 1] = one;
  return cats;
}

//free the text template
void freeT(text * t) {
  for (size_t i = 0; i < t->textSZ; i++) {
    free(t->lines[i]);
  }
  free(t->lines);
  free(t);
}

//free the cat array
void freeArr(catarray_t * cats) {
  if (cats != NULL) {
    for (size_t i = 0; i < cats->n; i++) {
      freeCT(&cats->arr[i]);
    }
    if (cats->arr != NULL) {
      free(cats->arr);
    }
    free(cats);
  }
}

//free one single category
void freeCT(category_t * cat) {
  for (size_t i = 0; i < cat->n_words; i++) {
    free(cat->words[i]);
  }
  free(cat->name);
  free(cat->words);
}
