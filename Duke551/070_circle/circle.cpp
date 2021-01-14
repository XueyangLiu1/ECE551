#include "circle.hpp"

#include <cmath>
void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  const double sum = radius + otherCircle.radius;
  double smallerR;
  double largerR;
  if (radius >= otherCircle.radius) {
    smallerR = otherCircle.radius;
    largerR = radius;
  }
  else {
    largerR = otherCircle.radius;
    smallerR = radius;
  }
  const double sub = largerR - smallerR;
  const double distance = center.distanceFrom(otherCircle.center);

  if (distance >= sum) {
    return 0.0;
  }
  else if (distance <= sub) {
    return M_PI * smallerR * smallerR;
  }
  else {
    double a = std::acos((smallerR * smallerR + distance * distance - largerR * largerR) /
                         (2.0 * smallerR * distance));
    double b = std::acos((largerR * largerR + distance * distance - smallerR * smallerR) /
                         (2.0 * largerR * distance));
    return a * smallerR * smallerR + b * largerR * largerR -
           smallerR * distance * std::sin(a);
  }
}
