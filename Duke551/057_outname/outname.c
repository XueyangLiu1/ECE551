#include "outname.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  size_t len = strlen(inputName);
  char * result;
  result = strndup(inputName, len);
  result = realloc(result, (len + 8) * sizeof(*result));
  strcpy(result + len, ".counts\0");
  return result;
}
