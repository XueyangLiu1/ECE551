#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(FILE * f, int key, FILE * outfile) {
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    char * ptr = line;
    while (*ptr != '\0') {
      int c = *ptr;
      if (isalpha(c)) {
        c = tolower(c);
        c -= 'a';
        c += key;
        c %= 26;
        c += 'a';
      }
      *ptr = c;
      ptr++;
    }
    fprintf(outfile, "%s", line);
  }
  free(line);
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  int key = atoi(argv[1]);
  if (key == 0) {
    fprintf(stderr, "Invalid key (%s): must be a non-zero integer\n", argv[1]);
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[2], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  //outfileNAme is argv[2] + ".txt", so add 4 to its length.(which is wrong! we need 1 more for \0)
  char * outFileName = malloc((strlen(argv[2]) + 5) * sizeof(*outFileName));
  strcpy(outFileName, argv[2]);
  strcat(outFileName, ".enc");
  FILE * outFile = fopen(outFileName, "w");
  free(outFileName);
  encrypt(f, key, outFile);
  if (fclose(outFile) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
