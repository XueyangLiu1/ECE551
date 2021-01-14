#include <stdio.h>
#include <stdlib.h>

/*size_t firstOnly(int * array, size_t n) {
  size_t count = 0;
  if (array == NULL || n == 0) {
    return count;
  }
  count = 1;
  for (int i = 0; i < n - 1; i++) {
    if (array[i + 1] > array[i]) {
      count++;
    }
    else {
      return count;
    }
  }
  return count;
}*/

size_t maxSeq(int * array, size_t n) {
  size_t count = 0;
  if (array == NULL || n == 0) {
    return count;
  }
  count = 1;
  /*newly added*/
  size_t countMax = 1;
  size_t i = 0;
  while (i < n - 1) {
    if (array[i] < array[i + 1]) {
      count++;
      if (i == n - 2 && count > countMax) {
        countMax = count;
      }
    }
    else {
      if (count > countMax) {
        countMax = count;
      }
      count = 1;
    }
    i++;
  }
  /*To reduce time complexity from quadratic to linear*/
  /*newly added*/

  /* for (int i = 0; i < n; i++) {    */
  /*   size_t each_count = firstOnly(&array[i], n - i); */
  /*   if (each_count > count) { */
  /*     count = each_count; */
  /*   } */
  /* } */
  return countMax;
}
