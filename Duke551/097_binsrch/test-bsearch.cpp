#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
//sin
class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};
//constant -10
class NegFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -10; }
};
//constant 3
class PosFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 3; }
};
//monotone-increasing f(x)=2x+2
class MonoIncrsFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 2 * arg + 2; }
};
//monotone-decreasing f(x)=-x
class MonoDcrsFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -arg; };
};
void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int num;
  //max invocations of f
  if (high > low) {
    num = log(high - low) / log(2) + 1;
  }
  else {
    num = 1;
  }
  CountedIntFn * function = new CountedIntFn(num, f, mesg);
  //perform the binary search
  int res = binarySearchForZero(function, low, high);
  //check the answer
  if (res != expected_ans) {
    fprintf(stderr, "The result of funtion %s is %d, not %d!\n", mesg, res, expected_ans);
    exit(EXIT_FAILURE);
  }
}
int main() {
  SinFunction sf;
  NegFunction nf;
  PosFunction pf;
  MonoIncrsFunction mif;
  MonoDcrsFunction mdf;
  //f(x)=sinx
  check(&sf, 0, 150000, 52359, "Sin");
  //f(x)=-10
  check(&nf, -100, 100, 99, "Neg in range(-100,100)");
  check(&nf, 10, 1000, 999, "Neg in range(10,100)");
  check(&nf, -100, -10, -11, "Neg in range(-100,-10)");
  check(&nf, 0, 0, 0, "Neg in (0,0)");
  //f(x)=3
  check(&pf, -100, 100, -100, "Pos in range(-100,100)");
  check(&pf, 10, 1000, 10, "Pos in range(10,100)");
  check(&pf, -100, -10, -100, "Pos in range(-100,-10)");
  check(&pf, 0, 0, 0, "Pos in (0,0)");
  //f(x)=2x+2
  check(&mif, -100, 100, -1, "MIF in range(-100,100)");
  check(&mif, 10, 1000, 10, "MIF in range(10,100)");
  check(&mif, -100, -10, -11, "MIF in range(-100,-10)");
  //f(0) = 2*0+2 = 2>0
  check(&mif, 0, 0, 0, "MIF in (0,0)");
  //f(x)=-x
  check(&mdf, -100, 100, 0, "MDF in range(-100,100)");
  check(&mdf, 10, 1000, 999, "MDF in range(10,100)");
  check(&mdf, -100, -10, -100, "MDF in range(-100,-10)");
  check(&mdf, 0, 0, 0, "MDF in (0,0)");
}
