#include <cstdio>
#include <cstdlib>

#include "vector.hpp"

int main(void) {
  Vector2D v1;
  Vector2D v2;
  v1.initVector(1.0, 2.0);  // we will see a better way to do this later
  v2.initVector(-1.5, 3.0);
  std::printf("Vector v1 = ");
  v1.print();  // we will see a better way to do this later
  std::printf(" and has magnitude %.2f\n", v1.getMagnitude());
  std::printf("Vector v2 = ");
  v2.print();
  std::printf(" and has magnitude %.2f\n", v2.getMagnitude());
  std::printf("v1 + v2 = ");
  (v1 + v2).print();
  std::printf("\n");
  std::printf("v1 += v2 = ");
  (v1 += v2).print();
  std::printf("\n");
  std::printf("Now v1 = ");
  v1.print();
  std::printf("\n");
  std::printf("v1 . v2 = %.2f\n", v1.dot(v2));
  return EXIT_SUCCESS;
}
