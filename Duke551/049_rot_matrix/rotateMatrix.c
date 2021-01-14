#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void rotate(FILE * f) {
  char output[10][10];
  char l[11];
  int lineNum = 0;
  while (fgets(l, 12, f) != NULL) {
    lineNum++;
    if (lineNum > 10) {
      fprintf(stderr, "The input file has more than 10 lines.\n");
      exit(EXIT_FAILURE);
    }
    if (l[10] != '\n') {
      fprintf(stderr, "The char numbers on line %d is not correct.\n", lineNum);
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 10; i++) {
      output[i][10 - lineNum] = l[i];
    }
  }
  if (lineNum < 10) {
    fprintf(stderr, "The input file has less than 10 lines.\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", output[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  rotate(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
