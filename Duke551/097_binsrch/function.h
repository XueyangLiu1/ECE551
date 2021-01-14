#ifndef __FUNCTION_H__
#define __FUNCTION_H__
template<typename R, typename A>
class Function {
 public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};
int binarySearchForZero(Function<int, int> * f, int low, int high);
#endif
