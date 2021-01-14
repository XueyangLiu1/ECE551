#ifndef _EXCEPTION_H__
#define _EXCEPTION_H__
#include <exception>
#include <iostream>
#include <stdexcept>

//a function to output the error message and exit failure
void errmsg(const char * msg) {
  std::cerr << msg << std::endl;
  exit(EXIT_FAILURE);
}
//several customized exceptions
class argErr : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "You should use the arguments above!";
  }
};
class strToNum : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "Error when converting the page number!";
  }
};
class noFile : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "Error: The file above is not found!";
  }
};
class noPound : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "Format err: There is no pound mark in the file!";
  }
};

class noChoices : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "Format err: # appers at the first line!";
  }
};

class goNoWhere : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "The page above has a reference to an invalid page!";
  }
};

class notReferenced : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "The page above is in the story but never referenced!";
  }
};

class noResults : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "The story does not have at least one win page and one lose page!";
  }
};
class notWinable : public std::exception {
 public:
  virtual const char * what() const throw() { return "There is no way to win"; }
};
#endif
