#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
void process(FILE * f) {
  char ** lines = malloc(sizeof(*lines));
  if (lines == NULL) {
    perror("mem not enough!");
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t charCount = 0;
  size_t lineCount = 0;
  while (getline(&line, &charCount, f) >= 0) {
    lines = realloc(lines, (lineCount + 1) * sizeof(*lines));
    lines[lineCount] = line;
    lineCount++;
    line = NULL;
  }
  //get each line from file, realloc lines every time and write line to lines
  sortData(lines, lineCount);
  for (size_t i = 0; i < lineCount; i++) {
    printf("%s", lines[i]);
    free(lines[i]);
  }
  free(lines);
  free(line);
}
int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    FILE * f = stdin;
    if (f == NULL) {
      perror("Could not open file");
      return EXIT_FAILURE;
    }
    process(f);
    //if (fclose(f) != 0) {
    //perror("Failed to close the input file!");
    //return EXIT_FAILURE;
    //}
  }
  if (argc > 1) {
    for (size_t i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }
      process(f);
      if (fclose(f) != 0) {
        fprintf(stderr, "Failed to close the input file: %s!", argv[i]);
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
