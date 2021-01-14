#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void test(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  test(0, 0, 1);
  test(3, 0, 1);
  test(4290000000, 1, 4290000000);
  test(0, 5, 0);
  test(4, 4, 256);
  test(1, 5, 1);
  return EXIT_SUCCESS;
}
