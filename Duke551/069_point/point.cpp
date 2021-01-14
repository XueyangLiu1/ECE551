#include "point.hpp"

#include <cmath>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
}
