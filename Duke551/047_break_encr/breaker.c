#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void breaker(FILE * f) {
  int c;
  int freqCount[26];
  for (int i = 0; i < 26; i++) {
    freqCount[i] = 0;
  }
  //initialize the freq count array
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      freqCount[c]++;
    }
  }
  int maxFreq = 0;
  int maxIndex = 0;
  for (int i = 0; i < 26; i++) {
    if (freqCount[i] > maxFreq) {
      maxFreq = freqCount[i];
      maxIndex = i;
    }
  }
  if (maxFreq == 0) {
    fprintf(stderr, "No letters in file.\n");
    exit(EXIT_FAILURE);
  }
  else if (maxIndex >= 4) {
    fprintf(stdout, "%d\n", maxIndex - 4);
  }
  else {
    fprintf(stdout, "%d\n", maxIndex + 22);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  breaker(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
