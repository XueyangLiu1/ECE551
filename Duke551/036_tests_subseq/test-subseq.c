#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void doTest(int * array, size_t n, size_t expected) {
  printf("maxSeq(");
  if (array == NULL) {
    printf("NULL");
  }
  else {
    printf("{");
    for (int i = 0; i < n; i++) {
      printf("%d", array[i]);
      if (i < n - 1) {
        printf(", ");
      }
    }
    printf("}");
  }
  size_t s = maxSeq(array, n);
  printf(", %lu) is %lu\n", n, s);

  if (s != expected) {
    printf("failed at this test! expected %lu but got %lu\n", expected, s);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array1[] = {1, 2, 1, 2, 3, 2, 3, 4, 5, 6, 7, 7, 8, 9, 11, 12, 13, 14, 15};
  int array2[] = {-42, 11, 13, 15, 21, -25, -26, 31, -100, -99, -98, -97, -96, -95};
  size_t n = 3;
  size_t e = 2;
  doTest(array1, n, e);
  n = 5;
  e = 3;
  doTest(array1, n, e);
  n = 11;
  e = 6;
  doTest(array1, n, e);
  n = 19;
  e = 8;
  doTest(array1, n, e);
  n = 2;
  e = 2;
  doTest(array2, n, e);
  n = 2;
  e = 1;
  doTest(&array2[4], n, e);
  n = 8;
  e = 5;
  doTest(array2, n, e);
  n = 14;
  e = 6;
  doTest(array2, n, e);
  n = 0;
  e = 0;
  doTest(array1, n, e);
  doTest(NULL, n, e);
  printf("all tests passed!\n");
  return EXIT_SUCCESS;
}
