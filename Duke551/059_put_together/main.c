#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

void error() {
  perror("NULL!");
  exit(EXIT_FAILURE);
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    error();
  }
  char * line = NULL;
  size_t sz = 0;
  counts_t * c = createCounts();
  while (getline(&line, &sz, f) > 0) {
    //printf("%s", line);
    char * next = strchr(line, '\n');
    if (next != NULL) {
      *next = '\0';
    }
    addCount(c, lookupValue(kvPairs, line));
    free(line);
    line = NULL;
  }
  free(line);
  assert(fclose(f) == 0);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 2) {
    error();
  }
  kvarray_t * kv = readKVs(argv[1]);
  //printKVs(kv);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      error();
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      error();
    }
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
