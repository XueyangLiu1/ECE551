#include "kv.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void savePair(kvpair_t * pair, char * line) {
  char * equal = strchr(line, '=');
  assert(equal != NULL);
  size_t key_len = equal - line;
  pair->key = strndup(line, key_len);
  char * next = strchr(equal + 1, '\n');
  if (next != NULL) {
    size_t value_len = next - equal - 1;
    pair->value = strndup(equal + 1, value_len);
  }
  else {
    pair->value = strdup(equal + 1);
  }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t * results = malloc(sizeof(*results));
  assert(results != NULL);
  results->pairs = malloc(sizeof(*results->pairs));
  assert(results->pairs != NULL);
  results->len = 0;
  char * line = NULL;
  size_t sz = 0;
  FILE * f = fopen(fname, "r");
  assert(f != NULL);
  while (getline(&line, &sz, f) >= 0) {
    results->len++;
    results->pairs = realloc(results->pairs, results->len * sizeof(*results->pairs));
    savePair(&results->pairs[results->len - 1], line);
    free(line);
    line = NULL;
  }
  free(line);
  assert(fclose(f) == 0);
  return results;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->len; i++) {
    free((pairs->pairs + i)->key);
    free((pairs->pairs + i)->value);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    if (strcmp(key, pairs->pairs[i].key) == 0) {
      return pairs->pairs[i].value;
    }
  }
  return NULL;
}
